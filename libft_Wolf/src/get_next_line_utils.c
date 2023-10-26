/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:10:02 by whendrik          #+#    #+#             */
/*   Updated: 2023/06/07 17:19:09 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	*specific_calloc(size_t count, size_t size)
{
	char				*tmp;
	char				*string;
	unsigned int		i;

	tmp = (void *)malloc(count * size);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	string = (char *)tmp;
	while (i < (unsigned int)(count * size))
	{
		string[i] = '\0';
		i++;
	}
	return (tmp);
}

size_t	ft_strlen_gnl(char *string, char z)
{
	int	i;

	i = 0;
	if (!string)
		return (i);
	if (z == '\0')
	{
		while (string[i])
			i++;
		return (i);
	}
	else
	{
		while (string[i] != z && string[i])
			i++;
		if (string[i] == z)
			i++;
	}
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	if (str1 == NULL && str2 == NULL)
		return (dst);
	while (n--)
		*str1++ = *str2++;
	return (dst);
}

char	*ft_strchr(const char *haystack, int needle)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)haystack;
	while (str[i] != needle && str[i] != '\0')
		i++;
	if (str[i] == needle)
		return (&str[i]);
	else
		return (NULL);
}

char	*ft_free_join(char *res, char *buffer)
{
	char	*totalstr;
	size_t	res_len;

	res_len = ft_strlen_gnl(res, '\0');
	totalstr = (char *)malloc(res_len + BUFFER_SIZE + 1);
	ft_memcpy(totalstr, res, res_len);
	ft_memcpy(totalstr + res_len, buffer, BUFFER_SIZE + 1);
	free(buffer);
	free(res);
	return (totalstr);
}
