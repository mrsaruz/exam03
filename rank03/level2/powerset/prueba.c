

#include <stdio.h>
#include <stdlib.h>


void	print_subset(int *set, int *path, int len)
{
	int i = 0;
	int first = 1;

	while (i < len)
	{
		if (path[i] == 1)
		{
			if (first == 0)
				printf(" ");
			printf("%d", set[i]);
			first = 0;
		}
		i++;
	}
	printf("\n");
	return ;
}


void	backtrack(int *set, int *path, int len, int i, int sum, int target)
{
	if (i == len)
	{
		if (sum == target)
			print_subset(set, path, len);
		return;
	}
	path[i] = 1;
	bactrack(set, path, len, i + 1, sum + set[i], target);
	path[i] = 0;
	backtrack(set, path, len, i + 1, sum, target);
}

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);

	int i = 0;
	int target = atoi(av[1]);
	int len = ac - 2;
	int *set = malloc(sizeof(int) * len);
	int *path = calloc(len, sizeof(int));

	if (!set || !path)
		return (1);

	while (i < len)
	{
		set[i] = atoi(av[i + 2]);
		i++;
	}
	backtrack(set, path, len, 0, 0, target);
	free(set);
	free(path);
	return (0);
}






