

#include <stdio.h> 


int	invalid(char *s)
{
	int i = 0;
	int open = 0;
	int close = 0;

	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	return (open + close);
}

void	generate_result(char *s, int remove, int delete, int pos)
{
	if (remove == delete && !invalid(s))
	{
		puts(s);
		return ;
	}
	while (s[pos])
	{
		if (s[pos] == '(' || s[pos] == ')')
		{
			char c = s[pos];
			s[pos] = ' ';
			generate_result(s, remove, delete + 1, pos + 1);
			s[pos] = c;
		}
		pos++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	int remove = invalid(av[1]);
	generate_result(av[1], remove, 0, 0);
	return (0);
}







