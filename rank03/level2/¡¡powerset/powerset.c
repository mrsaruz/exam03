#include <stdio.h>
#include <stdlib.h>

void	print_subset(int *arr, int *path, int len)
{
	int i = 0;
	int first = 1;

	while (i < len)
	{
		if (path[i] == 1)
		{
			if (first == 0)
				printf(" ");
			printf("%d", arr[i]);
			first = 0;
		}
		i++;
	}
	printf("\n");
	return ;
}


void backtrack(int *arr, int *path, int len, int i, int sum, int target)
{
	if (i == len)
	{
		if (sum == target)
			print_subset(arr, path, len);
		return ;
	}

	path[i] = 1; 
	backtrack(arr, path, len, i + 1, sum + arr[i], target);
	
	path[i] = 0;
	backtrack(arr, path, len, i + 1, sum, target);
}



int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);

	int	i = 0;
	int	target = atoi(av[1]);
	int	len = ac - 2;
	int	*arr = malloc(sizeof(int) * len);
	int	*path = calloc(len, sizeof(int));

	if (!arr || !path)
		return (1);
	while (i < len)
	{
		arr[i] = atoi(av[i + 2]);
		i++;
	}
	backtrack(arr, path, len, 0, 0, target);
	free(arr);
	free(path);
	return (0);
}















