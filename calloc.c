/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 15:18:30 by sle-guil          #+#    #+#             */
/*   Updated: 2017/02/14 15:18:33 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	size_t	check;
	void	*ret;

	ret = NULL;
	check = count * size;
	if (!count || check / count == size)
		ret = malloc(check);
	if (ret)
		ft_bzero(ret, check);
	return (ret);
}
