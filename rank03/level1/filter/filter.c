/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:37:00 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/06 17:54:19 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#ifndef BUFFER_SIZE //Si No esta Definida
# define BUFFER_SIZE 10 //la Defino
#endif //final

// La función ft_filter reemplaza todas las apariciones de la cadena 'str'
// dentro de la cadena 'line' por asteriscos '*'. 
// Por ejemplo: ft_filter("hola mundo", "mundo") → "hola *****"

void	ft_filter(char *line, char *str)
{
	int i = 0;              // Índice para recorrer la cadena 'line'
	int len = strlen(str);  // Longitud de la cadena 'str', usada para comparar y para saber cuántos '*' escribir

	while (line[i]) // Recorre cada carácter de 'line' hasta llegar al final
	{
		int j = 0; // Índice para recorrer 'str' desde el principio en cada iteración

		// Comprueba si la subcadena en 'line' a partir de la posición i coincide con 'str'
		while (str[j] && line[i + j] == str[j])
			j++;

		// Si se ha recorrido toda 'str', significa que se ha encontrado una coincidencia completa
		if (j == len)
		{
			// Si hemos encontrado una coincidencia completa de 'str' dentro de 'line',
			// sustituimos esa palabra escribiendo un asterisco '*' por cada carácter.
			while (j > 0)
			{
				write(1, "*", 1); // Escribe un asterisco en la salida estándar.
				j--; // Decrementa 'j' hasta que llegue a 0 (un asterisco por cada letra de 'str').
			}
			// Avanza el índice 'i' hasta el final de la palabra sustituida
			i += len;
		}
		else
		{
			// Si no hay coincidencia, imprime el carácter actual tal cual
			write(1, &line[i], 1);
			i++;
		}
	}
}



int	main(int ac, char **av)
{
	char	line[999999];  // Buffer muy grande donde se guarda el texto leído
	int	bytes_read = 1; // Guarda el número de bytes leídos en cada llamada a 'read'
	int	i = 0; // Índice para ir llenando 'line' de manera secuencial

	// Comprobamos que hay exactamente 1 argumento (además del nombre del programa)
	// y que ese argumento no está vacío
	if (ac != 2)
		return (1); // Termina con el código de error 1

	// Leemos del descriptor 0 (stdin), es decir, lo que escriba el usuario
	while (bytes_read > 0)
	{
		bytes_read = read(0, &line[i], BUFFER_SIZE); // Leer un bloque de datos
		
		if (bytes_read < 0) // Si hay error
		{
			perror("Error:");
			return (1);
		}
		i += bytes_read;  // Avanza el índice para no pisar lo leído
	}
	line[i] = '\0';
	// Una vez leído todo el texto, aplicamos el filtro
	ft_filter(line, av[1]);
	return (0);
}

/*La lógica del programa es implementar un filtro que lea datos desde la entrada
 estándar (stdin), reemplace todas las apariciones de una cadena específica (s) 
 por asteriscos (*), y luego escriba el resultado en la salida estándar (stdout).

Aquí está el desglose de su funcionamiento:

1. Validación de argumentos
	- El programa verifica que se pase exactamente un argumento (además del nombre del
		programa) y que este argumento no esté vacío.
	- Si no se cumple esta condición, el programa retorna 1 como código de error.

2. Lectura de datos desde stdin
	- Usa un buffer (line) para leer bloques de datos desde la entrada estándar 
		mediante la función read.
	- Los datos se van acumulando en el buffer hasta que no haya más datos por leer 
		(read devuelve 0).
	- Si ocurre un error durante la lectura (read devuelve un valor negativo), el 
		programa muestra un mensaje de error usando perror y termina con un código 
		de error.

3. Reemplazo de la cadena
	- Una vez que se han leído todos los datos, el programa llama a la función 
		ft_filter.
	- La función ft_filter recorre el contenido del buffer (line) y busca 
		coincidencias con la cadena s:
		- Si encuentra una coincidencia completa, escribe un número de asteriscos 
			(*) igual a la longitud de s en la salida estándar.
		- Si no hay coincidencia, escribe el carácter actual de line en la salida 
			estándar.
	- Este proceso se repite hasta que se haya procesado todo el contenido de line.

4. Escritura en stdout
	- Los datos procesados (con las cadenas reemplazadas por asteriscos) se 
		escriben directamente en la salida estándar mediante la función write.

5. Manejo de errores
	- Si ocurre un error en read o en la asignación de memoria (si se usa memoria 
	dinámica), el programa muestra un mensaje de error en la salida de errores 
	estándar (stderr) y retorna 1.

Resumen:
El programa actúa como una versión simplificada del comando sed con la opción de 
reemplazo global (s/old/new/g), pero implementado en C. Su objetivo principal es 
demostrar el manejo de entrada/salida estándar, manipulación de cadenas y manejo 
de errores.


*/
