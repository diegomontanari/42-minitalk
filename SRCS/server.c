#include "minitalk.h"
#include "ack_utils.h"

/*
 * Signal handler for the server.
 * Reconstructs a character from incoming SIGUSR1 and SIGUSR2 signals.
 * SIGUSR1 represents a bit value of 1, SIGUSR2 a bit value of 0.
 * When 8 bits are received, prints the resulting character.
 */
void ft_handler(int signal, siginfo_t *info, void *context)
{
    static int bit;
    static int i;
    (void)context;
    if (signal == SIGUSR1)
        i |= (0x01 << bit);
    bit++;
    if (bit == 8)
    {
        ft_printf("%c", i);
        bit = 0;
        i = 0;
    }
    send_ack(info->si_pid);
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
    install_server_signal_handlers(ft_handler);
    while (1)
        pause();
    return (0);
}