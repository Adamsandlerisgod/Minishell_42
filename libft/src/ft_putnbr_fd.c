/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:15:20 by jeremy            #+#    #+#             */
/*   Updated: 2023/05/07 16:14:35 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_putnbr_fd use copy a integer in the file descriptor fd.
The integer must to be change in characters.
*/

#include <unistd.h>
#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		sign;

	sign = 1;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		sign = -1;
	}
	if (n / 10)
		ft_putnbr_fd(n / 10 * sign, fd);
	c = (n % 10 * sign) + 48;
	ft_putchar_fd(c, fd);
}
