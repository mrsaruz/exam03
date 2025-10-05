/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:58:15 by adruz-to          #+#    #+#             */
/*   Updated: 2025/10/02 18:58:30 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

void	ft_putnbr(int n)
{
    char	c;
    if (n > 9)
        ft_putnbr(n / 10);
    c = n % 10 + '0';
    write(1, &c, 1);
}

void	print_board(int *board, int n, int i) //una vez se han colocado todas la reinas, se imprime solucion
{
    if (i == n) //significa que ya recorrimos todas las filas, entonces se imprimieron todas las filas
    {
        write(1, "\n", 1); //i es el índice de fila que estás imprimiendo en ese momento.
        return;
    }
    ft_putnbr(board[i]); //Imprime la columna donde está la reina en la fila i
    if (i < n - 1) //Si no estamos en la última fila
		write(1, " ", 1);// imprimimos un espacio entre números (opcional, por formato).
    print_board(board, n, i + 1); //Llamada recursiva para imprimir la siguiente fila.
}                               

int	is_valid(int *board, int row, int col) //board tablero
{
    int	i;

    i = 0;
    if (row == 0) //en primera fila siempre es valido porq podemos colocarla en cualquier columna
        return (1);
    while (i < row) //i es indice para recorrer filas anteriores para que no choquen
    {
        if (board[i] == col //misma columna
			|| board[i] - i == col - row //misma diagonal descendente
			|| board[i] + i == col + row) //misma diagonal ascendente
            return (0); //invalido
        i++;
    }
    return (1); //La posición (row, col) es segura para colocar la nueva reina.
}

void	nqueen_col(int n, int *board, int row, int col)
{
    if (col == n) //si ya probamos todas las columnas
        return ;
    if (is_valid(board, row, col)) //se verifica si es valido colocar una reina en la col de ls fila row
    {
        board[row] = col; //Se guarda la columna en la que se colocará la reina para la fila row
        nqueen(n, board, row + 1);//Avanzas hacia la siguiente fila
    }
    nqueen_col(n, board, row, col + 1); //Esto hace que pruebes la siguiente columna en la fila actual (row).
}


void	nqueen(int n, int *board, int row)
{
    if (row == n) //si ya colocaste todas las reinas (row == n), imprimes el tablero (solucion encontrada)
    {
        print_board(board, n, 0);
        return;
    }
    nqueen_col(n, board, row, 0); //Si no, llamas a nqueen_col para probar columnas (desde la col 0) en la fila actual
}


int	main(int ac, char **av)
{
    int	n; //n es num reinas y determina tamaño tablero nxn
    int	*board;

    if (ac != 2) //Verificamos que el programa haya recibido 1 argumento (además del nombre del programa).
        return (1);
    n = atoi(av[1]); //convertimos argumento a entero
    if (n < 1) //nos aseguramos que el valor sea valido
        return (1);
    board = malloc(sizeof(int) * n); //tamaño del tablero
    if (!board)
        return (1);
    nqueen(n, board, 0); //nqueen en row = 0 llama a nqueen_col para probar todas las columnas de la fila 0.
    free(board); //limpia la memoria al terminar
    return (0);
}