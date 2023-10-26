#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// typedef struct s_data
// {
// 	t_cmd	*cmd;
// }		t_data;

// typedef struct s_cmd
// {
// 	char			**cmd;
// 	bool			pipe;
// 	char			*infile;
// 	bool			in_redir;
// 	char			*outfile;
// 	bool			out_redir;
// 	bool			here_doc;
// 	char			*limiter;
// 	bool			append;
// 	// bool			op;
// }			t_cmd;

bool	ft_isquote(int c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}
bool	ft_isoptr(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&')
		return (true);
	return (false);
}
bool	ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}
bool	ft_istoken(int c)
{
	if (!(ft_isoptr(c)) && !(ft_isspace(c)))
		return (true);
	return (false);
}

int	lenoptr(char *line)
{
	if (*line && (line[1] == '&' || line[1] == '|' || line[1] == '<' || line[1] == '>'))
		return (2);
	return (1);
}

int	lenquote(char *line)
{
	int i;
	char	c;
	i = 1;
	c = line[0];
	while (line[i] != '\0')
	{
		if (line[i] == c)
			return (i + 1);
		i++;
	}
	// if (c == "\"")
	// 	quote_error(2);
	// if (c == "\'")
	// 	quote_error(1);
	return (i);
}

int	len_token(char *line)
{
	int		i;
	int		j;

	i = 0;
	if (ft_istoken(line[i]) || (line[i] == '&' && line[i + 1] != '&'))
	{
		if (line[i] == '&' && line[i + 1] != '&')
				i++;
		while ((ft_istoken(line[i]) || (line[i] == '&' && line[i + 1] != '&')) && line[i])
		{
			if (line[i] == '&' && line[i + 1] != '&')
				i++;
			if (ft_isquote(line[i]))
			{
				printf("lenquote = %d\n", lenquote(&line[i]));
				i += lenquote(&line[i]);
			}
			else
				i++;
		}
	}
	else if (ft_isoptr(line[i]))
		i += lenoptr(&line[i]);
	return (i);
}

int	token_count(char *line)
{
	int	tc;
	int	i;

	tc = 0;
	i = 0;
	if (!line)
		return (tc);
	printf("wigger\n");
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!(line[i]))
			return (tc);
		if(ft_istoken(line[i]))
			i += len_token(&line[i]);
		else if(ft_isoptr(line[i]))
			i += lenoptr(&line[i]);
		tc++;
	}
	return (tc);
}


char **token_split(char *line, int tc)
{
	int		i;
	int		j;
	int		k;
	char	**tokens;

	i = 0;
	j = 0;
	k = 0;
	tokens = NULL;
	tokens = (char **)malloc(sizeof(char *) * (token_count(line) + 1));
	printf("1\n");
	while (j < tc)
	{
		printf("2\n");
		while (ft_isspace(line[i]))
			i++;
		printf("3\n");
		k = len_token(&line[i]);
		printf("k = %d\n", k);
		tokens[j] = (char *)malloc(sizeof(char) * k);
		printf("5\n");
		memcpy(tokens[j], &line[i], k);
		printf("6\n");
		tokens[j][k] = '\0';
		i += k;
		j++;
	}
	tokens[tc] = NULL;
	return (tokens);
}

// int parsing(char *line, t_mini *stuff)
// {
// 	int tc;
// 	char **tokens;

// 	tc = token_count(line);
// 	if (tc == 0)
// 		return (false);
// 	tokens = (char **)malloc(sizeof(char *) * (tc + 1));
// 	tokens = token_split(line, tc + 1);
// 	stuff->token = tokens;
// 	return (true);
// }
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
		else if (*(array[i]) == '&' && ((array[i][1])))
		{
			if (array[i][1] == '&')
				block_count++;
		}
		i++;
	}
	return (block_count);
}

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
	
	line = "<<eff \'$var|afri&&ca fd|hhf||\'  <<";

	if (1 > 0)
	{
		int i = 0;
		int j = 0;
		printf("OG: %s\n", line);
		int tc = 0;
		printf("cunt \n");	
		while(line[i++])
		{
			if (line[i] == '|')
				j++;
		}
		printf("j = %d \n", j);

		array = (char **)malloc(sizeof(char *) * (j + 1));
		array = split_line(line, tc);
		// token_count(line);
		// array = (char **)malloc(sizeof(char *) * (token_count(line) + 1));
		printf("0\n");

		// array = token_split(line, token_count(line));
		
		printf("final");
		i = 0;
		while(array[i])
		{
			printf("array[%d]: %s \n", i, array[i]);
			i++;
		}
		// printf("block count = %d \n", count_blocks(array, tc));
	}
	return 0;

}