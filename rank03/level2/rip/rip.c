/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 11:33:52 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/08 15:00:31 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Nombre del ejercicio: rip
Archivos esperados: *.c *.h
Funciones permitidas: puts, write
-------------------------------------------------------------------------------
Escribe un programa que reciba como argumento una cadena que contenga únicamente 
paréntesis.

Si los paréntesis no están balanceados (por ejemplo "())"), tu programa deberá 
eliminar el mínimo número de paréntesis necesario para que la expresión quede 
balanceada.

Eliminar significa reemplazar por espacios.

Después deberás imprimir todas las soluciones posibles (pueden ser más de una).

El orden de las soluciones no es importante.

Ejemplos:
$> ./rip '(()' | cat -e
 ()$
( )$

$> ./rip '((()()())())' | cat -e
((()()())())$

$> ./rip '()())()'| cat -e
()() ()$
()( )()$
( ())()$

$> ./rip '(()(()(' | cat -e
(()  ) $
( )( ) $
( ) () $
 ()( ) $
 () () $
*/

#include <stdio.h>

/* Función que calcula cuántos paréntesis están "mal colocados" en la cadena.
Devuelve la suma de paréntesis abiertos sin cerrar + paréntesis cerrados 
sobrantes */

int invalid(char *s)
{
	int open = 0; // Contador de paréntesis abiertos '(' no cerrados aún
	int close = 0; // Contador de paréntesis de cierre ')' que sobran
	int i = 0; // Índice para recorrer la cadena
	
	while (s[i]) // Mientras no lleguemos al final de la cadena
	{
		if (s[i] == '(')
			open++; // Si encontramos un '(', incrementamos el contador de abiertos
		else if (s[i] == ')')
		{
			if (open > 0)
				open--; // Si hay un '(' disponible, lo emparejamos y reducimos 'open'
			else
				close++; // Si no hay ningún '(', este ')' está desbalanceado
		}
		i++; // Pasamos al siguiente carácter
	}
	return (open + close); // Su suma son los paréntesis inválidos
}

/* Función recursiva que genera todas las combinaciones posibles
 quitando exactamente "to_remove" paréntesis para obtener cadenas válidas 
 
 Parámetros:
	- s: cadena de entrada (se modifica temporalmente durante la recursión)
	- to_remove: número total de paréntesis que deben eliminarse
	- deleted: número de paréntesis eliminados hasta el momento
	- pos: posición actual en la cadena desde donde seguimos procesando
 */

void generate_result(char *s, int remove, int deleted, int pos)
{
	// Caso base:
	// Si ya hemos eliminado la cantidad necesaria de paréntesis
	// y la cadena resultante es válida (sin desbalanceo), la mostramos.
	if (remove == deleted && !invalid(s))
	{
		puts(s); // Imprime la cadena resultante
		return;
	}
	// Recorremos la cadena desde la posición 'pos'
	while (s[pos])
	{
		// Solo consideramos eliminar si el carácter es un paréntesis
		if (s[pos] == '(' || s[pos] == ')')
		{
			char c = s[pos]; // Guardamos el carácter original
			s[pos] = ' '; // Lo "eliminamos" temporalmente sustituyéndolo por un espacio
			// Avanzamos a la siguiente posición, aumentando el contador de eliminados
			generate_result(s, remove, deleted + 1, pos + 1);
			s[pos] = c; // Restauramos el carácter original tras volver de la recursión
		}
		pos++; // Pasamos al siguiente carácter
	}
}

// Función principal
int main(int ac, char **av)
{
	if (ac != 2) // Comprobamos que haya un solo argumento
		return (1); // Si no, salimos con código de error

	// Calculamos cuántos paréntesis hay que eliminar para que la cadena sea válida
	int remove = invalid(av[1]);
	// Genera y muestra las combinaciones válidas de la cadena
	generate_result(av[1], remove, 0, 0);
	return (0);
}




























