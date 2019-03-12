#include "conversions.h"
int StringToInt(const char a[]) {
	int c, sign = 0, offset, n;
	if (a[0] == '-') {
		sign = -1;
	}
	if (sign == -1) {
		offset = 1;
	}
	else {
		offset = 0;
	}
	n = 0;
	for (c = offset; a[c] != '\0'; c++) {
		n = n * 10 + a[c] - '0';
	}
	if (sign == -1) {
		n = -n;
	}
	return n;
}