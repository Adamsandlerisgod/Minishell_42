/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:37:32 by jeremy            #+#    #+#             */
/*   Updated: 2023/04/20 14:32:16 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_atoi function is a C function that takes a string as input and
returns an integer representing the numeric value of the string.
It ignores whitespace at the beginning of the string and
analyzes the following characters to determine the numeric value.
It takes into account the sign of the numeric value,
which can be specified by the characters '+' or '-'.
The function returns the integer corresponding to
the numeric value of the string.
*/

int	ft_atoi(const char *s)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == 45 || s[i] == 43)
	{
		if (s[i] == 45)
			sign *= -1;
		i++;
	}
	while (s[i] >= 48 && s[i] <= 57)
	{
		num = num * 10 + (s[i] - 48);
		i++;
	}
	return (num * sign);
}
