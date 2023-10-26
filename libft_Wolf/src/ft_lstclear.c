/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:03:20 by whendrik          #+#    #+#             */
/*   Updated: 2023/06/07 12:09:56 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*node;

	if (lst == NULL || del == NULL)
		return ;
	tmp = *lst;
	while (tmp != NULL)
	{
		node = tmp->next;
		del(tmp->content);
		free(tmp);
		tmp = node;
	}
	*lst = NULL;
}
