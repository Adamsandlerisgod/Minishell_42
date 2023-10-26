/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 22:20:13 by whendrik          #+#    #+#             */
/*   Updated: 2023/02/26 17:59:06 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s);
	ptr = (char *)s + len;
	if ((unsigned char)c == '\0')
		return (ptr);
	while (ptr >= s)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr--;
	}
	return (NULL);
}
