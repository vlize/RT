/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_mobius.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 11:06:18 by vlize             #+#    #+#             */
/*   Updated: 2016/03/03 08:38:55 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static int	ft_mobius_strip0(float *pt1, float *pt0, float *v0, float *k)
{
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (0);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (1);
}

float		*ft_mobius_strip(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[4];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	deg[3] = v0[4] * (v0[1] - 2 * v0[2]) + v0[1] * (v0[0] + v0[2]);
	deg[3] -= 2 * (v0[3] * v0[2]);
	deg[0] = pt0[0] * v0[0] - pt0[2] + v0[2];
	deg[2] = v0[1] * deg[0] - v0[3] * (pt0[2] + v0[2]) + v0[0] * v0[2];
	deg[2] = 2 * deg[2] + pt0[1] * (3 * v0[4] + v0[3] - v0[5]);
	deg[1] = pt0[1] * deg[0] - v0[2] * (pt0[3] + pt0[0] + pt0[4]);
	deg[1] -= pt0[2] * v0[0] * (2 * pt0[0] + 1);
	deg[1] = 2 * deg[1] + v0[2] * (3 * pt0[4] + pt0[3] + pt0[5] - obj->pow2_a);
	deg[0] = pt0[4] * (pt0[1] - 2 * pt0[2]);
	deg[0] += pt0[1] * (pt0[3] + pt0[5] - obj->pow2_a);
	deg[0] -= 2 * pt0[0] * pt0[2] * (pt0[0] + 1);
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	if (!ft_mobius_strip0(pt1, pt0, v0, k))
		return (NULL);
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
	n[1] -= env->obj0->pow2_a;
	n[2] = 2 * (p[1] * p[2] - pow2_p[1] - pow2_p[0] - env->obj0->d * p[0]);
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}
