/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:28:02 by dmontana          #+#    #+#             */
/*   Updated: 2025/02/26 14:28:06 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// Stampa un carattere e aggiorna il contatore
void	ft_print_char(const char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_print_low_hex(unsigned int nbr_hex, int *count)
{
	unsigned long	n;

	n = nbr_hex;
	ft_print_nbr_base(n, "0123456789abcdef", count);
}

void	ft_print_up_hex(unsigned int nbr_hex, int *count)
{
	unsigned long	n;

	n = nbr_hex;
	ft_print_nbr_base(n, "0123456789ABCDEF", count);
}
