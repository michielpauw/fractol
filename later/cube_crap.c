/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_crap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 14:14:57 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/15 14:16:37 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_event	*construct_menger(t_event *event)
{
	t_point	*cube;
	int		size = 100;
	int		i;
	t_angle	sq[4];

	cube = get_cube(size);
	printf("First: %d %d %d %d %d %d %d %d\n", cube[0].x, cube[0].y, cube[4].x, cube[4].y, cube[7].x, cube[7].y, cube[3].x, cube[3].y);
	cube = simple_rotation(cube, 0, -1);
	cube = simple_rotation(cube, 1, -1);
	printf("After rotation: %d %d %d %d %d %d %d %d\n", cube[0].x, cube[0].y, cube[4].x, cube[4].y, cube[7].x, cube[7].y, cube[3].x, cube[3].y);
	cube = get_projection(cube, 0, event);
	i = 0;


	printf("After projection: %d %d %d %d %d %d %d %d\n", cube[0].x, cube[0].y, cube[1].x, cube[1].y, cube[2].x, cube[2].y, cube[3].x, cube[3].y);
	sq[0].x = cube[5].x;
	sq[0].y = cube[5].y;
	sq[0].index = cube[5].x + cube[5].y * (event->img)->size_line_int;
	sq[1].x = cube[6].x;
	sq[1].y = cube[6].y;
	sq[1].index = cube[6].x + cube[6].y * (event->img)->size_line_int;
	sq[2].x = cube[7].x;
	sq[2].y = cube[7].y;
	sq[2].index = cube[7].x + cube[7].y * (event->img)->size_line_int;
	sq[3].x = cube[4].x;
	sq[3].y = cube[4].y;
	sq[3].index = cube[4].x + cube[4].y * (event->img)->size_line_int;
	event->img = fill_surface(event->img, sq, 0xff00ff);

	sq[0].x = cube[7].x;
	sq[0].y = cube[7].y;
	sq[0].index = cube[7].x + cube[7].y * (event->img)->size_line_int;
	sq[1].x = cube[6].x;
	sq[1].y = cube[6].y;
	sq[1].index = cube[6].x + cube[6].y * (event->img)->size_line_int;
	sq[2].x = cube[2].x;
	sq[2].y = cube[2].y;
	sq[2].index = cube[2].x + cube[2].y * (event->img)->size_line_int;
	sq[3].x = cube[3].x;
	sq[3].y = cube[3].y;
	sq[3].index = cube[3].x + cube[3].y * (event->img)->size_line_int;
	event->img = fill_surface(event->img, sq, 0xff);
	sq[0].x = cube[5].x;
	sq[0].y = cube[5].y;
	sq[0].index = cube[5].x + cube[5].y * (event->img)->size_line_int;
	sq[1].x = cube[1].x;
	sq[1].y = cube[1].y;
	sq[1].index = cube[1].x + cube[1].y * (event->img)->size_line_int;
	sq[2].x = cube[2].x;
	sq[2].y = cube[2].y;
	sq[2].index = cube[2].x + cube[2].y * (event->img)->size_line_int;
	sq[3].x = cube[6].x;
	sq[3].y = cube[6].y;
	sq[3].index = cube[6].x + cube[6].y * (event->img)->size_line_int;
	event->img = fill_surface(event->img, sq, 0xffff);
	sq[0].x = cube[0].x;
	sq[0].y = cube[0].y;
	sq[0].index = cube[0].x + cube[0].y * (event->img)->size_line_int;
	sq[1].x = cube[1].x;
	sq[1].y = cube[1].y;
	sq[1].index = cube[1].x + cube[1].y * (event->img)->size_line_int;
	sq[2].x = cube[5].x;
	sq[2].y = cube[5].y;
	sq[2].index = cube[5].x + cube[5].y * (event->img)->size_line_int;
	sq[3].x = cube[4].x;
	sq[3].y = cube[4].y;
	sq[3].index = cube[4].x + cube[4].y * (event->img)->size_line_int;
	event->img = fill_surface(event->img, sq, 0xff00);
	sq[0].x = cube[0].x;
	sq[0].y = cube[0].y;
	sq[0].index = cube[0].x + cube[0].y * (event->img)->size_line_int;
	sq[1].x = cube[1].x;
	sq[1].y = cube[1].y;
	sq[1].index = cube[1].x + cube[1].y * (event->img)->size_line_int;
	sq[2].x = cube[2].x;
	sq[2].y = cube[2].y;
	sq[2].index = cube[2].x + cube[2].y * (event->img)->size_line_int;
	sq[3].x = cube[3].x;
	sq[3].y = cube[3].y;
	sq[3].index = cube[3].x + cube[3].y * (event->img)->size_line_int;
	event->img = fill_surface(event->img, sq, 0xffffff);

	sq[0].x = cube[0].x;
	sq[0].y = cube[0].y;
	sq[0].index = cube[0].x + cube[0].y * (event->img)->size_line_int;
	sq[1].x = cube[4].x;
	sq[1].y = cube[4].y;
	sq[1].index = cube[4].x + cube[4].y * (event->img)->size_line_int;
	sq[2].x = cube[7].x;
	sq[2].y = cube[7].y;
	sq[2].index = cube[7].x + cube[7].y * (event->img)->size_line_int;
	sq[3].x = cube[3].x;
	sq[3].y = cube[3].y;
	sq[3].index = cube[3].x + cube[3].y * (event->img)->size_line_int;
	event->img = fill_surface(event->img, sq, 0xffff00);
	return (event);
}
