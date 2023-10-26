/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:53:25 by whendrik          #+#    #+#             */
/*   Updated: 2023/02/20 23:32:00 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	if (str1 == NULL && str2 == NULL)
		return (dst);
	while (n--)
		*str1++ = *str2++;
	return (dst);
}
/*
int	main(void)
{
	char	s[50] = "Fuck you";
	char	t[50];

	strcpy(t, "Bitch");
	printf("Before: %s \n", s);
	ft_memcpy(s, t, strlen(s)+1);
	printf("After: %s \n", t);
	return (0);
}
*/
