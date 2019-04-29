#pragma once

#include "../pch.h"

size_t measure_suffix(vector<complex_t> &state, size_t suffix, flt val)
{
	for (size_t i = 0; i < (1u << suffix); i++)
	{
		flt prob = 0;

		for (size_t j = 0; j < (state.size() >> suffix); j++)
			prob += len2(state[j + i * (state.size() >> suffix)]);

		if (prob > val)
		{
			for (size_t k = 0; k < state.size(); k++)
				if (k / (state.size() >> suffix) == i)
					state[k] /= sqrt(prob);
				else
					state[k] = 0;

			return i;
		}
		else
			val -= prob;
	}

	assert (false);
}
