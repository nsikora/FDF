/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsikora <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 09:28:02 by nsikora           #+#    #+#             */
/*   Updated: 2018/02/09 11:26:44 by nsikora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fdf.h"

int		ft_check_ext(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (str[i - 4] != '.' || str[i - 3] != 'f' || str[i - 2] != 'd'
		|| str[i - 1] != 'f')
	{
		ft_putendl("error: wrong file type");
		return (1);
	}
	return (0);
}
