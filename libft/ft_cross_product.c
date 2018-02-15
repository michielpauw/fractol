/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cross_product.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpauw <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 11:19:44 by mpauw             #+#    #+#             */
/*   Updated: 2018/01/30 17:31:34 by mpauw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_3v	*ft_cross_product(t_3v v1, t_3v v2)
{
	t_3v	*cp;
	double	*e1;
	double	*e2;

	if (!(cp = (t_3v *)malloc(sizeof(t_3v))))
		return (NULL);
	e1 = v1.v;
	e2 = v2.v;
	(cp->v)[0] = e1[1] * e2[2] - e2[1] * e1[2];
	(cp->v)[1] = e1[2] * e2[0] - e2[2] * e1[0];
	(cp->v)[2] = e1[0] * e2[1] - e2[0] * e1[1];
	return (cp);
}
