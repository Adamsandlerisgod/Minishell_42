/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:03:12 by jhurpy            #+#    #+#             */
/*   Updated: 2023/05/15 17:26:46 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Ft_realloc reallocate a new memory regarding the size copy the data and
free the previous pointer.
Ft_strlen count the len of the string regarding a parameter, 0 until '\0' else
the function count untill newline +1.
Find_nl return 1 if the function find new line in the string.
Ft_strlcpy copy the source in the destination respecting the dstsize.
Ft_strlcat concatenate the source after the destination respecting the dstsize.
*/

#include "../includes/libft.h"

size_t	ft_strlen_gnl(const char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	if (c == 0)
	{
		while (s[i] != '\0')
			i++;
	}
	else
	{
		while (s[i] && s[i] != '\n')
			i++;
		if (s[i] == '\n')
			i++;
	}
	return (i);
}

int	find_n(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_strlcat_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;

	dstlen = ft_strlen_gnl(dst, 0);
	i = 0;
	j = dstlen;
	while (src[i] != 0 && i < (dstsize - dstlen - 1))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
}

void	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (src == NULL)
	{
		dst[0] = '\0';
		return ;
	}
	while (src[i] != '\0' && (i != dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
