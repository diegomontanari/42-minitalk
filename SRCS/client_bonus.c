#include "minitalk_bonus.h"

/*
 * Signal handler for client confirmation.
 * Prints a message when a confirmation signal (SIGUSR1 or SIGUSR2) is received from the server.
 */
static void	ft_confirm(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("\033[0;32mQSL!\033[0;32m\n", 1);
	else
		ft_printf("\033[0;32mQSL!\033[0;32m\n", 1);
}

/*
 * Sends the bits of the character 'i' to the process with PID 'pid' using UNIX signals.
 * For each bit of the character, sends SIGUSR1 if the bit is 1, otherwise SIGUSR2.
 * Waits 100 microseconds between each signal to ensure correct delivery.
 */
void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

/*
 * Entry point for the bonus client program.
 * Expects two arguments: the server PID and the message to send.
 * Sets up confirmation signal handlers, then sends each character of the message
 * to the server by calling ft_send_bits. Sends a newline character at the end.
 * If the arguments are incorrect, prints an error message and usage instructions.
 */
int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			signal(SIGUSR1, ft_confirm);
			signal(SIGUSR2, ft_confirm);
			ft_send_bits(pid, argv[2][i]);
			i++;
		}
		ft_send_bits(pid, '\n');
	}
	else
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./client_bonus [PID] [MESSAGE]\033[0m\n");
		return (1);
	}
	return (0);
}