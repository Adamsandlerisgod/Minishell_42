/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:56:10 by whendrik          #+#    #+#             */
/*   Updated: 2023/02/21 17:46:20 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	destlen;
	unsigned int	srclen;

	i = 0;
	srclen = ft_strlen((char *)src);
	if (size == 0 && dest == NULL)
		return (srclen);
	destlen = ft_strlen(dest);
	if (destlen >= size)
		return (srclen + size);
	while (src[i] != '\0' && i < (size - destlen - 1))
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
/*
For some reason moving line 25 from line 21, allowed it to pass the test,
it previously said that my strlcat would crash when null parameter was sent
with a size of zero. */
