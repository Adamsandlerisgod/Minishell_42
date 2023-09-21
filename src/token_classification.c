/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classification.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:43:46 by whendrik          #+#    #+#             */
/*   Updated: 2023/09/14 19:25:56 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_blocks(char **array, int tc)
{
	int	i;
	int block_count;

	block_count = 1;
	i = 0;
	while (i < tc)
	{
		if (*(array[i]) == '|')
			block_count++;
/*
		else if (*(array[i]) == '&' && ((array[i][1])))
		{
			if (array[i][1] == '&')
				block_count++;
		}
*/
		i++;
	}
	return (block_count);
}

int block_tk_count(char **array, t_cmd *block)
{
	int	i;
	int tc;

	i = 0;
	while (array[i])
	{
		if (*(array[i]) == '|')
		{
			block->pipe = TRUE;
			return (i);
		}
		if (array[i][0] == '<' || array[0] == '>')
			{
				i++;
				
/* For Bonus 
		else if (*(array[i]) == '&' && ((array[i][1])))
		{
			if (array[i][1] == '&')
			{
				block.op = TRUE;
				return (i);
			}
		}
*/
		i++;
	}
	return (i);
}

int redirection_handle(char **array, t_cmd *block, int tc)
{
	int	i;

	i = 0;
	while (i != tc)
	{
		if (array[i][0] == '<')
		{
			if (array[i][1] && array[i][1] == '<')
			{
				block->here_doc = TRUE;
				block->limiter = ft_strdup(array[i + 1]);
			}
			else
			{
				block->in_redir = TRUE;
				block->infile = ft_strdup(array[i + 1]);
			}
		}
		else if(array[i][0] == '>')
		{
			if (array[i][1] && array[i][1] == '>')
			{
				block->append = TRUE;
				block->outfile = ft_strdup(array[i + 1]);
			}
			else
			{
				block->in_redir = TRUE;
				block->outfile = ft_strdup(array[i + 1]);
			}
		}
		i++;
	}
}

/*Blocks without redirections and pipes */
int token_block_split(char **array, int tc, t_data *stuff)
{
	int i;
	int j;
	int k;
	char **blocks;
	int block_count;

	i = 0;
	k = 0;
	j = 0;
	block_count = count_blocks(array, tc);
	blocks = array;
	
	while (block_count)
	{
		tc = block_tk_count(&(array[i]), stuff->cmd[j]);
		redirection_handle(&(array[i]), stuff.cmd, tc);
		while(tc--)
		{
			
			stuff->cmd[j]->cmd[k] = ft_strdup(array[i]);
			k++;
			i++;
		}
		block_count--;
	}
	return (blocks);
}