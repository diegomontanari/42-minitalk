#include "minitalk.h"
#include "ack_utils.h"

/*
One char s made of 8 bits.
---
if -> Se il bit alla posizione 'bit' è 1 manda (kill) SIGUSR1 al processo con PID 'pid'
else -> manda (kill) SIGUSR2 al processo con PID 'pid'
---
Waits 100 microseconds between each signal to ensure correct delivery.
-> int usleep(useconds_t microseconds) -> definita in <unistd.h>
serve a introdurre ritardi controllati in programmi che gestiscono segnali, thread, 
I/O o comunicazione fra processi per lasciare il tempo al sistema 
operativo di processare altri eventi.
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
		
		wait_for_ack();
		bit++;
	}
}

/*
Entry point for the client program.
Expects two arguments: the server PID and the message to send.
Converts the PID from string to integer, then sends each character of the message
to the server by calling ft_send_bits. Sends a newline character at the end.
If the arguments are incorrect, prints an error message and usage instructions.
 */
int main(int argc, char **argv)
{
    int pid;
    int i;

    install_ack_handler(); // <--- Mettila qui!

    i = 0;
    if (argc == 3)
    {
        pid = ft_atoi(argv[1]);
        while (argv[2][i] != '\0')
        {
            ft_send_bits(pid, argv[2][i]);
            i++;
        }
        ft_send_bits(pid, '\n');
    }
    else
    {
        ft_printf("\033[91mError: wrong format.\033[0m\n");
        ft_printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
        return (1);
    }
    return (0);
}