/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 14:50:28 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/15 16:35:57 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*ld_to_str(long double c)
{
	int		b;
	int		i;
	char	*str;
	char	*nb;

	if (!(str = (char *)malloc(sizeof(char) * 12)))
		error(errno);
	nb = ft_itoa(c);
	i = 0;
	if (ft_strlen(nb) > 9)
		return (nb);
	while (*nb)
		str[i++] = *(nb++);
	str[i++] = '.';
	if (c < 0)
		c = -1 * c;
	while (i < 11)
	{
		c = c * 10;
		b = (int)floor(c) % 10;
		str[i] = (char)b + '0';
		i++;
	}
	str[i] = 0;
	return (str);
}

static long double	get_x_coor(t_event *ev, int loc, int *pos_x)
{
	*pos_x = (ev->frc).width / 6 * (1 + 3 * (loc % 2));
	return ((long double)*pos_x * (ev->frc).val_pp + (ev->frc).x_zero);
}

static long double	get_y_coor(t_event *ev, int loc, int *pos_y)
{
	*pos_y = (ev->frc).height / 6 * (1 + 4 * (loc / 2));
	return (*pos_y * (ev->frc).val_pp + (ev->frc).y_zero);
}

t_event	*put_coordinates(t_event *ev)
{
	long double	x;
	long double	y;
	int		i;
	int		pos_x;
	int		pos_y;
	char	*str;

	i = 0;
	while (i < 4)
	{
		x = get_x_coor(ev, i, &pos_x);
		y = get_y_coor(ev, i, &pos_y);
		if (!(str = (char *)malloc(sizeof(char) * 26)))
			error(errno);
		str = ft_strcat(str, "(");
		str = ft_strcat(str, ld_to_str(x));
		str = ft_strcat(str, ", ");
		str = ft_strcat(str, ld_to_str(y));
		str = ft_strcat(str, ")");
		mlx_string_put(ev->mlx, ev->win, pos_x, pos_y, ev->sec_color * 0xff, str);
		free(str);
		*str = 0;
		i++;
	}
	return (ev);
}
