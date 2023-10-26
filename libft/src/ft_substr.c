/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:40:35 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/07 16:15:21 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_substr creat a substring from the string s.
The substring begin at index of start and copy for len size in substring.

Return the substring creat from s, or NULL if memory not allocated.
*/

#include <stdlib.h>
#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	sub_n;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) <= start || len == 0)
		return (ft_strdup(""));
	i = ft_strlen(&s[start]);
	if (len > i)
		sub_n = i + 1;
	else
		sub_n = len + 1;
	sub_s = (char *)malloc(sub_n * sizeof(char));
	if (sub_s == 0)
		return (0);
	ft_strlcpy(sub_s, &s[start], sub_n);
	return (sub_s);
}
