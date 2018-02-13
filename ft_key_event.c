/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 09:23:49 by nsikora           #+#    #+#             */
/*   Updated: 2018/02/09 12:57:33 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"
#include "mlx/mlx.h"
#include "libft/libft.h"

void	ft_free_for_all(t_dataset *data)
{
	int	x;

	x = 0;
	(void)(data);
	while (x < data->max_x)
		free(data->tab[x++]);
	mlx_destroy_window(data->mlx, data->win);
	free(data->tab);
	free(data);
	exit(0);
}

int		ft_key_event(int key, t_dataset *data)
{
	if (key == 49)
	{
		if (data->color >= 100000)
			data->color = data->color - 100000;
		else
			data->color = 0xFFFFFF;
		ft_display_dot(data);
	}
	if (key == 53)
		ft_free_for_all(data);
	return (0);
}
