"""只读分析已下载的官方榜单；运行后向标准输出打印统计，不联网。"""
import json
from collections import Counter, defaultdict
from pathlib import Path

import pymupdf

ROOT = Path(__file__).resolve().parent


def read_icpc(name):
    rows = []
    doc = pymupdf.open(ROOT / name)
    headers = {w[4]: w[0] for w in doc[0].get_text('words') if w[4] in ('过题数', '总用时')}
    score_x, penalty_x = headers['过题数'], headers['总用时']
    for page in doc:
        words = page.get_text('words')
        anchors = [w for w in words if w[0] < 90 and w[4].isdigit()]
        for anchor in anchors:
            same_row = [w for w in words if abs(w[1] - anchor[1]) < 1.5]
            solved = [w[4] for w in same_row if score_x <= w[0] < penalty_x and w[4].isdigit()]
            penalty = [w[4] for w in same_row if w[0] >= penalty_x and w[4].isdigit()]
            assert len(solved) == len(penalty) == 1, (name, page.number, anchor, solved, penalty)
            rows.append({'rank': int(anchor[4]), 'solved': int(solved[0]), 'penalty': int(penalty[0])})
    assert all(a['solved'] >= b['solved'] for a, b in zip(rows, rows[1:]))
    assert all(a['rank'] <= b['rank'] for a, b in zip(rows, rows[1:]))
    for a, b in zip(rows, rows[1:]):
        if a['rank'] == b['rank']:
            assert (a['solved'], a['penalty']) == (b['solved'], b['penalty'])
    return rows


def distribution(rows):
    grouped = defaultdict(list)
    for row in rows:
        grouped[row['solved']].append(row['rank'])
    return {'teams': len(rows), 'max_rank': max(r['rank'] for r in rows), 'score_bands': [
        {'solved': s, 'count': len(rs), 'ranks': [min(rs), max(rs)]}
        for s, rs in sorted(grouped.items(), reverse=True)
    ]}


result = {}
for i in (1, 2):
    result[f'ICPC_{i}_official_pdf'] = distribution(read_icpc(f'2026ICPC网络赛{i}.pdf'))

cc = json.loads((ROOT / '2026CCPC网络赛榜单.json').read_text(encoding='utf-8-sig'))
all_rows = cc['xcpcRankings']['rankings']
formal = [r for r in all_rows if not r['teamInfo'].get('excluded', False)]
active = [r for r in formal if any(d.get('validSubmitCount', 0) > 0 for d in r.get('detailsByProblemSetProblemId', {}).values())]
active.sort(key=lambda r: (-r['solvedCount'], r['solvingTime']))
normalized = [{'rank': i + 1, 'solved': r['solvedCount']} for i, r in enumerate(active)]
result['CCPC_public_api'] = {
    'all_rows': len(all_rows), 'formal_rows': len(formal),
    'active_formal_rows': len(active), 'formal_schools': len({r['teamInfo']['schoolName'] for r in formal}),
    'active_formal_schools': len({r['teamInfo']['schoolName'] for r in active}),
    'formal_member_entries': sum(len(r['teamInfo'].get('memberNames', [])) for r in formal),
    'active_formal_member_entries': sum(len(r['teamInfo'].get('memberNames', [])) for r in active),
    'distribution': distribution(normalized), 'problem_counts': []}
for pid, info in cc['xcpcRankings']['problemInfoByProblemSetProblemId'].items():
    accepted = sum(r.get('detailsByProblemSetProblemId', {}).get(pid, {}).get('acceptTime', -1) >= 0 for r in active)
    attempted = sum(r.get('detailsByProblemSetProblemId', {}).get(pid, {}).get('validSubmitCount', 0) > 0 for r in active)
    result['CCPC_public_api']['problem_counts'].append({
        'label': info['label'], 'active_formal_accepted': accepted, 'active_formal_attempted': attempted,
        'rate': round(accepted / len(active), 4), 'platform_acceptCount': info['acceptCount'],
        'platform_submitCount': info['submitCount']})
assert sum(r['solvedCount'] for r in active) == sum(x['active_formal_accepted'] for x in result['CCPC_public_api']['problem_counts'])
for city in ('shenzhen', 'chongqing'):
    teams = json.loads((ROOT / f'{city}-teams.json').read_text(encoding='utf-8'))
    runs = json.loads((ROOT / f'{city}-runs.json').read_text(encoding='utf-8'))
    formal = {t['team_id'] for t in teams if
              (t.get('official') or 'official' in t.get('group', [])) and
              not (t.get('unofficial') or 'unofficial' in t.get('group', []))}
    ac = {(r['team_id'], r['problem_id']) for r in runs if
          r['team_id'] in formal and r['status'] == 'ACCEPTED' and 0 <= r['timestamp'] <= 18000}
    per_team = Counter(t for t, _ in ac)
    result[f'history_{city}'] = {
        'all_teams': len(teams), 'formal_teams': len(formal),
        'solved_distribution': dict(sorted(Counter(per_team.get(t, 0) for t in formal).items())),
        'accepted': {chr(65+i): sum(int(p) == i for _, p in ac) for i in range(13)}}
print(json.dumps(result, ensure_ascii=False, indent=2))
