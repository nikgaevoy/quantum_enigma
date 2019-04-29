#include "pch.h"
#include "quantum/utils.h"
#include "quantum/gates.h"


const size_t qubits = 17; /// causes bad_alloc if >= 28
const size_t A_part = 9;
const size_t B_part = qubits - A_part;


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
	uniform_real_distribution<flt> urd(0, 1);

	vector<complex_t> state(1u << qubits);
	state[0] = 1;

	fft_prefix_gate(state, A_part);

	crazy_gate(state, A_part, n, x);

	auto B = measure_suffix(state, B_part, urd(mt));

	fft_prefix_gate(state, A_part, true);

	auto A = measure_suffix(state, qubits, urd(mt));

	assert((A >> A_part) == B);
	A &= (1u << A_part) - 1;

	auto r = gcd(A, (1u << A_part));

	return check(n, x, r);
}


unsigned Shor()
{
	const unsigned n = 1u << 8u;
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
			else
				cout << "fail" << endl;
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << setprecision(4);

	cout << Shor() << endl;

	cout << "clock: " << clock() / (flt) CLOCKS_PER_SEC << endl;

	return 0;
}
