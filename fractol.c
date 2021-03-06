/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:07:23 by mpauw             #+#    #+#             */
/*   Updated: 2018/01/02 11:44:40 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error(int code)
{
	strerror(code);
	exit(1);
}

int		main(int argc, char **argv)
{
	int	fractal;

	srand(time(NULL));
	fractal = 0;
	if (argc == 2)
		fractal = ft_atoi(argv[1]) - 1;
	else if (argc > 2)
		error(errno);
	if (fractal > AMOUNT_FRAC - 1 || fractal < 0)
		fractal = 0;
	handle_window(fractal);
}
