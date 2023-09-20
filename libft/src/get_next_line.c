/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:03:16 by jhurpy            #+#    #+#             */
/*   Updated: 2023/05/15 17:27:47 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The function get_next_line will return a line read from a file descriptor one
by one.
Creat_node_new_fd will creat a new node if the fd is new.
Free_node_if_empty free the node of the fd after read and return every line.
Line_and_remains change the remains and the len_rem, and finaly return the line.
Read_fd read the file descriptor and copy every buf in remains.
*/

#include "../includes/libft.h"

t_fd_list	*creat_node_new_fd(int fd, t_fd_list **list)
{
	t_fd_list	*new_list;

	new_list = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (new_list == NULL)
		return (NULL);
	new_list->fd = fd;
	new_list->remains = (char *)malloc(sizeof(char) * 1);
	if (new_list->remains == NULL)
	{
		free(new_list);
		return (NULL);
	}
	new_list->remains[0] = '\0';
	new_list->len_rem = 1;
	new_list->len_read = 1;
	new_list->next = *list;
	*list = new_list;
	return (new_list);
}

t_fd_list	*free_node_if_empty(int fd, t_fd_list **cursor)
{
	t_fd_list	*prev;
	t_fd_list	*current;

	prev = NULL;
	current = *cursor;
	while (current != NULL && current->fd != fd)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL && current->len_read == 0)
	{
		if (prev == NULL)
			*cursor = current->next;
		else
			prev->next = current->next;
		free(current->remains);
		free(current);
	}
	return (*cursor);
}

char	*line_and_remains(t_fd_list *cursor)
{
	char	*line;
	int		len_nl;
	int		tmp;

	tmp = cursor->len_rem;
	len_nl = (ft_strlen_gnl(cursor->remains, 1));
	cursor->len_rem -= len_nl;
	if (ft_strlen_gnl(cursor->remains, 0) == 0)
		return (NULL);
	line = malloc(sizeof(char) * (len_nl + 1));
	if (line == NULL)
		return (NULL);
	ft_strlcpy_gnl(line, cursor->remains, len_nl + 1);
	ft_strlcpy_gnl(cursor->remains, cursor->remains + len_nl, cursor->len_rem);
	cursor->remains = ft_realloc(cursor->remains, tmp, cursor->len_rem);
	return (line);
}

void	read_fd(int fd, t_fd_list *cursor)
{
	char	*buf;
	int		tmp;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return ;
	while (cursor->len_read > 0)
	{
		tmp = cursor->len_rem;
		cursor->len_read = (int)read(fd, buf, BUFFER_SIZE);
		if (cursor->len_read <= 0)
			break ;
		buf[cursor->len_read] = 0;
		cursor->len_rem += cursor->len_read;
		cursor->remains = ft_realloc(cursor->remains, tmp, cursor->len_rem);
		ft_strlcat_gnl(cursor->remains, buf, cursor->len_rem);
		if (find_n(cursor->remains) == 1)
			break ;
	}
	free(buf);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*list;
	t_fd_list			*cursor;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	cursor = list;
	if (!list)
		cursor = creat_node_new_fd(fd, &list);
	else
	{
		while (cursor != NULL && cursor->fd != fd)
			cursor = cursor->next;
		if (!cursor)
			cursor = creat_node_new_fd(fd, &list);
	}
	if (cursor->len_read > 0)
		read_fd(fd, cursor);
	line = line_and_remains(cursor);
	if (cursor->len_read == 0 && find_n(line) != 1)
	{
		list = free_node_if_empty(fd, &list);
		return (line);
	}
	return (line);
}
