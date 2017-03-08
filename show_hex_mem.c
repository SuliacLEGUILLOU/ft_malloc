/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:48:47 by sle-guil          #+#    #+#             */
/*   Updated: 2017/02/20 16:48:49 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	st_print_area(char *ptr, size_t size)
{
	char	tab;
	char	c[2];
	size_t	i;

	tab = 1;
	i = 0;
	while (i++ < size && i < 65)
	{
		c[0] = (ptr[i] & 0xf0) >> 4;
		c[1] = (ptr[i] & 0x0f);
		c[0] += (c[0] < 10) ? '0' : 'A' - 10;
		c[1] += (c[1] < 10) ? '0' : 'A' - 10;
		write(1, c, 2);
		if (!(tab % 2))
			write(1, " ", 1);
		tab++;
		ptr++;
	}
}

static void	st_print(t_alloc *lst)
{
	write(1, "\n", 1);
	while (lst)
	{
		if (!(lst->is_free))
		{
			ft_putnbrhex((long)(lst + 1));
			write(1, " - ", 3);
			if (lst->next)
				ft_putnbrhex(((long)lst) + lst->size + sizeof(t_alloc));
			else
				write(1, "NULL\t\t", 6);
			write(1, " : ", 3);
			st_print_area((char*)(lst + 1), lst->size);
			write(1, "\n", 1);
		}
		lst = lst->next;
	}
}

void		show_hex_mem(void)
{
	pthread_mutex_lock(&(g_saved.lock));
	write(1, "TINY : ", 7);
	ft_putnbrhex((long)g_saved.tiny.lst);
	st_print(g_saved.tiny.lst);
	write(1, "SMALL : ", 8);
	ft_putnbrhex((long)g_saved.small.lst);
	st_print(g_saved.small.lst);
	write(1, "LARGE : ", 8);
	ft_putnbrhex((long)g_saved.large.lst);
	st_print(g_saved.large.lst);
	pthread_mutex_unlock(&(g_saved.lock));
}
