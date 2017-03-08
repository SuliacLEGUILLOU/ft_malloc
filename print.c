/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:49:01 by sle-guil          #+#    #+#             */
/*   Updated: 2017/02/20 16:49:07 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		st_putchar(int c)
{
	write(1, &c, 1);
}

static void		ft_puthex(long p)
{
	int hex;

	hex = (int)p & 0xf;
	if (hex < 10)
		st_putchar('0' + hex);
	else
		st_putchar('A' + hex - 10);
}

void			ft_putnbrhex(long p)
{
	if (p > 0)
		ft_putnbrhex(p >> 4);
	if (p == 0)
		write(1, "0x", 2);
	else
		ft_puthex(p);
}

void			ft_putnbr(size_t nbr)
{
	if (nbr < 10)
		st_putchar('0' + (int)nbr);
	else
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
}
