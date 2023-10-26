/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:31:28 by jhurpy            #+#    #+#             */
/*   Updated: 2023/06/22 02:05:03 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The ft_atol() function converts the initial portion of the string pointed to by
s to long representation.
It ignores all white-space characters at the beginning of the string, converts
the subsequent characters as part of the number,
and then stops when it encounters the first character that isn't a number.
The function returns the converted value, if any.
*/

long	ft_atol(const char *s)
{
	int		i;
	long	sign;
	long	num;

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
