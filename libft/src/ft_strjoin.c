/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:39:57 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/07 16:14:56 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_strjoin allocate memory
and concatenate the string s1 and s2 in new string.

Return the new string result.
*/

#include <stdlib.h>
#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	len_new_s;

	if (s1 == NULL)
		return (NULL);
	len_new_s = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_s = (char *)malloc(len_new_s * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	ft_strlcpy(new_s, s1, len_new_s);
	ft_strlcat(new_s, (char *)s2, len_new_s);
	return (new_s);
}
