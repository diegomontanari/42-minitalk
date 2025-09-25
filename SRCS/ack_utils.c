/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ack_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:52:37 by dmontana          #+#    #+#             */
/*   Updated: 2025/09/25 16:52:39 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ack_utils.h"

volatile sig_atomic_t	g_ack = 0;
/* g_ack is declared as 'volatile sig_atomic_t' because:
 *
 * 1. sig_atomic_t (defined in <signal.h>) ensures atomic access: reading or
 *     writing the variable is indivisible, so a signal handler can't interrupt
 *     in the middle of an update and produce a corrupted value.
 *

* 2. volatile (keyword in C) tells the compiler not to optimize accesses to this
*    variable,
 *   because it can be modified asynchronously by a signal handler. Without
 *   volatile, the compiler might assume the value never changes on its own,
 *   leading to infinite loops or stale reads.
 *
 * In short, 'volatile sig_atomic_t' is the standard pattern for safely
 * communicating between normal code and a signal handler. */

void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

/* Using `while (!g_ack) pause();` can lead to a race condition:
 * if the signal arrives after checking !g_ack but before pause() is called,
 * the process might block indefinitely because the ack was already consumed.
 * A more robust POSIX approach is to block the signal and use sigsuspend()
 * to wait atomically, avoiding this race window. */
void	wait_for_ack(void)
{
	while (!g_ack)
		pause();
	g_ack = 0;
}

void	send_ack(pid_t client_pid)
{
	kill(client_pid, SIGUSR1);
}
/*
 * install_ack_handler() is a helper function that sets up the signal handler

* for acknowledgements (acks). It takes no parameters and simply
* tells the system:
* "when SIGUSR1 is received, execute the ack_handler function".

 * signal(SIGUSR1, ack_handler) sets ack_handler as the handler for SIGUSR1.
 * This is the older API: it works but has limitations, such as possibly
 * resetting the handler after the first signal and lacking extra info
 * (like sender PID). For more robust handling, sigaction() is preferred.
 */

void	install_ack_handler(void)
{
	signal(SIGUSR1, ack_handler);
}
/*

install_server_signal_handlers() sets up a robust signal handler
for SIGUSR1 and SIGUSR2.

- A sigaction struct 'sa' (defined in signal.h) is used to define
  how signals are handled.

- sa.sa_sigaction = handler sets the handler function (3-argument version)
to receive extra info like sender PID.

- sa.sa_flags = SA_SIGINFO enables the 3-argument handler mode.

- sigemptyset(&sa.sa_mask) ensures no signals are blocked while
  handling a signal.
 
 - sigaction(SIGUSR1, &sa, NULL) and sigaction(SIGUSR2, &sa,
	NULL) register the same handler for both signals.
 
 * In Minitalk, SIGUSR1 represents bit 0 and SIGUSR2 represents bit 1.
 * Using siginfo_t, the server knows which client sent each signal 
 * and can send back acknowledgements.
 */

void	install_server_signal_handlers(void (*handler)(int, siginfo_t *,
			void *))
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}
