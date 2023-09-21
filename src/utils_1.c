/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:06:30 by whendrik          #+#    #+#             */
/*   Updated: 2023/09/15 13:01:21 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	ft_istoken(int c)
{
	if (!(ft_isoprt(c)) && !(ft_isspace(c)))
		return (true);
	return (false);
}

bool	ft_isoptr(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}
