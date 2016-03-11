/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cubic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:26:42 by vlize             #+#    #+#             */
/*   Updated: 2016/03/11 17:23:55 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

int				ft_cubic_roots(float *x)
{
	if ((x[0] > x[1]) && (x[1] >= EPSILON))
		x[0] = x[1];
	if ((x[0] > x[2]) && (x[2] >= EPSILON))
		x[0] = x[2];
	if (x[0] < EPSILON)
		return (0);
	return (1);
}

static float	*ft_cubic_negative(float p, float *x, float *k)
{
	float	elem[3];

	elem[0] = 2 * sqrtf(0 - p / 3.0);
	elem[1] = acosf(k[0] * sqrtf(-27 / powf(p, 3))) / 3.0;
	elem[2] = M_PI / 1.5;
	x[0] = elem[0] * cosf(elem[1]) - k[1];
	x[1] = elem[0] * cosf(elem[1] + elem[2]) - k[1];
	x[2] = elem[0] * cosf(elem[1] + elem[2] * 2) - k[1];
	return (x);
}

static float	*ft_cubic_positive(float delta, float *x, float *k)
{
	float	u;
	float	v;

	delta = sqrtf(delta);
	u = cbrtf(k[0] + delta);
	v = cbrtf(k[0] - delta);
	x[0] = u + v - k[1];
	x[1] = x[0];
	x[2] = x[0];
	return (x);
}

static float	*ft_cubic_zero(float p, float q, float *x, float *k)
{
	x[0] = 3.0 * q / p - k[1];
	x[1] = -3.0 * q / (2.0 * p) - k[1];
	x[2] = x[1];
	return (x);
}

float			*ft_cubic_equation(float *d)
{
	static float	x[3];
	float			delta;
	float			k[2];
	float			p;
	float			q;

	if (fabsf(d[3]) < EPSILON)
		return (ft_quadratic_equation(d[2], d[1], d[0]));
	d[0] /= d[3];
	d[1] /= d[3];
	d[2] /= d[3];
	d[3] = powf(d[2], 2);
	p = d[1] - d[3] / 3.0;
	q = d[2] / 27.0 * (2.0 * d[3] - 9.0 * d[1]) + d[0];
	delta = powf(q / 2.0, 2) + powf(p / 3.0, 3);
	k[0] = 0 - q / 2.0;
	k[1] = d[2] / 3.0;
	if (fabsf(delta) < EPSILON)
		return (ft_cubic_zero(p, q, x, k));
	else if (delta > 0)
		return (ft_cubic_positive(delta, x, k));
	return (ft_cubic_negative(p, x, k));
}
