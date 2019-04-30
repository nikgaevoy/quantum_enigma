#pragma once

#include <bits/stdc++.h>

using namespace std;

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


template<class T>
void get_continued_fraction(T a, T b, vector<T> &ret)
{
	while (b != 0)
	{
		ret.push_back(a / b);
		a %= b;

		swap(a, b);
	}
}


template<class T>
void get_fraction(typename vector<T>::iterator be, typename vector<T>::iterator en, T &a, T &b)
{
	if (be == en)
	{
		a = 0;
		b = 1;

		return;
	}

	get_fraction(be + 1, en, a, b);

	if (a != 0)
		swap(a, b);

	a += b * *be;
}
