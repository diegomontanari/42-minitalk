/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ack_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:47:26 by dmontana          #+#    #+#             */
/*   Updated: 2025/09/25 16:47:31 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACK_UTILS_H
# define ACK_UTILS_H

# include <signal.h>
# include <unistd.h>

void	install_ack_handler(void);
void	wait_for_ack(void);
void	send_ack(pid_t client_pid);
void	install_server_signal_handlers(void (*handler)(int, siginfo_t *,
				void *));

#endif
