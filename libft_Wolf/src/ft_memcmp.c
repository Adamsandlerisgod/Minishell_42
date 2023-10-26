/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:52:54 by whendrik          #+#    #+#             */
/*   Updated: 2023/02/20 21:34:13 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)str1)[i] != ((unsigned char *)str2)[i])
			return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char *str1 = "sUckadong";
	char *str2 = "Suckadong";

	printf("%d,og \n %d,newstyle", memcmp(str1, str2, 6), ft_memcmp(str1, str2, 6));
}*/
