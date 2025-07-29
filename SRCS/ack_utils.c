#include "ack_utils.h"

volatile sig_atomic_t g_ack = 0;

void ack_handler(int sig)
{
    (void)sig;
    g_ack = 1;
}

void wait_for_ack(void)
{
    while (!g_ack)
        pause();
    g_ack = 0;
}

void send_ack(pid_t client_pid)
{
    kill(client_pid, SIGUSR1);
}

void install_ack_handler(void)
{
    signal(SIGUSR1, ack_handler);
}

void install_server_signal_handlers(void (*handler)(int, siginfo_t *, void *))
{
    struct sigaction sa;
    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
}