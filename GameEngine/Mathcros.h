#pragma once

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define clamp(a, b, c) min(max(a, b), c)

namespace math {
	float sq(float a) {
		return a * a;
	}
}