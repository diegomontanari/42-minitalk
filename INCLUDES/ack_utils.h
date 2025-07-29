#ifndef ACK_UTILS_H
#define ACK_UTILS_H

#include <signal.h>
#include <unistd.h>

void install_ack_handler(void);
void wait_for_ack(void);
void send_ack(pid_t client_pid);
void install_server_signal_handlers(void (*handler)(int, siginfo_t *, void *));

#endif