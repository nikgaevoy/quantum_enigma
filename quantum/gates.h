#pragma once

#include "../pch.h"


void fft(vector<complex_t>::iterator be, vector<complex_t>::iterator en, complex_t w)
{
	auto mi = be + (en - be) / 2;

	if (mi == be)
		return;

	vector<complex_t> a0(mi - be), a1(en - mi);

	for (auto it = be; it != en; ++it)
		((it - be) % 2 == 0 ? a0 : a1)[(it - be) / 2] = *it;

	fft(a0.begin(), a0.end(), sqr(w));
	fft(a1.begin(), a1.end(), sqr(w));

	complex_t q = 1;

	for (size_t i = 0; i < a0.size(); i++)
	{
		*(be + i) = (a0[i] + q * a1[i]) / sqrt2;
		*(be + i + a0.size()) = (a0[i] - q * a1[i]) / sqrt2;

		q *= w;
	}
}


// fft gate
/// fast version, not a scheme
void fft_prefix_gate(vector<complex_t> &state, size_t prefix, bool inverse = false)
{
	flt ang = 2 * pi / (1u << prefix);

	if (inverse)
		ang *= -1;

	complex_t w(cos(ang), sin(ang));

	for (size_t i = 0; i < state.size(); i += 1u << prefix)
		fft(state.begin() + i, state.begin() + i + (1u << prefix), w);
}


// |j>|0> -> |j>|x^j mod N>
/// fast version; scheme version is way too crazy, forget about it!
void crazy_gate(vector<complex_t> &state, size_t prefix, unsigned N, unsigned x)
{
	assert((N << prefix) <= state.size());
	assert(x < N && N > 1);

	unsigned xp = 1;

	for (size_t j = 0; j < (1u << prefix); j++)
	{
		// not accurate, but fast
		swap(state[j], state[(xp << prefix) | j]);

		xp *= x;
		xp %= N;
	}
}
