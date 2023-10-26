/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:37:42 by jeremy            #+#    #+#             */
/*   Updated: 2023/04/20 14:44:39 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_calloc function allocates a block of memory for an array
of count elements, each of size bytes, and initializes the memory to zero.
It first checks for potential overflow by comparing count and
size with the maximum possible value of a size_t.
If either is equal to SIZE_MAX, the function returns NULL to indicate an error.

If the allocation is successful, ft_calloc then uses malloc to allocate
the requested amount of memory and returns a pointer to
the first byte of the allocated memory. It then uses ft_bzero to set
all the bytes in the allocated memory block to zero.
*/

#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	p = (void *)malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}
