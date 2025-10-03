#include <unistd.h>
#include <stdio.h>
#include <string.h>
#ifndef BUFFER_SIZE //Si No esta Definida
# define BUFFER_SIZE 10 //la Defino
#endif //final

void	ft_filter(char *line, char *str)
{
	int	len = strlen(str);   // Calcula la longitud de la cadena 'str'
	int	i = 0;               // Índice para recorrer 'line'

	while (line[i])           // Mientras no lleguemos al final de 'line'
	{
		int	h = 0;           // Índice para comparar con 'str'

		// Compara carácter a carácter 'line' con 'str'
		while (str[h] && line[i + h] == str[h])
			h++;

		if (h == len)          // Si se encontró toda la palabra 'str'
		{
			// Escribe en su lugar tantos '*' como la longitud de 'str'
			while (h > 0)
			{
				write (1, "*", 1);
				h--;
			}
			i += len;           // Salta los caracteres que reemplazamos
		}
		else                   // Si no hay coincidencia
		{
			// Escribe el carácter actual de 'line'
			write (1, &line[i], 1);
			i++;
		}
	}
}


int	main(int argc, char **argv)
{
	char	line[999999];  // Buffer muy grande donde se guarda lo leído
	int	bytes_read = 1;       // Guarda lo que devuelve 'read'
	int	i = 0;         // Índice para ir llenando 'line'

	// Comprobamos que hay exactamente 1 argumento (además del nombre del programa)
	// y que ese argumento no está vacío
	if (argc != 2)
		return (1);

	// Leemos del descriptor 0 (stdin), es decir, lo que escriba el usuario
	while (bytes_read > 0)
	{
		bytes_read = read(0, &line[i], BUFFER_SIZE); // Leer un bloque de datos
		if (bytes_read < 0)                          // Si hay error
		{
			perror("Error:");
			return (1);
		}
		i += bytes_read;  // Avanza el índice para no pisar lo leído
	}
	line[i] = '\0';
	// Una vez leído todo el texto, aplicamos el filtro
	ft_filter(line, argv[1]);
	return (0);
}

