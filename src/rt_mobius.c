/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mobius.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 11:06:18 by vlize             #+#    #+#             */
/*   Updated: 2016/03/09 15:53:25 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static void	ft_cubic_init(float *d, float *pt0, float *v0, t_obj *obj)
{
	d[3] = v0[4] * (v0[1] - 2 * v0[2]) + v0[1] * (v0[0] + v0[2]);
	d[3] -= 2 * (v0[3] * v0[2]);
	d[0] = pt0[0] * v0[0] - pt0[2] + v0[2];
	d[2] = v0[1] * d[0] - v0[3] * (pt0[2] + v0[2]) + v0[0] * v0[2];
	d[2] = 2 * d[2] + pt0[1] * (3 * v0[4] + v0[3] - v0[5]);
	d[1] = pt0[1] * d[0] - v0[2] * (pt0[3] + pt0[0] + pt0[4]);
	d[1] -= pt0[2] * v0[0] * (2 * pt0[0] + 1);
	d[1] = 2 * d[1] + v0[2] * (3 * pt0[4] + pt0[3] + pt0[5] - obj->pow2_r);
	d[0] = pt0[4] * (pt0[1] - 2 * pt0[2]);
	d[0] += pt0[1] * (pt0[3] + pt0[5] - obj->pow2_r);
	d[0] -= 2 * pt0[0] * pt0[2] * (pt0[0] + 1);
}

static int	ft_check_result(float *x, float *xi)
{
	if (fabs(xi[0]) < EPSILON)
		x[0] = -1;
	if (fabs(xi[1]) < EPSILON)
		x[1] = -1;
	if (fabs(xi[2]) < EPSILON)
		x[2] = -1;
	if ((x[0] > x[1]) && (x[1] >= EPSILON))
		x[0] = x[1];
	if ((x[0] > x[2]) && (x[2] >= EPSILON))
		x[0] = x[2];
	if (x[0] < EPSILON)
		return (0);
	return (1);
}

float		*ft_mobius_strip(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			d[7];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	ft_cubic_init(d, pt0, v0, obj);
	if (!(k = ft_cubic_equation(d, &d[4])))
		return (NULL);
	if (!ft_check_result(k, &d[4]))
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

void		ft_mobius_strip_normal(float *n, t_env *env)
{
	float	p[3];
	float	pow2_p[3];

	ft_vector_rotation(p, env->vec, env->obj0, 1);
	pow2_p[0] = powf(p[0], 2);
	pow2_p[1] = powf(p[1], 2);
	pow2_p[2] = powf(p[2], 2);
	n[0] = 2 * (p[0] * (p[1] - 2 * p[2]) - env->obj0->d * p[2]);
	n[1] = 3 * pow2_p[1] - 2 * p[2] * p[1] + pow2_p[0] + pow2_p[2];
	n[1] -= env->obj0->pow2_r;
	n[2] = 2 * (p[1] * p[2] - pow2_p[1] - pow2_p[0] - env->obj0->d * p[0]);
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}
