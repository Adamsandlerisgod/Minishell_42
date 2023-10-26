/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:03:50 by whendrik          #+#    #+#             */
/*   Updated: 2023/02/20 15:26:12 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	char			*tmp;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	tmp = (void *)malloc(count * size);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}
