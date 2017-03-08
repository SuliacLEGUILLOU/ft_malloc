/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:07:35 by sle-guil          #+#    #+#             */
/*   Updated: 2017/02/14 16:07:46 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		st_ereaser_head(t_alloc *head)
{
	t_alloc		*lst;

	lst = g_saved.large.lst;
	if (head == lst)
		return (0);
	while (lst && lst->next != head)
		lst = lst->next;
	if (lst)
	{
		lst->next = head->next;
		return (1);
	}
	return (0);
}

void			free(void *ptr)
{
	t_alloc		*head;

	head = ptr;
	--head;
	pthread_mutex_lock(&(g_saved.lock));
	if (ptr && !is_alloc(ptr))
		errno = ENOMEM;
	else if (ptr && (head->is_free))
	{
		write(2, "ERROR, pointer already freed\n", 29);
		errno = ENOMEM;
	}
	else if (ptr)
	{
		head->is_free = 1;
		if (!(head->size % getpagesize()) && st_ereaser_head(head))
			munmap(head, head->size);
	}
	pthread_mutex_unlock(&(g_saved.lock));
}
