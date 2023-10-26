/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:39:49 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/07 16:14:52 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_strdup allocates sufficient memory for copy of the strings s1,
does the copy,
and returns a pointer to it.
The pointer may be used as an argument to the function free.
*/

#include <stdlib.h>
#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	len;

	len = ft_strlen(s);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	ft_strlcpy(p, s, len + 1);
	return (p);
}
