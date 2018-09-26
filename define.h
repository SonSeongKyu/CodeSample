#pragma once
#include <assert.h>

#define DEV_VER

template <typename T>
T clamp(T x, T min, T max)
{
	assert(min <= max);
	return std::min(std::max(min, x), max);
}

int safe_div(int lhs, int rhs) {
	if (rhs == 0 || lhs == INT_MIN && rhs == -1) return 0;
	else return lhs / rhs;
}