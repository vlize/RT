/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_equation2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 08:10:30 by vlize             #+#    #+#             */
/*   Updated: 2016/03/09 15:53:41 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static float	*ft_cubic_result(float *d, float *x, float *xi)
{
	float			dlt2;

	dlt2 = powf(d[2] + x[0], 2) / 4 - ((d[2] + x[0]) * x[0] + d[1]);
	x[1] = (0 - d[2] - x[0]) / 2;
	x[2] = x[1];
	if (dlt2 >= EPSILON)
	{
		dlt2 = sqrtf(dlt2);
		x[1] -= dlt2;
		x[2] += dlt2;
	}
	else if (dlt2 <= EPSILON)
	{
		dlt2 = sqrtf(dlt2);
		xi[1] = 0 - dlt2;
		xi[2] = dlt2;
	}
	return (x);
}

float			*ft_cubic_equation(float *d, float *xi)
{
	static float	x[3];
	float			dlt1;
	float			p;
	float			q;

	if ((fabsf(d[4]) < EPSILON) && (fabsf(d[3]) < EPSILON))
		return (ft_quadratic_equation(d[2], d[1], d[0]));
	d[0] /= d[3];
	d[1] /= d[3];
	d[2] /= d[3];
	d[3] = powf(d[2], 2);
	p = d[1] - d[3] * 3;
	q = d[2] / 27 * (2 * d[3] - 9 * d[1]) + d[0];
	dlt1 = powf(q / 2, 2) + powf(p / 3, 3);
	xi[2] = 0;
	xi[1] = 0;
	xi[0] = 0;
	x[0] = 0 - q / 2;
	x[0] = cbrtf(x[0] - dlt1) + cbrtf(x[0] - dlt1) - d[2] / 3;
	return (ft_cubic_result(d, x, xi));
}

static void		ft_quartic_init(float *d, float *d0, float *k)
{
	float			a;
	float			b;
	float			c;

	k[0] = d[3] / (4 * d[4]);
	k[1] = powf(k[0], 2);
	a = d[2] / d[4] - 6 * k[1];
	b = (2 * (k[1] - k[2]) + d[1]) / d[4];
	c = (d[2] - powf(d[3], 2) * 3 / 16) * k[1] - d[1] * k[0];
	d0[3] = 1;
	d0[2] = 2 * a;
	d0[1] = powf(a, 2) - 4 * c;
	d0[0] = 0 - powf(b, 2);
	k[1] = 0 - b;
}

static void		ft_quartic_result(float *x, float *y, float *yi, float *k)
{
	float	xi[4];

	y[0] = sqrtf(y[0]);
	ft_complex_roots(y, yi, k[1]);
	x[0] = (y[0] + y[1] + y[2]) / 2 - k[0];
	x[1] = (y[0] - y[1] - y[2]) / 2 - k[0];
	x[2] = (y[1] - y[0] - y[2]) / 2 - k[0];
	x[3] = (y[2] - y[0] - y[1]) / 2 - k[0];
	xi[0] = yi[1] + yi[2];
	xi[1] = 0 - yi[1] - yi[2];
	xi[2] = yi[1] - yi[2];
	xi[3] = yi[2] - yi[1];
	if (fabs(xi[0]) < EPSILON)
		x[0] = -1;
	if (fabs(xi[1]) < EPSILON)
		x[1] = -1;
	if (fabs(xi[2]) < EPSILON)
		x[2] = -1;
	if (fabs(xi[3]) < EPSILON)
		x[3] = -1;
}

float			*ft_quartic_equation(float *d)
{
	static float	x[4];
	float			*y;
	float			yi[3];
	float			d0[4];
	float			k[2];

	if (fabsf(d[4]) < EPSILON)
		return (ft_cubic_equation(d, yi));
	ft_quartic_init(d, d0, k);
	if (!(y = ft_cubic_equation(d0, yi)))
		return (NULL);
	ft_quartic_result(x, y, yi, k);
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
