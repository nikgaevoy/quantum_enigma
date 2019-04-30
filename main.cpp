#include "pch.h"
#include "quantum/utils.h"
#include "quantum/gates.h"


unsigned check(unsigned n, unsigned x, unsigned r)
{
	if (r % 2 == 1)
		return 0;

	auto xr = powmod(x, r / 2, n);

	auto g = gcd(xr + 1, n);

	if (1 < g && g < n)
		return g;

	g = gcd(xr - 1, n);

	if (1 < g && g < n)
		return g;
	return 0;
}


unsigned try_x(unsigned n, unsigned x)
{
	unsigned A_part = 1, B_part = 1;

	while ((1u << A_part) < n * n)
		A_part++;
	while ((1u << B_part) < n)
		B_part++;

	unsigned qubits = A_part + B_part; /// causes bad_alloc if >= 28

	cout << "qubits: " << qubits << endl;

	uniform_real_distribution<flt> urd(0, 1);

	vector<complex_t> state(1u << qubits);
	state[0] = 1;

	fft_prefix_gate(state, A_part);

	crazy_gate(state, A_part, n, x);

	auto B = measure_suffix(state, B_part, urd(mt));

	fft_prefix_gate(state, A_part, true);

	auto A = measure_suffix(state, qubits, urd(mt));

	auto M = 1u << A_part;

	assert((A >> A_part) == B);
	A &= M - 1;

	vector<unsigned> fr;

	get_continued_fraction(A, M, fr);

	for (size_t i = 1; i <= fr.size(); i++)
	{
		unsigned p, q;

		get_fraction(fr.begin(), fr.begin() + i, p, q);

		if (q > n)
			break;

		auto d = check(n, x, q);

		if (d != 0)
			return d;
	}

	return 0;
}


unsigned Shor(unsigned n)
{
	uniform_int_distribution<unsigned> uid(1, n - 1);

	for (ever) // :)
	{
		unsigned x, g;

		do
		{
			x = uid(mt);
			g = gcd(x, n);
		} while (g > 1);

		for (int i = 0; i < 20; i++)
		{
			auto d = try_x(n, x);

			if (d != 0)
				return d;
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << setprecision(4);

	cout << Shor(55) << endl;

	cout << "clock: " << clock() / (flt) CLOCKS_PER_SEC << endl;

	return 0;
}
