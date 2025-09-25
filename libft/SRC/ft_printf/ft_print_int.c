/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:28:53 by dmontana          #+#    #+#             */
/*   Updated: 2025/02/26 14:28:58 by dmontana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// in ft_print_nbr_base((unsigned long)n, "0123456789", count);
// -> Once the minus is removed, I proceed with the decimal base

void	ft_print_int(int nbr, int *count)
{
	long	n;

	n = nbr;
	if (nbr == -2147483648)
	{
		ft_print_str("-2147483648", count);
		return ;
	}
	if (nbr < 0)
	{
		n = -nbr;
		ft_print_char('-', count);
	}
	ft_print_nbr_base((unsigned long)n, "0123456789", count);
}

// ft_print_nbr_base(n, "0123456789", count);
// Same thing but the check of the sign is useless

void	ft_print_uns_int(unsigned int nbr, int *count)
{
	unsigned long	n;

	n = nbr;
	ft_print_nbr_base(n, "0123456789", count);
}
