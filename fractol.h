/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:45:21 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/15 16:30:33 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define IMG_W 1200.0
# define IMG_H 800.0
# define IMG_SQ_3 729.0
# define IMG_X 0
# define IMG_Y 0
# define AMOUNT_FRAC 3
# define ZOOM_FACTOR 0.75

# define PointerMotionMask (1L<<6)
# define Button1MotionMask (1L<<8)
# define ButtonReleaseMask (1L<<3)
# define KeyPressMask (1L<<0)
# define KeyReleaseMask (1L<<1)
# define MotionNotify 6
# define KeyPress 2
# define KeyRelease 3
# define ButtonRelease 5

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>
# include <time.h>

typedef struct	s_complex
{
	long double	r;
	long double i;
}				t_complex;

typedef struct	s_img
{
	void		*img_ptr;
	char		*img_arr;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			size_line_int;
	int			endian;
}				t_img;

typedef struct	s_fractal
{
	int			id;
	char		*title;
	int			(*f)();
	int			grain;
	int			width;
	int			height;
	int			iterations;
	long double	x_zero;
	long double	y_zero;
	long double	val_pp;
}				t_fractal;

typedef struct	s_event
{
	void		*win;
	void		*mlx;
	int			store_x;
	int			store_y;
	t_img		*img;
	t_complex	c;
	t_fractal	frc;
	int			cur_grain;
	int			disco;
	int			color;
	int			sec_color;
	int			coor_wanted;
	int			coor_put;
	int			change_c;
	int			mouse_hold;
	int			moved;
}				t_event;

int			in_mandelbrot(t_complex z, t_complex c, int iterations);
int			in_julia(t_complex z, t_complex c, int iterations);
int			in_sierpinski(t_complex z, t_complex c, int iterations);
void		handle_window(int fractal);
t_event		*get_fractal(t_event *event);
void		error(int code);
t_event		*set_zoom(t_event *event, int x, int y, int dir);
t_event		*set_move(t_event *event, int dir);
t_event		*set_color(t_event *event, int color, int disco);
t_event		*set_detail(t_event *event, int detail);
int			fill_square(t_img **img, int index, int size, int color);
long double	get_im(t_event *event, int index);
long double	get_re(t_event *event, int index);
t_img		*init_image(void *mlx, int width_scr, int height_scr);
t_event		*setup_event(void *mlx, int fractal);
t_event		*new_image(t_event *event);
t_event		*update_event(t_event *event, int fractal);
int			mouse_motion_julia(int x, int y, void *param);
int			mouse_motion_sierpinski(int x, int y, void *param);
int			mouse_click(int button, int x, int y, void *param);
t_event		*put_coordinates(t_event *ev);
t_event		*change_fractal(t_event *event, int fractal);
void		loop(t_event *event);
int			drag_fractal(int x, int y, void *param);
int			toggle_button(int button, int x, int y, void *param);

#endif
