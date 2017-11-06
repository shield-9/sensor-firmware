#include "helper.h"

int1 divide_data(char *s1, char *s2) {
	for (int i = 0; s1[i] != '\0'; i++) {
		if (s1[i] == ',') {
			s1[i] = '\0'; // Replace "," to "\0",

			s2 = s1 + (i + 1);
			return 1;
		}
	}

	return 0;
}

int1 is_equal(char *s1, char *s2) {
	int i = 0;
	int is_null1 = 0, is_null2 = 0;
	while (!(is_null1 && is_null2)) {
		if (*(s1 + i) != *(s2 + i)) return 0;
		is_null1 = *(s1 + i) == '\0';
		is_null2 = *(s2 + i) == '\0';
		i++;
	}
	return 1;
}

int1 is_leap(long int y) { return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0; }

float str_to_float(char *s) {
	int i, j;
	float pow;
	float result = 0.0;

	i = 0;
	while (s[i] != '.' && s[i] != '\0') {
		i++;
	}

	pow = 0.1;
	for (j = i + 1; s[j] != '\0'; j++) {
		result += (s[j] - '0') * pow;
		pow /= 10.0;
	}

	pow = 1.0;
	for (j = i - 1; j > 0; j--) {
		result += (s[j] - '0') * pow;
		pow *= 10.0;
	}

	if (s[0] == '-') {
		result *= -1.0;
	}

	return result;
}
