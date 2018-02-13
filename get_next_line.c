/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:22:10 by nsikora           #+#    #+#             */
/*   Updated: 2018/02/09 15:41:52 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*init(t_list **lst, size_t fd)
{
	t_list	*tmp;
	t_gnl	*content;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(content = malloc(sizeof(t_gnl))))
		return (0);
	if (!(content->str = malloc(sizeof(char))))
		return (0);
	if (!(tmp = ft_lstnew(NULL, 0)))
		return (0);
	tmp->content = (void*)content;
	tmp->content_size = fd;
	content->str[0] = '\0';
	content->index = 0;
	ft_lstadd(lst, tmp);
	return (*lst);
}

static int		line_copy(t_gnl *content, char **line)
{
	content->len = content->index;
	while (content->str[content->len] && content->str[content->len] != '\n')
		content->len++;
	if (!(*line = malloc(sizeof(char) *
					(content->len - content->index) + 1)))
		return (0);
	line[0][content->len - content->index] = '\0';
	ft_strncpy(*line, content->str + content->index,
			content->len - content->index);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_list			*tmp;
	char			*str_tmp;
	char			buf[BUFF_SIZE + 1];

	if (!line || fd < 0 || !(tmp = init(&lst, fd)) || read(fd, buf, 0) == -1)
		return (-1);
	CAST(tmp)->size = 0;
	while (((CAST(tmp)->size * BUFF_SIZE < CAST(tmp)->index)
				|| !ft_strchr(CAST(tmp)->str + CAST(tmp)->index, '\n'))
			&& (CAST(tmp)->len = read(fd, buf, BUFF_SIZE)))
	{
		buf[CAST(tmp)->len] = '\0';
		str_tmp = CAST(tmp)->str;
		if (!(CAST(tmp)->str = ft_strjoin(CAST(tmp)->str, buf)))
			return (-1);
		free(str_tmp);
		CAST(tmp)->size++;
	}
	if (!line_copy(CAST(tmp), line))
		return (-1);
	if (CAST(tmp)->str[CAST(tmp)->index] == '\0')
		return (0);
	CAST(tmp)->index = CAST(tmp)->len + CAST(tmp)->str[CAST(tmp)->len] / 10;
	return (1);
}
