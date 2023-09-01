/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:15:49 by whendrik          #+#    #+#             */
/*   Updated: 2023/02/22 20:06:58 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*string;

	string = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		j = ft_strlen((char *)s1);
		while (s1[i] && ft_strchr((char *)set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr((char *)set, s1[j - 1]) && j > i)
			j--;
		string = (char *) malloc(sizeof(char) * (j - i + 1));
		if (string)
			ft_strlcpy(string, (char *)&s1[i], j - i + 1);
	}
	return (string);
}
