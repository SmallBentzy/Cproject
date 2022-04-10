
#include <stdio.h>
#include <ctype.h> 
#include "Utililities.h"

void lowerCaseString(char* str) {
	while (*str)
	{
		//printf("%c", *str);
		if (isupper(*(str)))
			*str= tolower(*str);
		str++;
	}
	
}

//insensitive compares insensitive strings a b
int strcicmp(char const* a, char const* b)
{
	for (;; a++, b++) {
		int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
		if (d != 0 || !*a)
			return d;
	}
}
int strcincmp(char const* a, char const* b, int n)
{
	for ( ;n>=0; n--, a++, b++) {
		int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
		if (d != 0 || !*a)
			return d;
	}
	return 0;
}
void eraseSpace(char* str) {
	int i, index = -1;
	for (i = 0; str[i]; i++) {
		if (str[i] != ' ')
			index = -1;
		else if (index == -1)
			index = i;
	}
	if (index != -1)
		str[index] = '\0';
}