/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_z_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 19:58:21 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/14 18:19:46 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_point	matrix_mult_3d(t_point *p, float **mat)
{
	float	x_cur;
	float	y_cur;
	float	z_cur;

	x_cur = p->x;
	y_cur = p->y;
	z_cur = p->z;
	p->x = x_cur * mat[0][0] + y_cur * mat[0][1] + z_cur * mat[0][2];
	p->y = x_cur * mat[1][0] + y_cur * mat[1][1] + z_cur * mat[1][2];
	p->z = x_cur * mat[2][0] + y_cur * mat[2][1] + z_cur * mat[2][2];
	return (*p);
}

t_point	*get_cube(int size)
{
	int	i;
	t_point	*cube;

	if (!(cube = (t_point *)malloc(8 * sizeof(t_point))))
		error(errno);
	i = 0;
	while (i < 8)
	{
		if (i < 4)
			cube[i].z = size;
		else
			cube[i].z =  -size;
		if (i == 2 || i == 6 || i == 5 || i == 1)
			cube[i].x = size;
		else
			cube[i].x = -size;
		if (i == 2 || i == 3 || i == 6 || i == 7)
			cube[i].y = -size;
		else
			cube[i].y = size;
		i++;
	}
	return (cube);
}

t_point			*get_projection(t_point *data, int cam, t_event *event)
{
	t_point	*proj;
	int		i;

	if (!(proj = (t_point *)malloc(8 * sizeof(t_point))))
		error(errno);
	i = 0;
	while (i < 8)
	{
		proj[i].z = DIST_CAM + cam - data[i].z;
		if (round(proj[i].z) == 0)
			(proj[i].z)++;
		proj[i].x = (data[i].x * (event->frc).width) / proj[i].z + (event->frc).width / 2;
		proj[i].y = (data[i].y * (event->frc).height) / proj[i].z + (event->frc).height / 2;
		i++;
	}
	return (proj);
}

t_point			*simple_rotation(t_point *points, int axis, int dir)
{
	float	**rotation_matrix;
	int		i;

	rotation_matrix = get_rotation_matrix(axis, dir);
	i = 0;
	while (i < 8)
	{
		points[i] = matrix_mult_3d(&points[i], rotation_matrix);
		i++;
	}
	i = 0;
	while (i < 3)
		free(rotation_matrix[i++]);
	free(rotation_matrix);
	return (points);
}
