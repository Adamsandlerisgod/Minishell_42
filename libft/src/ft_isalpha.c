/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:37:51 by jeremy            #+#    #+#             */
/*   Updated: 2023/04/20 14:51:01 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_isalpha() function checks whether the given character is
an alphabetic character (uppercase or lowercase).
It returns a non-zero value if the character is
an alphabetic character and zero otherwise.
*/

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
