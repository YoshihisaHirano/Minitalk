#include "../minitalk.h"

t_msg	g_msg = {};

void	error_exit(int code)
{
	if (code == 1)
		ft_putstr_fd("The server's id is invalid\n", 2);
	if (code == 2)
		ft_putstr_fd("Please specify the server's id AND the message\n", 2);
	exit(1);
}

void	transfer_msg(char *text)
{
	char	i;

	while (g_msg.chr <= ft_strlen(text))
	{
		while (g_msg.bit_no < 8)
		{
			i = (text[g_msg.chr] >> (7 - g_msg.bit_no)) & 1;
			if (i == 0)
				kill(g_msg.pid, SIGUSR1);
			else
				kill(g_msg.pid, SIGUSR2);
			usleep(40);
			g_msg.bit_no++;
		}
		g_msg.bit_no = 0;
		g_msg.chr++;
	}
	g_msg.bit_no = 0;
}

void	decode_num(int sig, siginfo_t *info, void *ucontext)
{
	int	i;

	(void)ucontext;
	if (info->si_pid == g_msg.pid)
	{
		if (sig == SIGUSR1)
			i = 0;
		else
			i = 1;
		g_msg.bit_qty |= i;
		g_msg.bit_qty = g_msg.bit_qty << 1;
		g_msg.bit_no++;
		if (g_msg.bit_no == g_msg.bit_len)
			g_msg.closed = 1;
	}
}

void	handle_ack(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = decode_num;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (!g_msg.closed)
		pause();
}

int	main(int argc, char **argv)
{
	char	*text;
	size_t	bit_size;

	if (argc >= 3)
	{
		g_msg.pid = ft_atoi(argv[1]);
		if (g_msg.pid == 0)
			error_exit(1);
		text = argv[2];
		bit_size = (ft_strlen(text) * 8) + 8;
		transfer_msg(text);
		g_msg.bit_len = sizeof(g_msg.bit_qty) * 8;
		handle_ack();
		if (g_msg.bit_qty == bit_size)
			ft_putstr_fd("Everything was delivered successfully!\n", 1);
		else
			ft_putstr_fd("Something went wrong.\n", 1);
	}
	else
		error_exit(2);
	return (0);
}
