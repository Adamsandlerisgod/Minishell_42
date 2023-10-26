/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:39:35 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/07 16:14:46 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_split use character c delimiter to split a string s.
Free the memory allocated by malloc after all the split is done.

Return the array of new strings.
*/

#include <stdlib.h>
#include "../includes/libft.h"

static void	*mem_free(char **tab, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(tab[j]);
		j++;
	}
	free(*tab);
	return (NULL);
}

static int	count_str(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (s[i] == 0)
		return (count);
	if (s[i] != c && i == 0)
	{
		count++;
		i++;
	}
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c && i > 0)
			count++;
		i++;
	}
	return (count);
}

static char	*tab_line(char const *s, int i, char c)
{
	char	*str;
	int		index;
	size_t	len;
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (k <= i)
	{
		len = 0;
		while (s[j] == c)
			j++;
		index = j;
		while (s[j] != c && s[j] != '\0')
		{
			j++;
			len++;
		}
		if (k == i)
			str = ft_substr(s, index, len);
		k++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		line;
	int		i;

	line = count_str(s, c);
	if (s == NULL)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (line + 1));
	if (tab == NULL)
		return (0);
	tab[line] = NULL;
	i = 0;
	while (i < line)
	{
		tab[i] = tab_line(s, i, c);
		if (tab[i] == NULL)
			return (mem_free(tab, i));
		i++;
	}
	return (tab);
}
