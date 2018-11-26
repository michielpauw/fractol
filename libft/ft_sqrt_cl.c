/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_cl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 08:43:28 by mpauw             #+#    #+#             */
/*   Updated: 2017/11/20 08:43:50 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_sqrt_cl(size_t nb)
{
	size_t	i;

	i = 0;
	while (i * i < nb)
	{
		if (i > 65535)
			return (0);
		i++;
	}
	return (i);
}
