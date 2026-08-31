#include <stdio.h>
#include <iostream>
const unsigned int bufl = 1 << 11;
const double base1[16] = {1,    1e-1, 1e-2,  1e-3,  1e-4,  1e-5,  1e-6,  1e-7,
                          1e-8, 1e-9, 1e-10, 1e-11, 1e-12, 1e-13, 1e-14, 1e-15};
const double base2[16] = {1,   1e1, 1e2,  1e3,  1e4,  1e5,  1e6,  1e7,
                          1e8, 1e9, 1e10, 1e11, 1e12, 1e13, 1e14, 1e15};
struct IN {
    FILE *IT;
    char ibuf[bufl], *is = ibuf, *it = ibuf;
    IN() {
        IT = stdin;
    }
    IN(char *a) {
        IT = fopen(a, "r");
    }
    inline char getChar() {
        if(is == it) {
            it = (is = ibuf) + fread(ibuf, 1, bufl, IT);
            if(is == it)
                return EOF;
        }
        return *is++;
    }
    template <typename Temp> inline void getInt(Temp &a) {
        a = 0;
        unsigned int b = 0, c = getChar();
        while(c < 48 || c > 57)
            b ^= (c == 45), c = getChar();
        while(c >= 48 && c <= 57)
            a = (a << 1) + (a << 3) + c - 48, c = getChar();
        if(b)
            a = -a;
    }
    IN &operator>>(char &a) {
        a = getChar();
        return *this;
    }
    IN &operator>>(char *a) {
        do {
            *a = getChar();
        } while(*a <= 32);
        while(*a > 32)
            *++a = getChar();
        *a = 0;
        return *this;
    }
    IN &operator>>(unsigned int &a) {
        getInt(a);
        return *this;
    }
};
struct OUT {
    FILE *IT;
    char obuf[bufl], *os = obuf, *ot = obuf + bufl;
    unsigned int Eps;
    long double Acc;
    OUT() {
        IT = stdout, Eps = 6, Acc = 1e-6;
    }
    OUT(char *a) {
        IT = fopen(a, "w"), Eps = 6, Acc = 1e-6;
    }
    inline void ChangEps(unsigned int x = 6) {
        Eps = x;
    }
    inline void flush() {
        fwrite(obuf, 1, os - obuf, IT);
        os = obuf;
    }
    inline void putChar(unsigned int a) {
        *os++ = a;
        if(os == ot)
            flush();
    }
    template <typename Temp> inline void putInt(Temp a) {
        if(a < 0) {
            putChar(45);
            a = -a;
        }
        if(a < 10) {
            putChar(a + 48);
            return;
        }
        putInt(a / 10);
        putChar(a % 10 + 48);
    }
    OUT &operator<<(char a) {
        putChar(a);
        return *this;
    }
    OUT &operator<<(char *a) {
        while(*a > 32)
            putChar(*a++);
        return *this;
    }
    OUT &operator<<(unsigned int a) {
        putInt(a);
        return *this;
    }
    ~OUT() {
        flush();
    }
};
IN fin;
OUT fout;