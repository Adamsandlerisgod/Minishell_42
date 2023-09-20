/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:37:55 by jeremy            #+#    #+#             */
/*   Updated: 2023/04/20 15:01:04 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_isascii checks whether the given argument c is
a valid ASCII character or not.
It returns 1 if c is a valid ASCII character, which means it has
a decimal value between 0 and 127 (inclusive), and 0 otherwise.
*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
