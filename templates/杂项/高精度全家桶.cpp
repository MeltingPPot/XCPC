#include <bits/stdc++.h>
using namespace std;

struct BigInt {
    static constexpr int BASE = 1000000000;
    vector<int> digit;
    int sign = 1;

    BigInt(long long value = 0) {
        *this = value;
    }

    BigInt &operator=(long long value) {
        sign = value < 0 ? -1 : 1;
        value = abs(value);
        digit.clear();
        do {
            digit.emplace_back(value % BASE);
            value /= BASE;
        } while(value);
        return normalize();
    }

    BigInt &normalize() {
        while(digit.size() > 1 && digit.back() == 0)
            digit.pop_back();
        if(digit.size() == 1 && digit[0] == 0)
            sign = 1;
        return *this;
    }

    int absCompare(const BigInt &other) const {
        if(digit.size() != other.digit.size())
            return digit.size() < other.digit.size() ? -1 : 1;
        for(int i = (int)digit.size() - 1; i >= 0; --i) {
            if(digit[i] != other.digit[i])
                return digit[i] < other.digit[i] ? -1 : 1;
        }
        return 0;
    }

    BigInt &operator+=(const BigInt &other) {
        if(sign != other.sign)
            return *this -= -other;
        int carry = 0;
        for(int i = 0; i < (int)max(digit.size(), other.digit.size()) || carry; ++i) {
            if(i == (int)digit.size())
                digit.emplace_back(0);
            long long value =
                digit[i] + carry + (i < (int)other.digit.size() ? other.digit[i] : 0LL);
            digit[i] = value % BASE;
            carry = value / BASE;
        }
        return *this;
    }

    BigInt operator-() const {
        BigInt result = *this;
        if(result.digit != vector<int>{0})
            result.sign = -result.sign;
        return result;
    }

    BigInt &operator-=(const BigInt &other) {
        if(sign != other.sign)
            return *this += -other;
        if(absCompare(other) < 0) {
            BigInt result = other;
            result -= *this;
            return *this = -result;
        }
        int borrow = 0;
        for(int i = 0; i < (int)digit.size(); ++i) {
            long long value =
                digit[i] - borrow - (i < (int)other.digit.size() ? other.digit[i] : 0);
            borrow = value < 0;
            if(borrow)
                value += BASE;
            digit[i] = value;
        }
        return normalize();
    }

    BigInt &operator*=(const BigInt &other) {
        BigInt result;
        result.sign = sign * other.sign;
        result.digit.assign(digit.size() + other.digit.size(), 0);
        for(int i = 0; i < (int)digit.size(); ++i) {
            long long carry = 0;
            for(int j = 0; j < (int)other.digit.size() || carry; ++j) {
                long long value =
                    result.digit[i + j] + carry +
                    1LL * digit[i] * (j < (int)other.digit.size() ? other.digit[j] : 0);
                result.digit[i + j] = value % BASE;
                carry = value / BASE;
            }
        }
        return *this = result.normalize();
    }
};

BigInt operator+(BigInt a, const BigInt &b) {
    return a += b;
}
BigInt operator-(BigInt a, const BigInt &b) {
    return a -= b;
}
BigInt operator*(BigInt a, const BigInt &b) {
    return a *= b;
}
