#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

int ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

void ft_swap(char *a, char *b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

int ft_strchr(const char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return 1; // Encontrado
		i++;
	}
	return 0; // No encontrado
}

// Ordena los caracteres de la cadena con un "bubble sort"
char *order_string(char *s)
{
	int len = ft_strlen(s);
	int flag = 1; 
	
	while (flag)
	{
		flag = 0;
		int i = 0;
		while (i < len - 1) 
		{
			if (s[i] > s[i + 1]) 
			{
				ft_swap(&s[i], &s[i + 1]);
				flag = 1; 
			}
			i++;
		}
	}
	return s;
}


// Genera todas las permutaciones posibles de los caracteres de "source"
void generate_permutations(char *source, char *result, int pos)
{
	int source_len = ft_strlen(source);
	if (pos == source_len)
	{
		puts(result);
		return;
	}

	int i = 0;
	while (i < source_len)
	{
		if (!ft_strchr(result, source[i]))
		{
			result[pos] = source[i];
			generate_permutations(source, result, pos + 1);
			result[pos] = '\0';
		}
		i++;
	}
}


int main(int ac, char **av)
{
	if (ac != 2)
		return 1;
	if (ft_strlen(av[1]) == 0 || (av[1][0] == ' ' && !av[1][1]))
		return 0;
	int i = 0;
	while (av[1][i])
	{
		if (!ft_isalpha(av[1][i]))
			return 0;
		i++;
	}
	int len = ft_strlen(av[1]);
	char *result = calloc(len + 1, sizeof(char));
	if (!result)
		return 1;
	char *source = order_string(av[1]);
	generate_permutations(source, result, 0);
	free(result);
	return 0;
}


/*
 * EJEMPLO DE EJECUCIÓN:
 * 
 * ./permutations abc
 * abc
 * acb  
 * bac
 * bca
 * cab
 * cba
 * 
 * PROCESO PARA "abc":
 * 1. Ordenar: "abc" (ya está ordenado)
 * 2. pos=0: Probar 'a', 'b', 'c'
 *    - Elegir 'a': result="a"
 *      - pos=1: Probar 'b', 'c' (no 'a' porque está usado)
 *        - Elegir 'b': result="ab"
 *          - pos=2: Probar 'c': result="abc" → IMPRIMIR
 *        - Elegir 'c': result="ac"  
 *          - pos=2: Probar 'b': result="acb" → IMPRIMIR
 *    - Elegir 'b': result="b"
 *      - Similar proceso...
 */



/*
 * PUNTOS CLAVE PARA EL EXAMEN:
 * 
 * 1. ORDEN ALFABÉTICO:
 *    - CRUCIAL ordenar el string antes de generar permutaciones
 *    - Sin ordenamiento, no se garantiza orden alfabético
 *    - Usar algoritmo de ordenamiento simple pero correcto
 * 
 * 2. BACKTRACKING EFICIENTE:
 *    - Usar array de caracteres usados para verificación O(n)
 *    - Marcar/desmarcar caracteres correctamente
 *    - No olvidar limpiar estado al retornar
 * 
 * 3. GESTIÓN DE MEMORIA:
 *    - Alocar buffer para permutación actual
 *    - Usar calloc() para inicializar a '\0'
 *    - Liberar memoria al finalizar
 * 
 * 4. VALIDACIÓN ROBUSTA:
 *    - Verificar número de argumentos
 *    - Validar que solo contiene letras
 *    - Manejar casos especiales (string vacío, espacios)
 * 
 * 5. OPTIMIZACIONES:
 *    - Para strings con caracteres duplicados, usar algoritmo diferente
 *    - Para strings muy largos, considerar algoritmo de Heap
 *    - Evitar regenerar permutaciones duplicadas
 */
