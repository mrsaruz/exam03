
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

void	ft_filter(char *line, char *str)
{
	int len = strlen(str);
	int i = 0;

	while (line[i])
