/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt_fl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 08:38:29 by mpauw             #+#    #+#             */
/*   Updated: 2017/11/20 08:43:17 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_sqrt_fl(size_t nb)
{
	size_t	i;

	i = 0;
	while (i * i < nb)
	{
		if (i > 65535)
			return (0);
		i++;
	}
	if (i * i == nb)
		return (i);
	else
		return (i - 1);
}
