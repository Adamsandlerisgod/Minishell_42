/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:37:46 by jeremy            #+#    #+#             */
/*   Updated: 2023/04/24 22:11:16 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_isalnum function checks whether the given character is
an alphanumeric character. An alphanumeric character is
any uppercase or lowercase letter or any decimal digit.
The function takes an integer as its argument, which represents
the character to be checked, and
returns 1 if the character is alphanumeric and 0 otherwise.
*/

int	ft_isalnum(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57));
}
