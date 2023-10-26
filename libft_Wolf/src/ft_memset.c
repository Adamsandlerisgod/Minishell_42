/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:55:56 by whendrik          #+#    #+#             */
/*   Updated: 2023/02/20 23:32:21 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, unsigned int n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (n--)
		*ptr++ = (unsigned char)c;
	return (str);
}
/*
int	main(void)
{
	char str[] = "Fuck you pussy bitch";
	char str1[] = "Fuck you pussy bitch";

	printf("Before Change: %s \n After: %s", str, ft_memset(str1, '#', 7));
}*/
