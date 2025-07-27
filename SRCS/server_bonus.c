#include "minitalk_bonus.h"

/*
 * Signal handler for the bonus server.
 * Reconstructs a character from incoming SIGUSR1 and SIGUSR2 signals.
 * SIGUSR1 represents a bit value of 1, SIGUSR2 a bit value of 0.
 * When 8 bits are received, prints the resulting character and sends a confirmation
 * signal (SIGUSR2) back to the client using the sender's PID from siginfo_t.
 */
void	ft_handler(int signal, siginfo_t *info, void *s)
{
	static int	bit;
	static int	i;

	(void)info;
	(void)s;
	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
		kill(info->si_pid, SIGUSR2);
	}
}

/*
 * Entry point for the bonus server program.
 * Prints its PID and waits for messages from clients.
 * Sets up sigaction with ft_handler to receive bits and sender info.
 * Prints an error message if arguments are incorrect.
 */
int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./server\033[0m\n");
		return (0);
	}
	pid = getpid();
	ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
	ft_printf("\033[90mWaiting for a message...\033[0m\n");
	sig.sa_sigaction = ft_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
	return (0);
}