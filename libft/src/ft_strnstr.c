/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:40:21 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/07 16:15:12 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_strnstr locates the first occurence of
null terminated string needle in the string haystack,
where no more than len charactere are searched.

Return pointer to the first character of the first occurence of needle.
If needle empty return haystack, if needle occurs nowhere return NULL.
*/

#include <stdlib.h>
#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;
	char	*ptr;

	ptr = (char *) haystack;
	if (*needle == 0)
		return (ptr);
	if (len == 0)
		return (NULL);
	needle_len = ft_strlen(needle);
	i = 0;
	while ((ptr[i] != '\0') && ((i + needle_len) <= len))
	{
		if (ft_strncmp(&ptr[i], needle, needle_len) == 0)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}
