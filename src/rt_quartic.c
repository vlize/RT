/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_quartic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 08:10:30 by vlize             #+#    #+#             */
/*   Updated: 2016/03/10 16:27:37 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static void		ft_quartic_init2(float *d, float *d0, float *k)
{
	float			a;
	float			b;
	float			c;

	d[3] /= d[4];
	d[2] /= d[4];
	d[1] /= d[4];
	d[0] /= d[4];
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

static void		ft_quartic_result2(float *x, float *y, float *yi, float *k)
{
	float	xi[4];

	y[0] = sqrtf(y[0]);
	ft_complex_root(&y[1], &yi[1], 2, 0);
	ft_complex_root(&y[2], &yi[2], 2, 0);
	x[0] = (y[0] + y[1] + y[2]) / 2 - k[0];
	x[1] = (y[0] - y[1] - y[2]) / 2 - k[0];
	x[2] = (y[1] - y[0] - y[2]) / 2 - k[0];
	x[3] = (y[2] - y[0] - y[1]) / 2 - k[0];
	xi[0] = yi[1] + yi[2];
	xi[1] = 0 - yi[1] - yi[2];
	xi[2] = yi[1] - yi[2];
	xi[3] = yi[2] - yi[1];
	if (fabs(xi[0]) >= EPSILON)
		x[0] = -1;
	if (fabs(xi[1]) >= EPSILON)
		x[1] = -1;
	if (fabs(xi[2]) >= EPSILON)
		x[2] = -1;
	if (fabs(xi[3]) >= EPSILON)
		x[3] = -1;
}

float			*ft_quartic_equation2(float *d)
{
	static float	x[4];
	float			*y;
	float			yi[3];
	float			d0[4];
	float			k[2];

	if (fabsf(d[4]) < EPSILON)
	{
		if (fabsf(d[3]) < EPSILON)
			return (ft_quadratic_equation(d[2], d[1], d[0]));
		return (ft_cubic_equation(d, yi));
	}
	ft_quartic_init2(d, d0, k);
	if (!(y = ft_cubic_equation(d0, yi)))
		return (NULL);
	ft_quartic_result2(x, y, yi, k);
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

static void		ft_quartic_init(float *d, float *d0)
{
	d[3] /= d[4];
	d[2] /= d[4];
	d[1] /= d[4];
	d[0] /= d[4];
	d0[3] = 1;
	d0[2] = (3 * d[3] * d[3] / 8 - d[2]) / 2;
	d0[1] = powf(d[3], 4) * 3 / 256 - d[3] * d[3] * d[2] / 16 + d[3] * d[1] \
			/ 4 - d[0];
	d0[0] = powf(d[3], 3) / 16 - d[3] * d[2] / 4 + d[1] / 2;
	d0[0] = d0[2] * d0[1] - d0[0] * d0[0];
}

static void		ft_quartic_alpha(float *delta, float alpha, float *x, float a)
{
	if (alpha > 0)
	{
		x[0] = delta[2] * (sqrtf(delta[0]) + sqrtf(alpha)) / 2 - a / 4;
		x[1] = delta[2] * (sqrtf(delta[0]) - sqrtf(alpha)) / 2 - a / 4;
		return ;
	}
	x[0] = delta[2] * sqrtf(delta[0]) / 2 + a / 4;
	x[1] = delta[2] * sqrtf(delta[0]) / 2 + a / 4;
}

static float	*ft_quartic_roots(float *d, float *d0, float *x, float *y)
{
	float	delta[3];
	float	alpha;

	delta[0] = 2 * (y[0] + d0[2]);
	if (delta[0] < 0)
		return (NULL);
	else if (delta[0] > 0)
		delta[1] = sqrtf((d0[2] * d0[1] - d0[0]) / delta[0]);
	else if ((delta[1] = y[0] * y[0] + d0[1]) < 0)
		return (NULL);
	else
		delta[1] = sqrtf(delta[1]);
	x[0] = -1;
	x[1] = -1;
	x[2] = -1;
	x[3] = -1;
	delta[2] = -1;
	alpha = delta[0] - 4 * (y[0] - delta[1]);
	ft_quartic_alpha(delta, alpha, x, d[3]);
	delta[2] = 1;
	alpha = delta[0] - 4 * (y[0] + delta[1]);
	ft_quartic_alpha(delta, alpha, &x[2], d[3]);
	return (x);
}

float			*ft_quartic_equation(float *d)
{
	static float	x[4];
	float			*y;
	float			yi[3];
	float			d0[4];

	if (fabsf(d[4]) < EPSILON)
	{
		if (fabsf(d[3]) < EPSILON)
			return (ft_quadratic_equation(d[2], d[1], d[0]));
		return (ft_cubic_equation(d, yi));
	}
	ft_quartic_init(d, d0);
	if (!(y = ft_cubic_equation(d0, yi)))
		return (NULL);
	ft_quartic_roots(d, d0, x, y);
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
