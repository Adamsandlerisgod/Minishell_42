/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 22:22:22 by jhurpy            #+#    #+#             */
/*   Updated: 2023/06/06 23:57:45 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_lstsize count every node of the list.

Return the lenght of the list.
*/

#include "../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*node;

	node = lst;
	i = 0;
	while (node != NULL)
	{
		node = node->next;
		i++;
	}
	return (i);
}
