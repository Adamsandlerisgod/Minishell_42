/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:39:53 by jeremy            #+#    #+#             */
/*   Updated: 2023/02/16 21:06:06 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function ft_striteri pass the function pointed by f
to every characteres of the string s.
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s != 0)
	{
		while (s[i] != '\0')
		{
			f(i, &s[i]);
			i++;
		}
		s[i] = '\0';
	}
}
