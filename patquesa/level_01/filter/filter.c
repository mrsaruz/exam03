/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:28:52 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/02 18:28:55 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096   /*tamaño típico de una página de memoria en muchos sistemas UNIX/Linux*/
#endif

// Compara manualmente pattern con data para ver si hay coincidencia con el patrón
int is_match(const char *data, size_t i, size_t len, const char *pattern, size_t pat_len)
{
    if (i + pat_len > len) //Si desde la posición i No hay espacio suficiente para comparar pat_len caracteres
        return 0;          //i es la posicion actual en el texto

    size_t j = 0; //indice para recorrer el patron
    while (j < pat_len && data[i + j] == pattern[j])
    {
        j++; //avanza mientras coincida y no se acabe el patron (j < pat_len)
    }
	if (j == pat_len)
        return 1; // Si hay Coincidencia completa, return 1
    return 0; //else
    //return (j == pat_len); versión corta d lo anterior
}

void replace_and_write(char *data, size_t len, const char *pattern, size_t pat_len)
{
    size_t i = 0; //iterador de len (data)
	//UNO.- desde la posición i, hay espacio suficiente para comparar el patrón completo: 2 CASOS
    while (i + pat_len <= len) 
	{  //1) SI hay coincidencia, reemplazamos por ****
        if (is_match(data, i, len, pattern, pat_len))
		{
            size_t j = 0; //iterador de pat_len
            while (j < pat_len)
			{
                write(1, "*", 1);
                j++;
            }
            i += pat_len; //avanzar el índice i tantas posiciones como la longitud del patrón (pat_len)
        } //2) NO hay coincidencia
		else // solo imprimimos
		{
            write(1, &data[i], 1);
            i++;
        }
    }//DOS.- cd i + pat_len > len //es d, No hay espacio para comparar patron. Se Imprime simplemente
    write(1, data + i, len - i);
}

int main(int argc, char **argv)
{
    if (argc != 2 || argv[1][0] == '\0') //Si no hay exactamente 1 argumento o si el argumento es una cadena vacía
        return 1;

    const char *pattern = argv[1]; //PATTERN patron
    size_t pat_len = strlen(pattern);
    
    char *stash = NULL; //STASH guarda lo que quedó sin procesar de la lectura anterior
    size_t stash_len = 0; 
    char buf[BUFFER_SIZE]; //BUF es el buffer principal donde guardamos lo leído con read
    ssize_t r = read(0, buf, BUFFER_SIZE); //Lee (read) hasta BUFFER_SIZE bytes y lo guarda en buf (buffer temporal) 
    while (r > 0) // r > 0: se leyó bien; r == 0: EOF (fin de archivo); r < 0: error;
	{
        size_t total_len = stash_len + r; //TOTAL_LEN = contenido anterior mas lo que se acaba d leer
        char *data = malloc(total_len); //DATA es un puntero a un bloque de MEMORIA para total_len (lo q quedo del buffer anterior y lo q se acaba de leer)
        if (!data)
		{
            perror("Error malloc"); //imprime mensaje de error
            free(stash); //liberas lo q estaba guardado
            return 1;
        }
        if (stash) //si quedaron datos pendientes del bucle anterior (stash), se COPIAN a data
            memmove(data, stash, stash_len);
        memmove(data + stash_len, buf, r); //a cont. se AÑADEN en data los que se acaban de leer (buf)
        free(stash); //liberas stash. Ahora esta todo en data.
        stash = NULL;
        
        size_t safe_len; //SAFE_LEN desde donde podemos hacer comparaciones seguras y completas con el patron
		if (total_len >= pat_len)
			safe_len = total_len - pat_len + 1;//total_len - pat_len te da la última posición de inicio válida. +1 pq son num intentos (no indices)
		else
			safe_len = 0;
             
        replace_and_write(data, safe_len, pattern, pat_len); //llama a is_match para comprobar coincidencia y si hay, reemplaza por *
        
        stash_len = total_len - safe_len; // stash_len = RESTO (lo que queda para la ss vuelta)
        if (stash_len > 0) 
        {
            stash = malloc(stash_len); //reservamos MEMORIA PARA RESTO (stash) q no pudimos procesar para una comparacion completa del patron
            if (!stash)
            {
                perror("Error malloc stash");
                free(data);
                return 1;
            }
            memmove(stash, data + safe_len, stash_len); //Copiamos stash_len bytes RESTO q estan despues de safe_len en data, y los guarda en stash.
        }
        free(data);
    }
    if (r < 0) //si hubo un error de lectura
    {
        perror("Error read"); //imprime error
        free(stash); //si habia algo guardado, se libera
        return 1; //codigo error
    }
    if (stash && stash_len > 0) //si existe algo en stash y tiene al menos 1 byte que se quedo sin procesar (ultima vuelta)
        replace_and_write(stash, stash_len, pattern, pat_len); //lo procesamos (si no hay un bloque suficiente simplemente los imprimera)
    free(stash); //Libera la memoria reservada para stash después de haberla usado por última vez.
    return 0; //termino con exito
}