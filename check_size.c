/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:45:55 by sle-guil          #+#    #+#             */
/*   Updated: 2017/02/17 17:46:00 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void	count_alloc(void)
{
	size_t	count;
	t_alloc	*alloc;

	count = 0;
	alloc = g_saved.large.lst;
	while (alloc)
	{
		alloc = alloc->next;
		count++;
	}
	printf("%lu large, ", count);
	count = 0;
	alloc = g_saved.small.lst;
	while (alloc)
	{
		alloc = alloc->next;
		count++;
	}
	printf("%lu small, ", count);
	count = 0;
	alloc = g_saved.tiny.lst;
	while (alloc)
	{
		alloc = alloc->next;
		count++;
	}
	printf("%lu tiny\n", count);
}

void	check_size(void)
{
	t_alloc		*p;
	size_t		s;

	p = g_saved.tiny.lst;
	s = 0;
	while (p)
	{
		s += p->size + sizeof(t_alloc);
		p = p->next;
	}
	if (s != g_saved.tiny.size)
		printf("ERROR SIZE TINY %lu / %lu", s, g_saved.tiny.size);
	p = g_saved.small.lst;
	s = 0;
	while (p)
	{
		s += p->size + sizeof(t_alloc);
		p = p->next;
	}
	if (s != g_saved.small.size)
		printf("ERROR SIZE TINY %lu / %lu", s, g_saved.small.size);
}
