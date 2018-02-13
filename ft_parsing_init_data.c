/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:32:11 by nsikora           #+#    #+#             */
/*   Updated: 2018/02/09 10:53:08 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include "fdf.h"

int			ft_parsing_init_data(int fd, t_dataset *data, t_utils *u)
{
	char	*line;

	while (get_next_line(fd, &line) != 0)
	{
		u->y = 0;
		u->i = 0;
		u->nb = 0;
		u->cp = 0;
		if (ft_parsing(line, data, u) == 1)
		{
			close(fd);
			free(line);
			free(u);
			return (1);
		}
		u->x++;
		free(line);
	}
	close(fd);
	free(line);
	free(u);
	return (0);
}
