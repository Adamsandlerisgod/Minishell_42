/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:39:08 by whendrik          #+#    #+#             */
/*   Updated: 2023/02/20 23:20:32 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d == s || len == 0)
		return (dst);
	if (s < d && s + len > d)
	{
		while (len--)
			d[len] = s[len];
	}
	else
	{
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}
/*
int main()
{
    char str1[20] = "hello world";
    char str2[20];
    char str3[20] = "hello world";
    char str4[20];

    // move the string from str1 to str2
    ft_memmove(str2, str1, 5);
    memmove(str4, str3, 5);

    // print the results
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    printf("str3: %s\n", str3);
    printf("str4: %s\n", str4);


    return 0;
}
*/
