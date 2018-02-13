/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 14:14:54 by nsikora           #+#    #+#             */
/*   Updated: 2018/02/08 14:38:08 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "fdf.h"

void	ft_declare_data(t_dataset *data)
{
	data->mlx = mlx_init();
	data->max = 0;
	data->min = 0;
	data->win_x = 2560;
	data->win_y = 1400;
	data->color = 0x00FF00;
}
