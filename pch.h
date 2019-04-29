#pragma once

#include <bits/stdc++.h>

using namespace std;

#define ever ;;

mt19937 mt(736);

using flt = float;
using complex_t = complex<flt>;
using ll = long long;
using ull = unsigned long long;

const flt pi = 3.14159265358979323846;
const flt sqrt2 = sqrt(2);

template<class T>
T sqr(T x)
{
	return x * x;
}


template<class T>
T len2(const complex<T> &x)
{
	return sqr(x.real()) + sqr(x.imag());
}


template<class T>
T gcd(T a, T b)
{
	return b == 0 ? a : gcd(b, a % b);
}


template<class T>
T powmod(ull x, ull y, T mod)
{
	return y == 0 ? 1 : (y % 2 == 0 ? sqr(powmod(x, y / 2, mod)) : x * powmod(x, y - 1, mod)) % mod;
}
