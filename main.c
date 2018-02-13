/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 13:03:14 by nsikora           #+#    #+#             */
/*   Updated: 2018/02/09 15:36:55 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "get_next_line.h"
#include "libft/libft.h"
#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int				ft_getdot(char *line, t_dataset *data)
{
	int			i;
	int			total;

	i = 0;
	total = 0;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != '-' && line[i] != ' '
			&& line[i] != '\n')
			return (-1);
		if ((ft_isdigit(line[i]) == 1 && (ft_isspace(line[i - 1]) == 1
			|| i == 0)) || (line[i] == '-' && (ft_isdigit(line[i + 1]) == 1
			&& (ft_isspace(line[i - 1]) == 1 || i == 0))))
			total++;
		i++;
	}
	if ((data->max_y != 0 && data->max_y != total) || total < 1)
		return (-1);
	data->max_y = total;
	return (total);
}

int				ft_get_nb_line(char *file, t_dataset *data)
{
	int			fd;
	int			nb;
	int			i;
	char		*line;

	nb = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((i = get_next_line(fd, &line)) != 0)
	{
		if (i == -1)
		{
			close(fd);
			free(line);
			return (-1);
		}
		nb++;
		free(line);
	}
	close(fd);
	free(line);
	if (nb < 1)
		return (-1);
	return (data->max_x = nb);
}

int				ft_parsing(char *line, t_dataset *data, t_utils *u)
{
	if (!(data->tab[u->x] = malloc(sizeof(int) * (ft_getdot(line, data)))))
		return (1);
	u->i = 0;
	while (line[u->i] != '\0')
	{
		while (ft_isdigit(line[u->i]) == 1)
		{
			u->nb = u->nb * 10 + line[u->i] - 48;
			(line[u->i - 1] == '-') ? u->nb = u->nb * -1 : 1;
			u->cp++;
			u->i++;
		}
		(u->nb > data->max) ? data->max = u->nb : 1;
		(u->nb < data->min) ? data->min = u->nb : 1;
		if (u->cp > 0)
		{
			data->tab[u->x][u->y++] = u->nb;
			u->i--;
			u->cp = 0;
			u->nb = 0;
		}
		u->i++;
	}
	return (0);
}

int				ft_init_data(char *file, t_dataset *data)
{
	t_utils		*u;
	int			fd;
	int			size;

	fd = open(file, O_RDONLY);
	size = ft_get_nb_line(file, data);
	if (size == -1)
	{
		ft_putendl("error: file does not exist or is empty");
		exit(0);
	}
	if (!(data->tab = malloc(sizeof(int *) * (size))))
	{
		close(fd);
		return (1);
	}
	data->max_y = 0;
	if (!(u = malloc(sizeof(t_utils))))
		return (1);
	u->x = 0;
	if (ft_parsing_init_data(fd, data, u) == 1)
		return (1);
	return (0);
}

int				main(int ac, char **av)
{
	t_dataset	*data;

	if (ac != 2)
	{
		ft_putendl("usage: ./fdf filename.fdf");
		return (0);
	}
	if (ft_check_ext(av[1]) == 1 || (data = malloc(sizeof(t_dataset))) == 0)
		return (1);
	ft_declare_data(data);
	data->win = mlx_new_window(data->mlx, data->win_x, data->win_y, "fdf");
	if (ft_init_data(av[1], data) == 1)
	{
		ft_putendl("error: file content is not valid");
		return (1);
	}
	ft_display_info(av[1], data, "", "");
	ft_display_dot(data);
	mlx_key_hook(data->win, ft_key_event, data);
	mlx_loop(data->mlx);
	return (0);
}
