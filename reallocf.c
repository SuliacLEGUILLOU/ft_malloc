/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:45:35 by sle-guil          #+#    #+#             */
/*   Updated: 2017/02/17 17:45:37 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				*reallocf(void *ptr, size_t size)
{
	void	*ret;

	ret = realloc(ptr, size);
	if (!ret)
		free(ptr);
	return (ret);
}
