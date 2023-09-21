/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:55:49 by whendrik          #+#    #+#             */
/*   Updated: 2023/09/15 17:27:18 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char **split_line(char *line, int tc)
{
	int	i;
	int	j;
	int	k;
	char **line_s;

	i = 0;
	j = 1;
	k = 0;
	while(line[i++])
	{
		if (line[i] == '|')
			j++;
	}	
	i = 0;
	line_s = (char **)malloc(sizeof(char *) * (j + 1));
	while (k < j)
	{
		while(line[tc] != '|' && line[tc])
			tc++;	
		// tc = ft_strlen_gnl(&(line[i]), '|');
		line_s[k] = (char *)malloc(sizeof(char) * (tc - i + 1));
		memcpy(line_s[k], &(line[i]), tc - i + 1);
		line_s[k++][tc + 1] = '\0';
		tc++;
		i = tc; 
	}
	line_s[k] = NULL;
	return(line_s);
}

int main(void)
{
	char **array;
	char *line;
	
	line = "BUSHb ]]|  DID  |9  |1     1";

	int i = 0;
	int j = 1;

		printf("OG: %s\n", line);
	while(line[i++])
	{
		if (line[i] == '|')
			j++;
	}
		printf("j = %d \n", j);

		array = (char **)malloc(sizeof(char *) * (j + 1));
		printf("0\n");
		array = split_line(line, 0);
		printf("final");
		i = 0;
		while(array[i])
		{
			printf("array[%d]: %s \n", i, array[i]);
			i++;
		}
	
	return 0;
}