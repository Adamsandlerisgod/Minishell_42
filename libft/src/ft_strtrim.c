/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:40:30 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/07 16:15:18 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_strtrim copy the string s1 in new string,
remove the set of charactere at begining and end of s1.

Return the new trimmed string.
*/

#include <stdlib.h>
#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;

	if (set == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL)
		return (NULL);
	start = 0;
	while (ft_strchr(set, s1[start]) != NULL)
	{
		start++;
		if (start == ft_strlen(s1))
			return (ft_strdup(""));
	}
	start = 0;
	while (ft_strchr(set, s1[start]) != NULL)
		start++;
	len = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[len]) != NULL)
		len--;
	return (ft_substr(s1, start, (len - start + 1)));
}
