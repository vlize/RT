/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_quartic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 08:10:30 by vlize             #+#    #+#             */
/*   Updated: 2016/03/11 17:16:36 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static void		ft_quartic_init(float *d, float *d0, float *k)
{
	d[3] /= d[4];
	d[2] /= d[4];
	d[1] /= d[4];
	d[0] /= d[4];
	k[0] = d[3] / 4.0;
	k[1] = d[3] * d[3];
	d0[3] = 1;
	d0[2] = -3.0 * k[1] / 8.0 + d[2];
	d0[1] = d[3] * k[1] / 8.0 - d[3] * d[2] / 2.0 + d[1];
	d0[0] = -3.0 * k[1] * k[1] / 256.0 + d[2] * k[1] / 16.0 \
			- d[3] * d[1] / 4.0 + d[0];
}

static void		ft_quartic_roots_init(float b, float *c, float *d0)
{
	float	k[2];

	k[0] = b * b + d0[2];
	k[1] = d0[1] / b;
	c[0] = (k[0] - k[1]) / 2.0;
	c[1] = (k[0] + k[1]) / 2.0;
}

static int		ft_quartic_roots(float *x, float b, float *d0)
{
	float	*x2;
	float	c[2];

	ft_quartic_roots_init(b, c, d0);
	if (!(x2 = ft_quadratic_equation(1, b, c[0])))
	{
		if (!(x2 = ft_quadratic_equation(1, -b, c[1])))
			return (0);
		x[0] = x2[0];
		x[1] = x2[1];
		x[2] = x2[0];
		x[3] = x2[1];
		return (1);
	}
	x[0] = x2[0];
	x[1] = x2[1];
	x[2] = x2[0];
	x[3] = x2[1];
	if (!(x2 = ft_quadratic_equation(1, -b, c[1])))
		return (1);
	x[2] = x2[0];
	x[3] = x2[1];
	return (1);
}

static float	*ft_quartic_result(float *x, float *k)
{
	x[0] -= k[0];
	x[1] -= k[0];
	x[2] -= k[0];
	x[3] -= k[0];
	if ((x[0] > x[1]) && (x[1] >= EPSILON))
		x[0] = x[1];
	if ((x[0] > x[2]) && (x[2] >= EPSILON))
		x[0] = x[2];
	if ((x[0] > x[3]) && (x[3] >= EPSILON))
		x[0] = x[3];
	if (x[0] < EPSILON)
		return (NULL);
	return (x);
}

float			*ft_quartic_equation(float *d)
{
	static float	x[4];
	float			*y;
	float			d0[4];
	float			k[2];

	if (fabsf(d[4]) < EPSILON)
		return (ft_cubic_equation(d));
	ft_quartic_init(d, d0, k);
	if (!(y = ft_cubic_equation(d0)))
		return (NULL);
	if (!ft_quartic_roots(x, y[0], d0))
		return (NULL);
	return (ft_quartic_result(x, k));
}
