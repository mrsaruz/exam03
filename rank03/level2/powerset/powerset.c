/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:36:00 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/07 14:45:35 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Nombre del ejercicio : powerset
Archivos esperados   : *.c *.h
Funciones permitidas : atoi, printf, fprintf, malloc, calloc, realloc, free, 
stdout, write
--------------------------------------------------------------------------------

Escribe un programa que reciba como argumento un entero n seguido de un conjunto
s de enteros distintos.
Tu programa deberá mostrar todos los subconjuntos de s cuya suma de elementos 
sea igual a n.

El orden de las líneas no es importante, pero el orden de los elementos dentro 
de cada subconjunto sí debe coincidir con el orden del conjunto inicial s.
De esta manera, no habrá duplicados (por ejemplo: 1 2 y 2 1).

Por ejemplo, usando el comando:
Write a program that will take as argument an integer n followed by a set s of
distinct integers.
Your program should display all the subsets of s whose sum of elements is n.

./powerset 5 1 2 3 4 5
this output is valid:
1 4
2 3
5
this one is also valid:
2 3
5
1 4
but not this one:
4 1
3 2
5

En caso de error con malloc, tu programa deberá terminar con el código de 
salida 1.

No se probará con conjuntos inválidos (por ejemplo, 1 1 2).

Pista: El subconjunto vacío es un subconjunto válido de cualquier conjunto. 
Se mostrará como una línea vacía.


Ejemplos:

$> ./powerset 3 1 0 2 4 5 3 | cat -e
3$
0 3$
1 2$
1 0 2$
$> ./powerset 12 5 2 1 8 4 3 7 11 | cat -e
8 4$
1 11$
1 4 7$
1 8 3$
2 3 7$
5 7$
5 4 3$
5 2 1 4$
$> ./powerset 0 1 -1 | cat -e
$
1 -1$
$> ./powerset 7 3 8 2 | cat -e
*/

#include <stdio.h>
#include <stdlib.h>

// Función para imprimir un subconjunto basado en el array `path`
void	print_subset(int *set, int *path, int len)
{
	int i = 0;
	int first = 1;

	while (i < len)
	{
		if (path[i] == 1) // Si el elemento está incluido en el subconjunto
		{
			if (first == 0) // Imprime un espacio antes de los elementos excepto el primero
				printf(" ");
			printf("%d", set[i]); // Imprime el elemento
			first = 0;
		}
		i++;
	}
	printf("\n"); // Nueva línea al final del subconjunto
	return ;
}

// Función de retroceso (backtracking) para generar subconjuntos
void backtrack(int *set, int *path, int len, int i, int sum, int target)
{
	if (i == len) // Caso base: se procesaron todos los elementos
	{
		if (sum == target) // Si la suma coincide con el objetivo, imprime el subconjunto
			print_subset(set, path, len);
		return ;
	}

	// Incluye el elemento actual en el subconjunto
	path[i] = 1; 
	backtrack(set, path, len, i + 1, sum + set[i], target);
	
	// Excluye el elemento actual del subconjunto
	path[i] = 0;
	backtrack(set, path, len, i + 1, sum, target);
}

// Función principal
int	main(int ac, char **av)
{
	if (ac < 2) // Verifica que haya al menos un objetivo y un conjunto
		return (1);

	int	i = 0;
	int	target = atoi(av[1]); // Convierte el objetivo a entero
	int	len = ac - 2; // Longitud del conjunto
	int	*set = malloc(sizeof(int) * len); // Reserva memoria para el conjunto
	int	*path = calloc(len, sizeof(int)); // Reserva memoria para el arreglo `path`

	if (!set || !path) // Verifica errores de asignación de memoria
		return (1);
	while (i < len)
	{
		set[i] = atoi(av[i + 2]); // Convierte los argumentos a enteros y los almacena en `arr`
		i++;
	}
	backtrack(set, path, len, 0, 0, target); // Llama a la función de retroceso
	free(set); // Libera la memoria asignada a `arr`
	free(path); // Libera la memoria asignada a `path`
	return (0);
}


/* 
En el contexto del enunciado del ejercicio, un conjunto se refiere a una colección
de números enteros distintos que se pasan como argumentos al programa. Este 
conjunto es representado por los números que vienen después del primer argumento
(el objetivo n) en la línea de comandos.

Por ejemplo, si ejecutas el programa con el comando:

./powerset 5 1 2 3 4 5
	- El objetivo (n) es 5.
	- El conjunto (s) es {1, 2, 3, 4, 5}.

El programa debe trabajar con este conjunto para encontrar todos los subconjuntos
cuyos elementos sumen exactamente el valor del objetivo (n).
*/




