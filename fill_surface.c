/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_surface.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 08:04:19 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/14 18:19:56 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	*get_first(t_angle square[4])
{
	int	*order;
	int	i;
	int	j;
	int	tmp;

	if (!(order = (int *)malloc(4 * sizeof(int))))
		error(errno);
	i = -1;
	while (++i < 4)
		order[i] = i;
	i = -1;
	while (++i < 4)
	{
		j = i - 1;
		while (++j < 4)
		{
			if (square[i].index > square[j].index)
			{
				tmp = order[i];
				order[i] = order[j];
				order[j] = tmp;
			}
		}
	}
	return (order);
}

static void	index_to_xy(int index, int size_line, int *x, int *y)
{
	*x = index % size_line;
	*y = index / size_line;
}

static int	check_in(int index, t_angle sq[4], t_img *img)
{
	int	x;
	int	y;
	int	i;
	int	surface;
	int	surface_sq;

	index_to_xy(index, img->size_line_int, &x, &y);
	i = 0;
	surface = 0;
	while (i < 4)
	{
		surface = surface + abs((sq[i].x * (sq[(i + 1) % 4].y - y) +
					sq[(i + 1) % 4].x * (y - sq[i].y) + x * (sq[i].y
						- sq[(i + 1) % 4].y)) / 2);
		i++;
	}
	surface_sq = abs((sq[0].x * (sq[1].y - sq[2].y) + sq[1].x * (sq[2].y -
					sq[0].y) + sq[2].x * (sq[0].y - sq[1].y))) / 2;
	surface_sq += abs(sq[0].x * (sq[3].y - sq[2].y) + sq[3].x * (sq[2].y -
				sq[0].y) + sq[2].x * (sq[0].y - sq[3].y)) / 2;
	if (surface < surface_sq)
		return (1);
	return (0);
}

t_img	*fill_surface(t_img	*img, t_angle square[4], int color)
{
	int		i;
	int		begin;
	int		end;
	int		*order;

	i = 0;
	begin = 0;
	end = 0;
	order = get_first(square);
	begin = square[order[0]].index;
	end = square[order[3]].index;
	while (begin + i < end)
	{
		if (check_in(begin + i, square, img))
			((int *)(img->img_arr))[begin + i] = color;
		i++;
	}
	return (img);
}
