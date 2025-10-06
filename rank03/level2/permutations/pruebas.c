#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
	int i = 0;
	while(s[i])
		i++;
	return(i);
}

int ft_isalpha(int c)
{
	return((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

void ft_swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

int ft_strchr(char *s, char c)
{
	int i = 0;
	while(s[i])
	{
		if(s[i] == c)
			return 1;
		i++;
	}
	return 0;
}

