/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:14:51 by jeremy            #+#    #+#             */
/*   Updated: 2023/03/26 17:33:16 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_itoa take a integer and change it as an string copy in malloc.

Return the string in malloc.
*/

#include <stdlib.h>

static size_t	check_len(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*ptr;
	long	numb;

	len = check_len(n);
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[len] = '\0';
	numb = (long)n;
	if (n == 0)
		ptr[0] = '0';
	numb = (long)n;
	if (numb < 0)
	{
		ptr[0] = '-';
		numb = numb * -1;
	}
	while (numb > 0)
	{
		len--;
		ptr[len] = numb % 10 + 48;
		numb = numb / 10;
	}
	return (ptr);
}
