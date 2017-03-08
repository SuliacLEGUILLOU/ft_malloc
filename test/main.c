/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sle-guil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 17:52:31 by sle-guil          #+#    #+#             */
/*   Updated: 2017/03/08 16:28:09 by sle-guil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int main()
{
	char	*ptr, *ptr1, *ptr2, *ptr3;
	char	*tab[10240];

	ptr = malloc(5);
	printf("%p\n", (void*)ptr);
	free(ptr);
	int 	count = 0;

	ptr = malloc(5);
	ptr = malloc(5);
	ptr1 = malloc(5);
	ptr2 = malloc(5);
	free(ptr1);
	free(ptr);

	// The following line have to deadlock the program
	// pthread_mutex_lock(&(g_saved.lock));

	ptr3 = malloc(30);

	if (ptr3 != ptr)
		printf("Error while defrag\n");

	for (size_t i = 0; i < 500; i++)
	{
		ptr1 = ptr;
		ptr = malloc(i % 129);
		if (ptr && !(rand() % 3)) {
			free(ptr);
			ptr = NULL;
		}
		else if (ptr1 && !(rand() % 2))
			free(ptr1);
		else if (!ptr)
			printf("Should break here %d\n", count++);
	}
	check_size();

	for (size_t i = 0; i < 1024; ++i)
	{
		ptr = malloc(1024 + (size_t)(rand() % 10000));
		//printf("%p\n", ptr);
		free(ptr);
	}

	malloc(0);

	int		r;
	for (size_t i = 0; i < 1024; ++i) {
		//tab[i] = NULL;
		tab[i] = calloc((size_t) rand() % 100, 1);
		tab[i][0] = 'a';
		if (tab[i] && !is_alloc(tab[i]))
			write(1, "nope\n", 5);
	}
	//for (size_t i = 1023; i > 0; --i)
	//	free(tab[i]);
	for (size_t i = 0; i < 1000000; ++i)
	{
		r = rand() % 2048;
		if (!(rand() % 3)) {
			free(tab[r]);
			tab[r] = NULL;
		} else {
			tab[r] = realloc(tab[r], (size_t)rand() % 1024);
		}
		if (tab[r] && is_alloc(tab[r]) < 1)
			write(1, "nope\n", 5);
		if (!(i % 100000) && i)
			printf("%lu\n", 1000000 / i);
		check_size();
	}



	ptr = calloc(5, 5);
	//realloc(ptr + 5, 1000);
	free(ptr);
	if (calloc(5000000000, 500000000))
		printf("Probleme check size calloc\n");
	if (calloc(5000000000000000000, 500000000000000000))
		printf("Probleme check size calloc\n");
	check_size();

	//show_alloc_mem();
	//show_hex_mem();
	//printf("%lu, %lu\n", sizeof(size_t), sizeof(unsigned long int));

	return (0);
}
