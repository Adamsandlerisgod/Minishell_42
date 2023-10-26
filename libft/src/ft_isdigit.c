/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:38:01 by jeremy            #+#    #+#             */
/*   Updated: 2023/04/20 14:57:25 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_isdigit() function checks whether the given character is a digit.
It returns a non-zero value if the character is a digit and zero otherwise.
*/

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
