/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl_solution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:14:08 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/07 15:39:03 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif


#include "broken_gnl.h"

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while (s[i] != c) /* añadir s[i] && */
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	/* añadir size_t i = 0; */
	
	while (--n > 0) /* cambiar por (i < n) */
	{
		((char *)dest)[n - 1] = ((char *)src)[n - 1]; /* cambiar [n-1] por [i] */
		/* añadir i++; */
	}
	return (dest);
}

/* No hay que tocar nada, está OK */

size_t	ft_strlen(char *s)
{
	size_t	ret = 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = ft_strlen(*s1); /* añadir = *s1 ? ft_strlen(*s1) : 0; */
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	/* añadir if (*s1) */
	/* poner tabulación */ ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

/* No hay que hacer nada, está OK */

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src) /* cambiar > por < */
		return (ft_memcpy(dest, src, n));
	else if (dest == src)
		return (dest);
	size_t	i = ft_strlen((char *)src) - 1; /* cambiar 'ft_strlen((char *)src) - 1' por 'n' */
	while (i >= 0) /* quitar el = */
	{
		/* añadir i--; */
		((char *)dest)[i] = ((char *)src)[i];
		i--; /* quitar esta línea, se pone arriba */
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;

	char	*tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return (NULL);
		/* añadir b[0] = '\0'; */
		int	read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		/* añadir:
		if (read_ret == 0)
			break; */
		b[read_ret] = 0;
		/* añadir tmp = ft_strchr(b, '\n'); */
	}
	/* añadir if (tmp)*/
	{
	/* añadir tabulación */	if (!str_append_mem(&ret, b, tmp - b + 1))
		{
			free(ret);
			return (NULL);
		}
		/* añadir ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1); */
	}
	/* añadir:
	else
	{
		b[0] = '\0';
		if (!ret || !*ret)
		{
			free(ret);
			return (NULL);
		}
	}*/
	return (ret);
}

/* main para probar que funciona 

#include <stdio.h>
#include <fcntl.h>
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
