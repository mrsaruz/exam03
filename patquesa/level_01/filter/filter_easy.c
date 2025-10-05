/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_easy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:30:53 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/02 18:56:33 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif


// Reemplaza todas las ocurrencias de str en line por '*'
void	ft_filter(char *line, int total_bytes, char *str)
{
	int	pat_len = strlen(str); //longitud patron
	int	i = 0; //indice para recorrer line
	int	j; //indice para comparar el patron

	while (i < total_bytes && line[i]) //recorre toda la cadena line
	{
		j = 0;
		while (str[j] && (i + j < total_bytes && line[i + j] == str[j])) //compara si hay coincidencia con patron
			j++;
		if (j == pat_len) // coincidencia completa
		{
			while (j > 0)
			{
				write(1, "*", 1);
				j--;
			}
			i += pat_len; // saltar el patrón reemplazado
		}
		else
		{
			write(1, &line[i], 1);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	char	*line = NULL;   // buffer dinámico que existe durante todo el programa, va acumulando datos leidos. Almacena todo para procesarlo al final.
	int		bytes_read = 1;
	int		total_bytes = 0;          // cantidad de datos acumulados
	char	tmp[BUFFER_SIZE]; //bufer temporal para cada  operacion de lectura (read), solo existe durabte cada iteracion del bucle

	if (argc != 2 || argv[1][0] == '\0')
		return (1);

	while ((bytes_read = read(0, tmp, BUFFER_SIZE)) > 0) //lee de stdun en bloques de BUFFER_SIZE
	{
		char *newbuf = realloc(line, total_bytes + bytes_read + 1); // +1 para '\0'
		if (!newbuf)
		{
			perror("Error");
			free(line);
			return (1);
		}
		line = newbuf;
		memcpy(line + total_bytes, tmp, bytes_read); //copia datos del buffer temporal a continuacion de los q ya habia en line (void *memcpy(void *dest, const void *src, size_t n))
		total_bytes += bytes_read; //actualiza total bytes = bytes anteriores + bytes nuevos
	}
	if (bytes_read < 0) // error en read
	{
		perror("Error");
		free(line);
		return (1);
	}
	if (!line) // si no se leyo nada, crea bufer vacio
	{
		line = malloc(1); //1 byte para '\0
		if (!line)
		{
			perror("Error");
			return (1);
		}
		line[0] = '\0'; //cadena vacia
	}
	else
		line[total_bytes] = '\0'; // cerramos la cadena

	ft_filter(line, total_bytes, argv[1]); //procesa y filtra contenido
	free(line);
	return (0);
}

/*
void	ft_filter(char *line, char *str)
{
	int	len = strlen(str);
	int	i = 0;
	int	j;

	while (line[i])
	{
		j = 0;
		while (str[j] && line[i + j] == str[j])
			j++;
		if (j == len) //si se encontro toda la palabra str
		{
			while (j > 0)
			{
				write(1, "*", 1);
				j--;
			}
			i += len; //salta los caracteres que reemplazamos
		}
		else
		{
			write(1, &line[i], 1);
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	char line[999999];
	int	bytes_read = 1;
	int	i = 0;

	if (argc != 2)
		return (1);
	while (bytes_read > 0)
	{
		bytes_read = read(0, &line[i], BUFFER_SIZE);
		if (bytes_read < 0)
		{
			perror ("Error:");
			return (1);
		}
		i += bytes_read;
	}
	line[i]= '\0';
	ft_filter(line, argv[1]);
	return(0);
}*/
