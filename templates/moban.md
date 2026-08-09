# 1. 数论

## 1.1 素数

### 1.1.1 线性筛素数

```cpp
// bool vis[N]
void getprime(int MAXN){
    for(int i=2;i<=MAXN;i++){
        if(!vis[i]) prim[++prim[0]]=i;
        for(int j=1;j<=prim[0]&&prim[j]*i<=MAXN;++j){
            vis[prim[j]*i]=1;
            if(i%prim[j]==0) break;
        }
    }
}
// int vis[N]
void getprim(int MAXN){
    for(int i=2;i<=MAXN;++i){
        if(!vis[i]) vis[i]=prim[++prim[0]]=i;
        for(int j=1;j<=prim[0]&&i*prim[j]<=MAXN;++j){
            vis[i*prim[j]]=prim[j];
        }
    }
}
```
### 1.1.2 埃筛素数

```cpp
void getprim(int MAXN){
    int cnt(0);
    for(int i=2;i<=MAXN;++i){
        if(!vis[i]){
            prim[++cnt]=i;
            for(int j=i+i;j<=;j+=i) vis[j]=1;
        }
    }
}
```

### 1.1.3.1 素性检验（试除法）

```cpp
bool isPrime(int a){
    if(a<2) return 0;
  for(int i=2;i<a;++i)
    if(a%i==0) return 0;
  return 1;
}
```
### 1.1.3.2 素性检验（Miller–Rabin）

二次探测定理：若 $p$ 为奇素数，则 $x^2\equiv1 \mod p$ 或者 $x^2\equiv p-1 \mod p$.

```cpp
bool MillerRabin(int n){
    int test_time(30);
    if(n<3||n%2==0) return n==2;
    if(n%3==0) return n==3;
    int u(n-1),t(0);
    for(;u%2==0;u>>=1,++t);
    for(;test_time--;){
        int a(rand()%(n-3)+2);
        int v(qpow(a,u,n));// 快速幂
        if(v==1) continue;
        int s;
        for(s=0;s<t;++s){
            if(v==n-1) break;
            v=(long long) v*v%n;
        }
        if(s==t) return 0;
    }
    return 1;
}
```
### 1.1.4 质因数分解

```cpp
vector<int> BreakDown(int MAXN){
    vector<int> res;
    for(int i=2;i*i<=MAXN;++i){
        if(MAXN%i==0){
            for(;MAXN%i==0;MAXN/=i);
            res.pushback(i);
        }
    }
    if(MAXN^1) res.push_back(MAXN);
    return res;
}
```
## 1.2 欧拉函数

### 1.2.1 根号欧拉函数

设 $n=\prod^s_{i=1}p_i^{k_i}$，则有：

$$
\begin{aligned}
\varphi(n)&=\prod^s_{i=1}\varphi(p_i^{k_i})\\
    &=\prod^s_{i=1}(p_i-1)p_i^{k_i-1}\\
    &=\prod^s_{i=1}(1-\frac{1}{p_i})p_i^{k_i}\\
    &=n\prod^s_{i=1}(1-\frac{1}{p_i})
\end{aligned}
$$

```cpp
int euler_phi(int n){
    int ans(n);
    for(int i=2;i*i<=n;i++)
        if(n%i==0){
            ans=ans/i*(i-1);
            for(n%i==0) n/=i;
        }
    if(n>1) ans=ans/n*(n-1);
    return ans;
}
```
推论：对任意不全为 $0$ 的整数 $m,n,\varphi(mn)\varphi(\gcd(m,n))=\varphi(m)\varphi(n)\gcd(m,n)$.

### 1.2.2 欧拉求和

$$
n=\sum_{d|n}\varphi(d)
$$

### 1.2.1 欧拉反演

$$
\begin{aligned}
n&=\sum_{d|n}\varphi(d)\\
\gcd(a,b)&=\sum_{d|\gcd(a,b)}\varphi(d)\\
\gcd(a,b)&=\sum_{d}[d|a][d|b]\varphi(d)\\
\sum_{i=1}^n \gcd(i,n)&=\sum_{d|n}\lfloor\frac{n}{d}\rfloor\varphi(d)\\
\sum_{i=1}^d i[\gcd(i,d)=1]&=\sum_{d|n}\frac{d\times \varphi(d)}{2}\\
\end{aligned}
$$

## 1.3 筛法

### 1.3.1 筛法求欧拉函数

```cpp
void pre_eular(int MAXN){
    phi[1]=1;
    for(int i=2;i<=MAXN;++i){
        if(!phi[i]) prim[++prim[0]]=i,phi[i]=i-1;
        for(int j=1;j<=prim[0]&&i*prim[j]<=MAXN;++j){
            if(!(i%prim[j])){
                phi[i*prim[j]]=prim[j]*phi[i];
                break;
            }
            phi[i*prim[j]]=(prim[j]-1)*phi[i];
        }
    }
}
```
### 1.3.2 筛法求莫比乌斯函数

```cpp
void pre_mu(int MAXN){
    mu[1]=1;
    for(int i=2;i<=MAXN;i++){
        if(!vis[i]) prime[++cnt]=i,mu[i]=-1;
        for(int j=1;j<=cnt&&i*prime[j]<=MAXN;j++){
            vis[i*prime[j]]=1;
            if(i%prime[j]==0) break;
            mu[i*prime[j]]=-mu[i];
        }
    }
}
```
### 1.3.3 筛法求约数个数函数

```cpp
void pre_d(int MAXN){
    d[1]=1;
    for(int i=2;i<=MAXN;++i){
        if(!vis[i]) prim[++prim[0]]=i,d[i]=2,num[i]=1;
        for(int j=1;j<=prim[0]&&i*prim[j]<=MAXN;++j){
            vis[prim[j]*i]=1;
            if(i%prim[j]==0){
                num[i*prim[j]]=num[i]+1;
                d[i*prim[j]]=d[i]/(num[i]+1)*(num[i]+2);
                break;
            }
            num[i*prim[j]]=1;
            d[i*prim[j]]=d[i]<<1;
        }
    }
}
```

### 1.3.4 筛法求约数和
生成函数乘积，取质因子随机组合。
```cpp
void pre_f(int MAXN){
    // g[i]为i的最小质因子p的k次定比数列和
    g[1]=f[1]=1;
    for(int i=2;i<=MAXN;++i){
        if(!vis[i]) prim[++prim[0]]=i,g[i]=f[i]=i+1;
        for(int j=1;j<=prim[0]&&i*prim[j]<=MAXN;++j){
            vis[prim[j]*i]=1;
            if(i%prim[j]==0){
                g[i*prim[j]]=g[i]*prim[j]+1;
                f[i*prim[j]]=f[i]/g[i]*g[i*prim[j]];
                break;
            }
            g[i*prim[j]]=1+prim[j];
            f[i*prim[j]]=f[i]*(prim[j]+1);
        }
    }
}
```
## 1.4 最大公约数

### 1.4.1 欧几里得算法

```cpp
int gcd(int a,int b){return !b?a:gcd(b,a%b);}
int gcd(int a,int b){
  for(int tmp;b;)
    tmp=a,a=b,b=tmp%b;
  return a;
}
```

### 1.4.2 扩展欧几里得算法

```cpp
void Exgcd(ll a,ll b,ll &x,ll &y){
    if(!b) x=1,y=0;
    else Exgcd(b,a%b,y,x),y-=a/b*x;
}
```

## 1.5 模算术类

### 1.5.1 快速幂

```cpp
ll qpow(ll a,ll b,ll p){
    ll res(1);
    for(;b;b>>=1,a=a*a%p) if(b&1) res=res*a%p;
    return res%p;
}
```

### 1.5.2 逆元

#### 1.5.2.1 费马小定理
```cpp
int inv=qpow(a,p-2,p);// p为质数
```
#### 1.5.2.2 线性求逆元 
$$
i^{-1}\equiv-\lfloor\frac{p}{i}\rfloor\times(p\text{ mod } i)^{-1} \mod p
$$

```cpp
inv[1]=1;
for(int i=2;i<p;++i)
    inv[i]=(p-p/i)*inv[p%i]%p;
```

#### 1.5.2.2 扩欧求逆元 

```cpp
void Exgcd(ll a,ll b,ll &x,ll &y){
    if(!b) x=1,y=0;
    else Exgcd(b,a%b,y,x),y-=a/b*x;
}
int main(){
    ll x,y;
    Exgcd(a,p,x,y);
    x=(x%p+p)%p;//x是a在mod p下的逆元
}
```
#### 1.5.2.3 阶乘逆元

$$
\frac{1}{i!}\times i=\frac{1}{(i-1)!}
$$

得到：

$$
\frac{1}{i!}\times (i-1)!=\frac{1}{i}
$$

更一般的将 $i$ 替换为 $a_i$ 也可线性求列表逆元。

### 1.5.3 卢卡斯定理

```cpp
ll Lucas(ll n,ll k,ll p) {
    if(!k) return 1ll;
  return(C(n%p,k%p,p)*Lucas(n/p,k/p,p))%p;
}// p为质数
```
### 1.5.4 扩展卢卡斯定理

## 1.6 中国剩余定理

## 1.7 数论分块





# 2.线性代数

# 3.组合数学

# 4.多项式与生成函数

# 5.数值算法

# 6.博弈论

