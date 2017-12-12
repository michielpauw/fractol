/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 12:23:21 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/12 15:47:50 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img	*get_fractal(t_img *img, t_complex c, int (f)(t_complex, t_complex, int))
{
	t_complex	z;
	int			index;
	int			length;
	int			rep;
	
	index = 0;
	length = img->size_line_int * IMG_H / img->cur_grain * img->cur_grain;
	while (index < length)
	{
		z.i = get_im(img, index);
		z.r = get_re(img, index);
		if (!(rep = f(z, c, img->detail)))
			index = fill_square(&img, index, img->cur_grain, 0xffffff);
		else
			index = fill_square(&img, index, img->cur_grain,
				((rep * 0xff) / img->detail) * img->color % 0xffffff); 
	}
	img->img_arr = img->new_arr;
	return (img);
}
