/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:18:30 by sle-guil          #+#    #+#             */
/*   Updated: 2017/03/08 12:36:15 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_data g_saved;

static void		*st_alloc_tall(size_t size)
{
	t_alloc		**ref;

	ref = &(g_saved.large.lst);
	while (*ref)
	{
		if ((*ref)->is_free && (*ref)->size >= size + sizeof(t_alloc))
			break ;
		ref = &((*ref)->next);
	}
	if (*ref)
		(*ref)->is_free = 0;
	else
	{
		(*ref) = mmap(NULL, PAGE_SIZE((size + sizeof(t_alloc))),\
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (*ref != MAP_FAILED)
		{
			ft_bzero(*ref, PAGE_SIZE((size + sizeof(t_alloc))));
			(*ref)->size = PAGE_SIZE((size + sizeof(t_alloc)));
		}
		else
			(*ref) = NULL;
	}
	return ((*ref) ? (*ref) + 1 : NULL);
}

static void		st_init_alloc(void)
{
	static char		init = 0;

	if (init)
		return ;
	init = 1;
	pthread_mutex_init(&(g_saved.lock), NULL);
	g_saved.tiny.size = PAGE_SIZE(((N + sizeof(t_alloc)) * ALLOC_NUM));
	g_saved.tiny.lst = mmap(NULL, g_saved.tiny.size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0);
	g_saved.tiny.lst->next = NULL;
	g_saved.tiny.lst->size = g_saved.tiny.size - sizeof(t_alloc);
	g_saved.tiny.lst->is_free = 1;
	g_saved.small.size = PAGE_SIZE(((M + sizeof(t_alloc)) * ALLOC_NUM));
	g_saved.small.lst = mmap(NULL, g_saved.small.size, PROT_READ | PROT_WRITE,\
		MAP_ANON | MAP_PRIVATE, -1, 0);
	g_saved.small.lst->next = NULL;
	g_saved.small.lst->size = g_saved.small.size - sizeof(t_alloc);
	g_saved.small.lst->is_free = 1;
	g_saved.large.lst = NULL;
}

static void		st_setup_alloc(t_alloc *ret, size_t size)
{
	void	*swap;

	swap = ret->next;
	ret->next = ((void*)ret) + size + sizeof(t_alloc);
	ret->next->next = swap;
	ret->next->is_free = 1;
	ret->next->size = ret->size - size - sizeof(t_alloc);
	ret->size = size;
}

static void		*st_add_small(t_alloc *lst, size_t size)
{
	t_alloc	*ret;

	ret = NULL;
	while (lst && !ret)
	{
		if (lst->next && lst->is_free && lst->next->is_free)
		{
			lst->size += lst->next->size + sizeof(t_alloc);
			lst->next = lst->next->next;
		}
		else if (lst->is_free && lst->size >= size)
			ret = lst;
		else
			lst = lst->next;
	}
	if (ret)
	{
		ret->is_free = 0;
		if (lst->size >= size + 2 * sizeof(t_alloc))
			st_setup_alloc(ret, size);
	}
	return ((void*)(ret) ? ret + 1 : NULL);
}

void			*malloc(size_t size)
{
	void	*ret;
	t_list	*list;

	st_init_alloc();
	pthread_mutex_lock(&(g_saved.lock));
	if (size >= M)
		ret = st_alloc_tall(size);
	else
	{
		list = &(g_saved.tiny);
		if (size >= N)
			list = &(g_saved.small);
		ret = st_add_small(list->lst, size);
	}
	pthread_mutex_unlock(&(g_saved.lock));
	if (!ret)
		errno = ENOMEM;
	return (ret);
}
