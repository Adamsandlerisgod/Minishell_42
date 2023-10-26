/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_var_finder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:55:34 by whendrik          #+#    #+#             */
/*   Updated: 2023/10/11 12:20:25 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>

int	ft_isalpha(int c)
{
	return ((c <= 122 && c >= 97) || (c <= 90 && c >= 65));
}

static char	*var_position(char *token, int *s_open, int *d_open, int *p)
{
	int	open_single_qt;
	int	open_double_qt;
	int i = *p;

	open_single_qt = *s_open;
	open_double_qt = *d_open;
	while (token[i] != '\0')
	{
		if (token[i] == '\'' && !open_double_qt)
			open_single_qt = !open_single_qt;	
		if (token[i] == '\"' && !open_single_qt)
			open_double_qt = !open_double_qt;
		if (token[i] == '$' && ((token[i + 1] == '?') | (ft_isalpha(token[i + 1]))) && !open_single_qt)
		{
			*s_open = open_single_qt;
			*d_open = open_double_qt;
			*p = i;
			return (&token[i]);
		}
		i++;
	}
	*s_open = open_single_qt;
	*d_open = open_double_qt;
	return (NULL);
}
int main() {
    char token[] = "This is a $test 'string' with $variables inside $fuck you ";
    int s_open = 0;
    int d_open = 0;
	int i = 0;

    char *pos = var_position(token, &s_open, &d_open, &i);

 while (pos != NULL){
	if (pos != NULL) {
        printf("Variable Position: %s\n", pos);
		i += 1;
    } else {
        printf("No expandable variable found.\n");
    }
	pos = var_position(token, &s_open, &d_open, &i);	
 }

    return 0;
}