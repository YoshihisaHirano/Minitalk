#include "../minitalk.h"

t_msg	g_msg = {};

void	send_ack(void)
{
	int		size;
	size_t	i;

	size = sizeof(size_t) * 8;
	while (size >= 0)
	{
		i = (g_msg.bit_qty >> size) & 1;
		if (i == 0)
			kill(g_msg.pid, SIGUSR1);
		else
			kill(g_msg.pid, SIGUSR2);
		usleep(40);
		size--;
	}
	g_msg.bit_qty = 0;
}

void	print_text(void)
{
	write(1, g_msg.text, g_msg.chr);
	if (g_msg.text[g_msg.chr - 1] == 0)
	{
		write(1, "\n", 1);
		usleep(300);
		send_ack();
	}
	ft_bzero(g_msg.text, g_msg.chr);
	g_msg.chr = 0;
}

void	decoder(int sig, siginfo_t *info, void *ucontext)
{
	char	i;

	(void) ucontext;
	g_msg.pid = info->si_pid;
	if (sig == SIGUSR1)
		i = 0;
	else
		i = 1;
	g_msg.bit_qty++;
	if (g_msg.bit_no != 0)
		g_msg.text[g_msg.chr] = g_msg.text[g_msg.chr] << 1;
	g_msg.text[g_msg.chr] |= i;
	if (g_msg.bit_no == 7)
	{
		g_msg.bit_no = 0;
		g_msg.chr++;
	}
	else
		g_msg.bit_no++;
	if ((g_msg.chr > 0 && g_msg.text[g_msg.chr - 1] == 0) || g_msg.chr
		== BUFF_SIZE - 1)
		print_text();
}

void	handle_sig(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = decoder;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}

int	main(void)
{
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	ft_bzero(g_msg.text, BUFF_SIZE);
	handle_sig();
	return (0);
}
