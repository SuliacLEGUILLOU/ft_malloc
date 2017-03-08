/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:18:30 by sle-guil          #+#    #+#             */
/*   Updated: 2017/02/14 15:18:33 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	st_iter(t_alloc *lst, t_alloc const *ref)
{
	ref--;
	while (lst)
	{
		if (ref == lst)
		{
			if (lst->is_free)
				return (-1);
			else
				return (1);
		}
		else if (lst->next && lst < ref && ref < lst->next)
			return (-1);
		lst = lst->next;
	}
	return (0);
}

static int	st_iter_tall(t_alloc *lst, t_alloc const *ref)
{
	ref--;
	while (lst)
	{
		if (ref == lst)
		{
			if (lst->is_free)
				return (-1);
			else
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}

int		is_alloc(void const *ref)
{
	int		ret;

	ret = st_iter(g_saved.tiny.lst, ref);
	if (!ret)
		ret = st_iter(g_saved.small.lst, ref);
	if (!ret)
		ret = st_iter_tall(g_saved.large.lst, ref);
	return ((ret == 1) ? 1 : 0);
}