#ifndef GNL
# define GNL


#include <stdlib.h> /* poner librería */
# include <unistd.h> /* poner librería */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

#endif
