/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cubic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 08:26:42 by vlize             #+#    #+#             */
/*   Updated: 2016/03/10 15:07:23 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static float	*ft_cubic_negative(float p, float *x, float *k)
{
	float	elem[3];

	elem[0] = 2 * sqrtf(0 - p / 3);
	elem[1] = acosf(k[0] * sqrtf(-27 / powf(p, 3))) / 3;
	elem[2] = M_PI / 1.5;
	x[0] = elem[0] * cosf(elem[1]) - k[1];
	x[1] = elem[0] * cosf(elem[1] + elem[2]) - k[1];
	x[2] = elem[0] * cosf(elem[1] + elem[2] * 2) - k[1];
	return (x);
}

static float	*ft_cubic_positive(float delta, float *x, float *xi, float *k)
{
	float	u;
	float	v;
	float	j[2];

	j[0] = -0.5;
	j[1] = sqrtf(3) / 2;
	delta = sqrtf(delta);
	u = cbrtf(k[0] + delta);
	v = cbrtf(k[0] - delta);
	x[0] = u + v;
	x[1] = j[0] * x[0] - k[1];
	xi[1] = j[1] * (u - v);
	x[2] = x[1];
	xi[2] = j[1] * (v - u);
	x[0] -= k[1];
	return (x);
}

static float	*ft_cubic_zero(float p, float q, float *x, float *k)
{
	x[0] = 3 * q / p - k[1];
	x[1] = -3 * q / (2 * p) - k[1];
	x[2] = x[1];
	return (x);
}

float			*ft_cubic_equation2(float *d, float *xi)
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
	p = d[1] - d[3] / 3;
	q = d[2] / 27 * (2 * d[3] - 9 * d[1]) + d[0];
	delta = powf(q / 2, 2) + powf(p / 3, 3);
	xi[2] = 0;
	xi[1] = 0;
	xi[0] = 0;
	k[0] = 0 - q / 2;
	k[1] = d[2] / 3;
	if (fabsf(delta) < EPSILON)
		return (ft_cubic_zero(p, q, x, k));
	else if (delta > 0)
		return (ft_cubic_positive(delta, x, xi, k));
	return (ft_cubic_negative(p, x, k));
}

float			*ft_cubic_equation(float *d, float *xi)
{
	static float	x[3];
	float			delta;
	float			k[3];
	float			q;
	float			r;

	xi[0] = 0;
	d[0] /= d[3];
	d[1] /= d[3];
	d[2] /= d[3];
	q = (d[2] * d[2] - 3 * d[1]) / 9;
	r = (d[2] * (d[2] * d[2] - 4.5 * d[1]) + 13.5 * d[0]) / 27;
	delta = q * q * q - r * r;
	k[2] = -d[2] / 3;
	if (delta >= 0)
	{
		k[0] = acosf(r / powf(q, 1.5)) / 3;
		k[1] = -2 * powf(q, 0.5);
		x[0] = k[1] * cosf(k[0]) + k[2];
		x[1] = k[1] * cosf(k[0] + M_PI / 1.5) + k[2];
		x[2] = k[1] * cosf(k[0] + M_PI / 0.75) + k[2];
		xi[1] = 0;
		xi[2] = 0;
		return (x);
	}
	k[1] = cbrtf(sqrtf(-delta) + fabs(r));
	x[1] = -1;
	x[2] = -1;
	xi[1] = -1;
	xi[2] = -1;
	if (r < 0)
		x[0] = k[2] + k[1] + q / k[1];
	else
		x[0] = k[2] - k[1] - q / k[1];
	return(x);
}

int				ft_cubic_roots(float *x, float *xi)
{
	if (fabs(xi[0]) >= EPSILON)
		x[0] = -1;
	if (fabs(xi[1]) >= EPSILON)
		x[1] = -1;
	if (fabs(xi[2]) >= EPSILON)
		x[2] = -1;
	if ((x[0] > x[1]) && (x[1] >= EPSILON))
		x[0] = x[1];
	if ((x[0] > x[2]) && (x[2] >= EPSILON))
		x[0] = x[2];
	if (x[0] < EPSILON)
		return (0);
	return (1);
}