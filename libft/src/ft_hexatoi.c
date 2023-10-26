/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexatoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:53:40 by jhurpy            #+#    #+#             */
/*   Updated: 2023/05/31 01:42:35 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_ishexa(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')
		|| (c >= 'a' && c <= 'f'))
		return (1);
	return (0);
}

/*
The function ft_atoi_base converts the string argument str (base N <= 16)
*/

int	ft_hexatoi(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 2;
	while (ft_ishexa(str[i]))
	{
		result = result * 16;
		if (str[i] >= '0' && str[i] <= '9')
			result += (str[i] - '0');
		else if (str[i] >= 'a' && str[i] <= 'f')
			result += (str[i] - 'a' + 10);
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += (str[i] - 'A' + 10);
		i++;
	}
	return (result);
}
