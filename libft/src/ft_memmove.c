/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:39:03 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/07 16:13:54 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_memmove copies len bytes from the string src to string dst.
The two strings may overlap, the copy is always done in a non-destructive manner.

Returns the original value of dst.
*/

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == s || len == 0)
		return (d);
	if (d > s && s + len > d)
	{
		while (len--)
		{
			d[len] = s[len];
		}
	}
	else
		return (ft_memcpy(d, s, len));
	return (d);
}
