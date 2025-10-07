
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

void	ft_filter(char *line, char *str)
{
	int i = 0;
	int len = strlen(str);

	while (line[i])
	{
		int j = 0;
		while (str[j] && line[i + j] == str[j])
			j++;
		if (j == len)
		{
			while (j > 0)
			{
				write(1, "*", 1);
				j--;
			}
			i += len;
		}
		else
		{
			write(1, &line[i], 1);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	char line[999999];
	int i = 0; 
	int bytes_read = 1;

	if (ac != 2)
		return (1);
	while (bytes_read > 0)
	{
		bytes_read = read(0, &line[i], BUFFER_SIZE);

		if (bytes_read < 0)
		{
			perror("Error:");
			return (1);
		}
		i += bytes_read;
	}
	line[i] = '\0';
	ft_filter(line, av[1]);
	return (0);
}


































