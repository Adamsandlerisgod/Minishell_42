/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:40:25 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/12 00:30:27 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_strrchr locates the last occurence of c
in the string pointed to by s, this included the null character.

Return a pointer to the located character.
*/

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	while (*s)
	{
		if (*s == c)
			ptr = (char *)s;
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (ptr);
}
