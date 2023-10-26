/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:37:38 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/07 02:06:13 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_bzero function is a function that sets the first n bytes of the memory
pointed to by s to zero. It does so by using a loop to iterate
over the n bytes of memory and setting each byte to zero
using a typecast to unsigned char *.
*/

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}
