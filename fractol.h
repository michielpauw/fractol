/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:45:21 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/12 15:48:03 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define ITERATIONS 0xff
# define INIT_W 1800
# define INIT_H 1200
# define IMG_W 1800.0
# define IMG_H 1200.0
# define ZERO_OFF_X IMG_W / 5 
# define IMG_X 0
# define IMG_Y 0
# define TO_DIS_W 4.0
# define GRAIN 16

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>

typedef struct	s_complex
{
	long double	r;
	long double i;
}				t_complex;

typedef struct	s_img
{
	void		*img_ptr;
	char		*img_arr;
	char		*new_arr;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			size_line_int;
	int			endian;
	int			color;
	int			detail;
	int			zoom_old_r;
	int			zoom_new_r;
	int			cur_grain;
	long double	val_pp;
	long double	x_zero;
	long double	y_zero;
}				t_img;

typedef struct	s_event
{
	void		*win;
	void		*mlx;
	t_img		*img;
}				t_event;

int			in_mandelbrot(t_complex z, t_complex c, int iterations);
int			in_julia(t_complex z, t_complex c, int iterations);
void		handle_window(void);
t_img		*get_fractal(t_img *img, t_complex c, int (f)(t_complex, t_complex, int));
void		error(int code);
t_img		*set_zoom(t_img *img, int x, int y, int dir);
t_img		*set_move(t_img *img, int dir);
t_img		*set_color(t_img *img, int color);
t_img		*set_detail(t_img *img, int detail);
int			fill_square(t_img **img, int index, int size, int color);
long double	get_im(t_img *img, int index);
long double	get_re(t_img *img, int index);

#endif
