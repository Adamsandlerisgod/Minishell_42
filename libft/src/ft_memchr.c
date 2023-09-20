/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:38:49 by jeremy            #+#    #+#             */
/*   Updated: 2023/02/05 01:08:41 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_memchr locates the first occurence of c in string s,
search in no more than len characteres of in string s.

Return a pointer to the byte located c.
*/

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (len > 0)
	{
		if (*ptr == (unsigned char) c)
			return (ptr);
		ptr++;
		len--;
	}
	return (NULL);
}
