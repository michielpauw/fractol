/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:07:23 by mpauw             #+#    #+#             */
/*   Updated: 2017/12/15 16:05:01 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error(int code)
{
	strerror(code);
	exit(1);
}

int	main(int argc, char **argv)
{
	int	fractal;

	srand(time(NULL));
	fractal = 0;
	if (argc == 2)
		fractal = ft_atoi(argv[1]);
	else if (argc > 2)
		error(errno);
	handle_window(fractal);
}

