/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:19:45 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/02 18:59:37 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFER_SIZE
# define BUFER_SIZE 10
#endif

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while(s[1] != c)
		i++;
	if (s[i] == c)
		return s + 1;
	else
		return NULL;
}

size_t ft_strlen(char *s)
{
	size_t	i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (--n > 0)
	{
		((char*)dest)[n - 1] = ((char*)src)[n - 1];
	}
	return dest;
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t	size1 = ft_strlen(*s1);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp;
	return 1;
}

int	str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		return ft_memcpy(dest, src, n);
	else if (dest == src)
		return dest;
		size_t	i = ft_strlen(((char*)src) - 1);
	while (i >= 0)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i--;
	}
	return dest;
}

char	*get_next_line(int fd)
{
	static	char b[BUFER_SIZE + 1] = "";
	char	*ret = NULL;
	char	*tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFER_SIZE);
		if(read_ret = -1)
				return NULL;
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	return ret;
}
