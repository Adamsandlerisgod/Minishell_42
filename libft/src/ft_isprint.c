/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:38:05 by jeremy            #+#    #+#             */
/*   Updated: 2023/04/20 14:58:50 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_isprint function is used to determine whether the given character is
a printable character or not. It checks whether the ASCII value of
the character lies between 32 and 126, which includes
all printable characters in the ASCII table.
The function returns 1 if the character is printable and 0 otherwise.
*/

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
