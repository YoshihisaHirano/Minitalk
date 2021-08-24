#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include "utils/utils.h"
# define BUFF_SIZE 1024

typedef struct s_msg
{
	size_t	bit_no;
	size_t	chr;
	char	text[BUFF_SIZE];
	int		closed;
	size_t	bit_qty;
	size_t	bit_len;
	int		pid;
}	t_msg;

#endif