#include "conversions.h"

int stringToInt(const char a[]) {
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

char* scanString()
{
	
	int c; //because getchar() -> int
	int i = 0;
	char* string = malloc(sizeof(char));
	string[0] = '\0';
	while ((c = getchar()) != '\n' && c != EOF)
	{
		string = realloc(string, i + 2);
		string[i] = (char)c;
		string[i + 1] = '\0';
		i++;
	}
	return string;
}

int intLen(int num) {
	return (int)floor(log10(abs(num))) + 1;
}

int scanInt()
{
	int result;
	while (!scanf_s(" %d", &result) || result < 1) {
		puts("please input a posivite number (>1)");
		while ((getchar()) != '\n'); // clear stdin buffer
	}
	getchar();
	return result;
}
