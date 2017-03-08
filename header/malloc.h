/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:46:20 by sle-guil          #+#    #+#             */
/*   Updated: 2017/02/17 17:46:24 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <errno.h>
# include <stddef.h>
# include <ctype.h>
# include <pthread.h>

# define N	513
# define M	4097

# define ALLOC_NUM	1024

# define PAGE_SIZE(x)	(x - x % (int)getpagesize() + (int)getpagesize())

typedef struct			s_alloc
{
	char			is_free;
	size_t 			size;
	struct s_alloc	*next;
}						t_alloc;

typedef struct 			s_list
{
	t_alloc			*lst;
	size_t			size;
}						t_list;

typedef struct			s_data
{
	t_list			tiny;
	t_list			small;
	t_list			large;
	pthread_mutex_t	lock;
}						t_data;


extern t_data		g_saved;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem(void);
void				show_hex_mem(void);

void				check_size(void);
int					is_alloc(void const *ref);
void				count_alloc(void);

void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_putnbrhex(long p);
void				ft_putnbr(size_t n);


void				*calloc(size_t count, size_t size);

#endif
