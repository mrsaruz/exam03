/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_solution_gnl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:59:11 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/02 18:59:15 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char	*ft_strchr(char *s, int c)
{
	int	i = 0;
	while(s[i] != c)
		i++;
	if (s[i] == c)
		return s;
	else
		return NULL;
}

//CORREGIDO
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (char *)s; //devuelve el puntero actual (se usa el puntero directamente)
		s++;
	}
	if (c == '\0') // también hay que comprobar si buscamos '\0'
		return (char *)s;
	return (NULL); //se entiende que devuelves un puntero vacio (NULL)
}

/*char	*ft_strchr(const char *s, int c)
{
	int	i = 0;
	
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]); //devuelve la direccion del caracter encontrado (se usa un indice i)
		i++;
	}
	if (c == '\0')
		return((char *)&s[i]);
	return (NULL);
}*/

//OK
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

//CORREGIDO
void	*ft_memcpy(void *dest, const void *src, size_t n) //copia n bytes desde src (origen) a la dirección dest
{
	unsigned char       *d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *)src;

	if (!dest || !src) //si alguno de los punteros es NULL, se evita copiar desde/hacia una direccion invalida
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}
/*el ultimo while equivale a 
while (n > 0) 
{
    *d++ = *s++;
    n--;
}
*/
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
//CORREGIDO
int	str_append_mem(char **s1, char *s2, size_t size2) //cuando vas a copiar una parte, hasta \n
{
	size_t	size1; //s1 es lo que teniamos y vamos a concatenar lo nuevo (s2)
	char	*tmp;
	
	size1 = 0;
	if (*s1)
		size1 = ft_strlen(*s1);
		
	tmp = malloc(size2 + size1 + 1); //tmp es un puntero q apunta a un nuevo bloque de memoria dd guardaremos (s1 + s2)
	if (!tmp)
		return 0;
		
	if (*s1) // solo copiamos si *s1 no es NULL //Firma d memcpy: void	*ft_memcpy(void *dest, const void *src, size_t n);
		ft_memcpy(tmp, *s1, size1); //memcpy en si mismo solo copia pisando lo q hay, no concatena
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
	*s1 = tmp; //ahora s1 apunta al nuevo bloque
	return 1; //todo fue ok, devuelve 1
}
//OK
int	str_append_str(char **s1, char *s2) //cuando vas a copiar la linea completa (no hay \n)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}
//INCORR
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
//CORREGIDO
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *d = (unsigned char *)dest;
	const unsigned char *s = (const unsigned char *)src;

	if (!dest || !src)
		return NULL;
	if (d < s)
	{ // copiar hacia adelante
		while (n--) //resta uno a n en cada iteración
			*d++ = *s++; //hacia adelante
	}
	else if (d > s)
	{ // copiar hacia atrás
		while (n--) //resta uno a n en cada iteración
			d[n] = s[n]; //hacia atras
	}
	return (dest); // si d == s, no hace falta copiar
}
//INCORR
char	*get_next_line(int fd)
{
	static	char b[BUFFER_SIZE + 1] = "";
	char	*ret = NULL;
	char	*tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
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

//CORREGIDO
char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1]; //b es un buffer donde guardamos lo q leemos con read
	char		*ret = NULL; //ret es la linea que vammos construyendo y devolvemos
	char		*tmp;
	int			read_ret;

	while (1) // 3 PARTES: 1) si hay \n 2) si no hay \n pero hay algo en b 3) read 
	{
		tmp = ft_strchr(b, '\n'); //busca salto linea en b
		if (tmp) // 1)si existe \n 
		{
			if (!str_append_mem(&ret, b, tmp - b + 1)) //copiamos hasta \n (incl.) en ret
				return (free(ret), NULL);                                                 
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1); // y desplaza lo que sobra tras \n al inicio de b para la ss vuelta (+1 para \0)
			return (ret); //devuelve la linea hasta \n
		}
		if (*b) //2)no encontramos salto linea y en b hay texto util
		//if (b[0] != '\0') // *b significa el valor almacenado en la 1ª posición del arreglo, es decir, b[0].
		{ //la firma de funcion es int str_append_str(char **s1, char *s2)
			if (!str_append_str(&ret, b)) //como no hay \n→ concatenar lo que haya en b a lo leido antes en ret
				return (free(ret), NULL); //significa free(ret);return(NULL);
			b[0] = '\0'; //vaciamos b para indicar q no hay nada pendiente
		}
		// 3)Lee hasta BUFFER_SIZE bytes del archivo fd y los guarda en el buffer b.
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1) //si error, devuelve -1
			return (free(ret), NULL);
		if (read_ret == 0) //Si read() devuelve 0, ya no hay más datos para leer (EOF fin del archivo)
			return (ret);
		/*if (read_ret == 0) es mas explicito pero lo anterior es correcto
		{
    		if (ret && *ret) // hay contenido acumulado
        		return (ret);
    		return (NULL); // nada que devolver. Si no se acumulo nada en ret entonces sigue siendo NULL (ret se inicializa en NULL)
		}*/ //El valor de retorno read_ret indica cuántos bytes se leyeron realmente.
		b[read_ret] = '\0'; //tras hacer read (solo si read_ret > 0), añadimos \0 para tener una cadena valida //read lee bytes, pero no pone \0 al final.
	}
}
