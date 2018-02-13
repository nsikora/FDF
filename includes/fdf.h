/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:41:38 by nsikora           #+#    #+#             */
/*   Updated: 2018/02/09 10:27:23 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

typedef struct	s_dataset
{
	void		*mlx;
	void		*win;
	int			**tab;
	int			max_x;
	int			max_y;
	int			min;
	int			max;
	int			win_x;
	int			win_y;
	int			color;
	int			size;
}				t_dataset;

typedef struct	s_bresenham
{
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
}				t_bresenham;

typedef struct	s_utils
{
	int			x;
	int			y;
	int			i;
	int			nb;
	int			cp;
}				t_utils;

# define ABS(i) ((i < 0) ? -i : i)

void			ft_display_info(char *name, t_dataset *data, char *str_x,
				char *str_y);
void			ft_display_dot(t_dataset *data);
void			ft_display_line(t_dataset *data, t_bresenham *bres);
void			ft_free_for_all(t_dataset *data);
void			ft_declare_data(t_dataset *data);
int				ft_key_event(int key, t_dataset *data);
int				ft_check_ext(char *str);
int				ft_send_coord(int x, int y, t_bresenham *bres, t_dataset *data);
int				ft_parsing_init_data(int fd, t_dataset *data, t_utils *u);
int				ft_parsing(char *line, t_dataset *data, t_utils *u);

#endif
