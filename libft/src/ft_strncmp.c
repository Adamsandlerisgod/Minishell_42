/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:40:17 by jeremy            #+#    #+#             */
/*   Updated: 2024/01/23 19:45:36 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_strncmp compares not more then n characters
of the NUL-terminated strings s1 and s2.

Returns an integer greater than, equal to, or less then 0,
according the string s1 is greater than, equal to, or less then s2.
*/

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((i < n) && ((s1[i] != '\0') || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}
