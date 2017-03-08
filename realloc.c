/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:44:49 by sle-guil          #+#    #+#             */
/*   Updated: 2017/02/17 17:45:08 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void			*st_norme(void *ptr, t_alloc *alloc, size_t size)
{
	void	*ret;

	ret = ptr;
	pthread_mutex_lock(&(g_saved.lock));
	if (alloc->size < M && size < M && alloc->next && alloc->size < size \
			&& alloc->size + alloc->next->size > size && alloc->next->is_free)
	{
		alloc->size += alloc->next->size + sizeof(t_alloc);
		alloc->next = alloc->next->next;
		pthread_mutex_unlock(&(g_saved.lock));
	}
	else if (alloc->size < size)
	{
		pthread_mutex_unlock(&(g_saved.lock));
		ret = malloc(size);
	}
	else
		pthread_mutex_unlock(&(g_saved.lock));
	return (ret);
}

void				*realloc(void *ptr, size_t size)
{
	void	*ret;
	t_alloc	*alloc;

	if (!ptr)
		return (malloc(size));
	alloc = (t_alloc*)ptr;
	alloc--;
	pthread_mutex_lock(&(g_saved.lock));
	if (!is_alloc(ptr))
	{
		pthread_mutex_unlock(&(g_saved.lock));
		return (NULL);
	}
	pthread_mutex_unlock(&(g_saved.lock));
	ret = st_norme(ptr, alloc, size);
	if (!ret)
		return (NULL);
	if (ret != ptr)
	{
		ft_memcpy(ret, ptr, (alloc->size < size) ? alloc->size : size);
		free(ptr);
	}
	return (ret);
}
