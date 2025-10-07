/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:04:09 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/07 12:59:42 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Assignment name : broken_GNL
Expected files  : get_next_line.c get_next_line.h
Allowed functions : read, free, malloc
--------------------------------------------------------------------------------
Repara la función get_next_line en el archivo get_next_line.c, cuya firma debe 
ser:

char *get_next_line(int fd);

Es posible que también necesites reparar otras funciones.

Descripción de la función get_next_line:

Tu función debe devolver una línea que haya sido leída del descriptor de archivo
 pasado como parámetro.

Una "línea que ha sido leída" se define como una sucesión de 0 a n caracteres 
que termina con un \n (código ASCII 0x0a) o con el final del archivo (EOF).

La línea debe devolverse incluyendo el \n si hay uno al final de la línea que 
se ha leído.

Cuando llegues al EOF, debes almacenar el búfer actual en un char * y devolverlo.
Si el búfer está vacío, debes devolver NULL.

En caso de error, devuelve NULL.

Si no devuelves NULL, el puntero debe ser liberable (freeable).

Tu programa se compilará con la bandera -D BUFFER_SIZE=xx, que debe usarse como 
el tamaño del búfer para las llamadas a read en tus funciones.

Tu función debe estar libre de fugas de memoria.

Cuando llegues al EOF, tu función no debe mantener ninguna memoria asignada con 
malloc excepto para la línea que se ha devuelto.

Llamar a tu función get_next_line en un bucle te permitirá leer el texto 
disponible en un descriptor de archivo línea por línea hasta el final del texto,
independientemente del tamaño del texto o de cualquiera de sus líneas.

Asegúrate de que tu función se comporte correctamente al leer desde un archivo, 
desde la salida estándar, desde una redirección, etc.

No se realizará ninguna llamada a otra función en el descriptor de archivo entre
dos llamadas a get_next_line.

Finalmente, consideramos que get_next_line tiene un comportamiento indefinido al
leer desde un archivo binario.
--------------------------------------------------------------------------------
*/


#include "broken_gnl.h"

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while (s[i] != c)/*(s[i] && s[i] != c)*/ /* añadir s[i] && */
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	/*size_t i = 0;*/
	
	while (--n > 0)/*(i < n)*/
	{
		((char *)dest)[n - 1] = ((char *)src)[n - 1];/*((char *)dest)[i] = ((char *)src)[i];*/
		/*i++;*/
	}
	return (dest);
}

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
	size_t	size1 = ft_strlen(*s1);/* = *s1 ? ft_strlen(*s1) : 0;*/
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	/*if (*s1)*/
	/*	*/ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp [size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	return (str_append_mem(s1, s2, ft_strlen(s2)));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest >/*<*/ src)
		return (ft_memcpy(dest, src, n));
	else if (dest == src)
		return (dest);
	size_t	i = ft_strlen((char *)src) - 1;/* = n*/
	while (i >=/*>*/ 0)
	{
		/*i--;*/
		((char *)dest)[i] = ((char *)src)[i];
		i--;/*clear*/
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
		/*b[0] = '\0';*/
		int	read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (NULL);
		/*if (read_ret == 0)
			break;*/
		b[read_ret] = 0;
		/*tmp = ft_strchr(b, '\n')*/
	}
	/*if (tmb)*/
	{
	/*	*/if (!str_append_mem(&ret, b, tmp - b + 1))
		{
			free(ret);
			return (NULL);
		}
		/*ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);*/
	}
	/*else
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
