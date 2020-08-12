#include "../include/conversions.h"

int string_to_int(const char* a)
{
	int c, sign = 0, offset, n;
	if (a[0] == '-')
	{
		sign = -1;
	}
	if (sign == -1)
	{
		offset = 1;
	}
	else
	{
		offset = 0;
	}
	n = 0;
	for (c = offset; a[c] != '\0'; c++)
	{
		n = n * 10 + a[c] - '0';
	}
	if (sign == -1)
	{
		n = -n;
	}
	return n;
}

char* scan_string()
{
	int c; // because getchar() -> int
	int i = 0;
	char* string = malloc(sizeof(char));
	char* tmp = NULL;
	if (string != NULL)
	{
		string[0] = '\0';
	}
	else
	{
		perror("AN ERROR OCCURRED");
		exit(-1);
	}
	while ((c = getchar()) != '\n' && c != EOF)
	{
		tmp = realloc(string, (size_t)i + 2);
		if (tmp != NULL)
		{
			string = tmp;
		}
		else
		{
			perror("AN ERROR OCCURRED");
			exit(-1);
		}
		if (string != NULL)
		{
			string[i] = (char)c;
			string[i + 1] = '\0';
		}
		else
		{
			perror("AN ERROR OCCURRED");
			exit(-1);
		}
		i++;
	}
	return string;
}

int int_len(int num) { return (int)floor(log10(abs(num))) + 1; }

int scan_int()
{
	int result;
	while (!scanf_s(" %d", &result) || result < 1)
	{
		puts("please input a posivite number (>=1)");
		while ((getchar()) != '\n'); // clear stdin buffer
	}
	getchar();
	return result;
}

int hash_password(const char* src)
{
	int result = 0;
	const int src_len = (int)strlen(src);
	for (int i = 0; i < src_len; i++)
	{
		result += (int)src[i];
	}
	return result;
}