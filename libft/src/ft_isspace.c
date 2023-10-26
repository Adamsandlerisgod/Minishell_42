/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:50:40 by jhurpy            #+#    #+#             */
/*   Updated: 2023/04/24 22:22:59 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_isspace function checks whether the character passed as a parameter
is a space, a tabulation, or a newline. If it is, the function
returns a nonzero value, otherwise it returns 0.
*/

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
