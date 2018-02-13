/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_dot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 10:36:33 by nsikora           #+#    #+#             */
/*   Updated: 2018/02/08 14:08:42 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"
#include "libft/libft.h"
#include "mlx/mlx.h"

void			ft_display_info(char *name, t_dataset *data, char *str_x,
				char *str_y)
{
	str_x = ft_itoa(data->max_x);
	str_y = ft_itoa(data->max_y);
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFF0000, "Map:");
	mlx_string_put(data->mlx, data->win, 60, 10, 0xFFFFFF, name);
	mlx_string_put(data->mlx, data->win, 10, 30, 0xFF0000, "Height:");
	mlx_string_put(data->mlx, data->win, 90, 30, 0xFFFFFF, str_x);
	mlx_string_put(data->mlx, data->win, 90 + ft_strlen(str_x) *
	10 + 30, 30, 0xFF0000, "Width:");
	mlx_string_put(data->mlx, data->win, 90 + ft_strlen(str_x) *
	10 + 100, 30, 0xFFFFFF, str_y);
	mlx_string_put(data->mlx, data->win, data->win_x / 2 - 100, data->win_y -
	110, 0xFFFFFF, "Press <");
	mlx_string_put(data->mlx, data->win, data->win_x / 2 - 25, data->win_y -
	110, 0xFFFF00, "ESC");
	mlx_string_put(data->mlx, data->win, data->win_x / 2 + 10, data->win_y -
	110, 0xFFFFFF, "> to quit");
	mlx_string_put(data->mlx, data->win, data->win_x / 2 - 140, data->win_y -
	130, 0xFFFFFF, "Press <");
	mlx_string_put(data->mlx, data->win, data->win_x / 2 - 65, data->win_y -
	130, 0xFFFF00, "space");
	mlx_string_put(data->mlx, data->win, data->win_x / 2 - 10, data->win_y -
	130, 0xFFFFFF, "> to swap color");
	free(str_x);
	free(str_y);
}

void			ft_display_line(t_dataset *data, t_bresenham *bres)
{
	bres->sx = (bres->x1 < bres->x2) ? 1 : -1;
	bres->sy = (bres->y1 < bres->y2) ? 1 : -1;
	bres->dx = (bres->x2 - bres->x1);
	bres->dy = (bres->y2 - bres->y1);
	bres->dx = (ABS(bres->dx));
	bres->dy = (ABS(bres->dy));
	bres->err = ((bres->dx > bres->dy) ? bres->dx : -bres->dy) / 2;
	while (bres->x1 != bres->x2 || bres->y1 != bres->y2)
	{
		mlx_pixel_put(data->mlx, data->win, bres->x1, bres->y1, data->color);
		bres->e2 = bres->err;
		if (bres->e2 > -bres->dx)
		{
			bres->err = bres->err - bres->dy;
			bres->x1 = bres->x1 + bres->sx;
		}
		if (bres->e2 < bres->dy)
		{
			bres->err = bres->err + bres->dx;
			bres->y1 = bres->y1 + bres->sy;
		}
	}
}

int				ft_get_square(t_dataset *data)
{
	if (((data->win_x - 200) / data->max_x) <=
	((data->win_y - 200) / data->max_y))
		data->size = (data->win_x - 200) / data->max_x / 2;
	else
		data->size = (data->win_y - 200) / data->max_y / 2;
	while ((data->size * 2 < (data->win_y - 200) / data->max_y / 2))
		data->size++;
	while ((data->size * 2 < (data->win_x - 200) / data->max_x / 2))
		data->size++;
	return (data->size);
}

int				ft_send_coord(int x, int y, t_bresenham *bres, t_dataset *data)
{
	if (y > 0)
	{
		bres->x1 = 1000 + (y - x) * data->size;
		bres->y1 = 100 + ((x * 2) + y) * data->size / 2 -
		(data->tab[x][y] * 100) / (data->max + 1);
		bres->x2 = 1000 + ((y - 1) - x) * data->size;
		bres->y2 = 100 + ((x * 2) + (y - 1)) * data->size / 2
		- (data->tab[x][y - 1] * 100) / (data->max + 1);
		ft_display_line(data, bres);
	}
	if (x > 0)
	{
		bres->x1 = 1000 + (y - x) * data->size;
		bres->y1 = 100 + ((x * 2) + y) * data->size / 2 -
		(data->tab[x][y] * 100) / (data->max + 1);
		bres->x2 = 1000 + (y - (x - 1)) * data->size;
		bres->y2 = 100 + (((x - 1) * 2) + y) * data->size / 2 -
		(data->tab[x - 1][y] * 100) / (data->max + 1);
		ft_display_line(data, bres);
	}
	y++;
	return (y);
}

void			ft_display_dot(t_dataset *data)
{
	t_bresenham	*bres;
	int			x;
	int			y;

	x = 0;
	y = 0;
	data->size = ft_get_square(data);
	if (!(bres = (t_bresenham *)malloc(sizeof(t_bresenham))))
		return ;
	while (x < data->max_x)
	{
		while (y < data->max_y)
			y = ft_send_coord(x, y, bres, data);
		y = 0;
		x++;
	}
	free(bres);
}
