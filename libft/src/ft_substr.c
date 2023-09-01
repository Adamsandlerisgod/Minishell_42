/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:26:21 by whendrik          #+#    #+#             */
/*   Updated: 2023/02/27 14:10:25 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*string;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) <= start || len == 0)
		return (ft_strdup(""));
	i = ft_strlen(&s[start]);
	if (len > i)
		j = i + 1;
	else
		j = len + 1;
	string = (char *) malloc(sizeof(char) * j);
	if (string == NULL)
		return (NULL);
	ft_strlcpy(string, &s[start], j);
	return (string);
}
/*
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	sub_n;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if ((unsigned int)ft_strlen(s) <= start || len == 0)
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
}*/
