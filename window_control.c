/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:12:27 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/12 15:56:19 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_img	*init_image(void *mlx, int width_scr, int height_scr)
{
	t_img	*img;
	int		bpp;
	int		size_line;
	int		endian;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		error(errno);
	img->img_ptr = mlx_new_image(mlx, width_scr, height_scr);
	img->width = width_scr;
	img->height = height_scr;
	img->img_arr = mlx_get_data_addr(img->img_ptr, &bpp, &size_line, &endian);
	img->new_arr = mlx_get_data_addr(img->img_ptr, &bpp, &size_line, &endian);
	img->bpp = bpp;
	img->size_line = size_line;
	img->size_line_int = size_line / (bpp / 8);
	img->endian = endian;
	img->zoom_old_r = 4.0;
	img->zoom_new_r = 3.0;
	img->color = 0x100000;
	img->detail = ITERATIONS;
	img->cur_grain = 1;
	img->val_pp = (long double)(TO_DIS_W) / width_scr;
	img->x_zero = -TO_DIS_W / 2.0;
	img->y_zero = (long double)img->x_zero * (IMG_H / IMG_W);
	return (img);
}

static int		key_pressed(int key, void *param)
{
	t_event	*event;
	t_img	*img;

	event = (t_event *)param;
	img = event->img;
	if (key == 53)
		exit(0);
	else if (key == 126)
		img = set_move(img, -1);
	else if (key == 125)
		img = set_move(img, 1);
	else if (key == 123)
		img = set_move(img, -2);
	else if (key == 124)
		img = set_move(img, 2);
	else if ((key >= 6 && key <= 8) || (key >= 0 && key <= 2))
		img = set_color(img, key);
	else if (key == 24 || key == 27)
		img = set_detail(img, key);
	img->new_arr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
	img->cur_grain = GRAIN;
//	get_fractal(img); 
	event->img = img;
	mlx_put_image_to_window(event->mlx, event->win, img->img_ptr, IMG_X, IMG_Y);
	return (1);
}

static int		mouse_event(int button, int x, int y, void *param)
{
	t_event	*event;
	t_img	*img;

	event = (t_event *)param;
	img = event->img;
	if (button == 1 || button == 4)
		img = set_zoom(img, x, y, 1);
	else if (button == 2 || button == 5)
		img = set_zoom(img, x, y, -1);
	img->new_arr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
	img->cur_grain = GRAIN;
//	get_fractal(img);
	event->img = img;
	mlx_put_image_to_window(event->mlx, event->win, img->img_ptr, IMG_X, IMG_Y);
	return (1);
}

static int		loop_event(void *param)
{
	t_event *event;
	t_img	*img;

	event = (t_event *)param;
	img = event->img;
	if (img->cur_grain > 1)
	{
		img->new_arr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
		img->cur_grain /= 2;
//		get_fractal(img);
		event->img = img;
		mlx_put_image_to_window(event->mlx, event->win, img->img_ptr, IMG_X, IMG_Y);
	}
	return (1);
}

void			handle_window(void)
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_event	*event;
	t_complex	c;

	c.r = 0;
	c.i = 0;

	mlx = mlx_init();
	win = mlx_new_window(mlx, INIT_W, INIT_H, "Fractol");
	img = init_image(mlx, IMG_W, IMG_H);
	img = get_fractal(img, c, &in_mandelbrot);
	mlx_put_image_to_window(mlx, win, img->img_ptr, IMG_X, IMG_Y);
	if (!(event = (t_event *)malloc(sizeof(t_event))))
		error(errno);
	event->mlx = mlx;
	event->win = win;
	event->img = img;
	mlx_key_hook(win, &key_pressed, event);
	mlx_mouse_hook(win, &mouse_event, event);
	mlx_loop_hook(mlx, &loop_event, event);
	mlx_loop(mlx);
	free(img);
}
