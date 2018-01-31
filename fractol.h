/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:45:21 by mpauw             #+#    #+#             */
/*   Updated: 2018/01/02 16:50:00 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define I_W 1800.0
# define I_H 1200.0
# define I_S 729.0
# define Y_Z -4.0 / 3.0
# define IMG_X 0
# define IMG_Y 0
# define AMOUNT_FRAC 4
# define ZOOM_FACTOR 0.75
# define MARGIN_TRI 100

# define POINTER_MOTION_MASK (1L<<6)
# define BUTTON_MOTION_MASK (1L<<8)
# define BUTTON_RELEASE_MASK (1L<<3)
# define KEY_PRESS_MASK (1L<<0)
# define MOTION_NOTIFY 6
# define KEY_PRESS 2
# define BUTTON_RELEASE 5

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

int				in_mand(t_complex z, t_complex c, int iterations);
int				in_julia(t_complex z, t_complex c, int iterations);
int				in_sierp(t_complex z, t_complex c, int iterations);
void			handle_window(int fractal);
t_event			*get_fractal(t_event *event);
void			error(int code);
t_event			*set_zoom(t_event *event, int x, int y, int dir);
t_event			*set_move(t_event *event, int dir);
t_event			*set_color(t_event *event, int color, int disco);
t_event			*set_detail(t_event *event, int detail);
int				fill_square(t_img **img, int index, int size, int color);
long double		get_im(t_event *event, int index);
long double		get_re(t_event *event, int index);
t_img			*init_image(void *mlx, int width_scr, int height_scr);
t_event			*setup_event(void *mlx, int fractal);
t_event			*new_image(t_event *event);
t_event			*update_event(t_event *event, int fractal);
int				mouse_motion_julia(int x, int y, void *param);
int				mouse_motion_sierpinski(int x, int y, void *param);
int				mouse_click(int button, int x, int y, void *param);
t_event			*put_coordinates(t_event *ev);
t_event			*change_fractal(t_event *event, int fractal);
void			init_loop(t_event *event);
int				drag_fractal(int x, int y, void *param);
int				toggle_button(int button, int x, int y, void *param);
t_event			*add_tri_point(t_event *event, int x, int y);

#endif
