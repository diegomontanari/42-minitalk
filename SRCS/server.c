#include "minitalk.h"

/*
 * Signal handler for the server.
 * Reconstructs a character from incoming SIGUSR1 and SIGUSR2 signals.
 * SIGUSR1 represents a bit value of 1, SIGUSR2 a bit value of 0.
 * When 8 bits are received, prints the resulting character.
 */
void	ft_handler(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}

/*
 * Entry point for the server program.
 * Prints its PID and waits for messages from clients.
 * Sets up signal handlers for SIGUSR1 and SIGUSR2 to receive bits.
 * Prints an error message if arguments are incorrect.
 */
int	main(int argc, char **argv)
{
	int	pid;

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
	while (argc == 1)
	{
		signal(SIGUSR1, ft_handler);
		signal(SIGUSR2, ft_handler);
		pause ();
	}
	return (0);
}