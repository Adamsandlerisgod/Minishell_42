/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:07:53 by jhurpy            #+#    #+#             */
/*   Updated: 2023/05/07 02:15:21 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_realloc function takes in a pointer to a block of memory allocated
using malloc, the size of the block of memory, and the new size that
is being requested. If the pointer is NULL, the function returns a pointer
to a new block of memory allocated using malloc with the requested size.
If the requested size is zero, the function frees the block of memory and
returns NULL.

If the requested size is greater than the old size,
the function allocates a new block of memory using malloc with
the requested size, copies the old data to the new block, and frees
the old block of memory. If the requested size is less than or equal
to the old size, the function allocates a new block of memory with
the requested size, copies the data from the old block up to the requested size,
and frees the old block of memory.

The function returns a pointer to the new block of memory allocated.
*/

#include <stddef.h>
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	void			*new_ptr;
	unsigned char	*src;
	unsigned char	*dst;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	src = (unsigned char *)ptr;
	dst = (unsigned char *)new_ptr;
	if (old_size <= size)
		size = old_size;
	while (size--)
		*dst++ = *src++;
	free(ptr);
	return (new_ptr);
}
