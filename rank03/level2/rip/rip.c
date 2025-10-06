#include <stdio.h>

// Función que calcula cuántos paréntesis están "mal colocados" en la cadena
// Devuelve la suma de paréntesis abiertos sin cerrar + paréntesis cerrados sobrantes
int invalid(char *s)
{
	int opened = 0;
	int closed = 0;

	for (int x = 0; s[x]; x++)
	{
		if (s[x] == '(')
			opened++;
		else if (s[x] == ')')
		{
			if (opened > 0)
				opened--;
			else
				closed++;
		}
	}
	return (opened + closed);
}

// Función recursiva que genera todas las combinaciones posibles
// quitando exactamente "to_remove" paréntesis para obtener cadenas válidas
void generate_result(char *s, int to_remove, int deleted, int pos)
{
	if (to_remove == deleted && !invalid(s))
	{
		puts(s);
		return;
	}
	while (s[pos])
	{
		if (s[pos] == '(' || s[pos] == ')')
		{
			char c = s[pos];
			s[pos] = ' ';
			generate_result(s, to_remove, deleted + 1, pos + 1);
			s[pos] = c;
		}
		pos++;
	}
}

// Función principal
int main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	int to_remove = invalid(av[1]);
	generate_result(av[1], to_remove, 0, 0);
	return (0);
}




























