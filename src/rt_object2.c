/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 14:54:28 by vlize             #+#    #+#             */
/*   Updated: 2016/03/09 15:11:27 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static void	ft_torus0(t_obj *obj, float *pt, float *v, float *d)
{
	float	pow2[4];
	float	ptv[5];
	float	r[2];

	r[0] = obj->pow2_rt - obj->pow2_r;
	r[1] = obj->pow2_rt + obj->pow2_r;
	ptv[0] = pt[0] * v[0];
	ptv[1] = pt[1] * v[1];
	ptv[2] = pt[2] * v[2];
	ptv[3] = ptv[0] + ptv[1];
	ptv[4] = ptv[3] + ptv[2];
	pow2[0] = v[3] + v[4];
	pow2[1] = pow2[0] + v[5];
	pow2[2] = pt[3] + pt[4];
	pow2[3] = pow2[0] + pt[5];
	d[4] = powf(v[0], 4) + powf(v[1], 4) + powf(v[2], 4);
	d[4] += 2 * (v[3] * v[4] + v[3] * v[5] + v[4] * v[5]);
	d[3] = 4 * pow2[1] * ptv[4];
	d[2] = (2 * pt[3] + pow2[3] - r[1]) * v[3];
	d[2] += (2 * pt[4] + pow2[3] - r[1]) * v[4];
	d[2] += (2 * pt[5] + pow2[3] + r[0]) * v[5];
	d[2] = 2 * d[2] + 8 * (ptv[0] * ptv[1] + ptv[0] * ptv[2] + ptv[1] * ptv[2]);
	d[1] = 4 * (pow2[3] * ptv[4] + r[0] * ptv[2] - r[1] * ptv[3]);
	d[0] = powf(pt[0], 4) + powf(pt[1], 4) + powf(pt[2], 4);
	d[0] += 2 * (pt[3] * pt[4] + r[0] * pt[5] + pow2[2] * (pt[5] - r[1]));
}

float		*ft_torus(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			degree[5];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	ft_torus0(obj, pt0, v0, degree);
	if (!(k = ft_quartic_equation(degree)))
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float		*ft_paraboloid(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[3];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	deg[2] = v0[3] / obj->pow2_a + obj->sign * v0[4] / obj->pow2_b;
	deg[1] = v0[0] * pt0[0] / obj->pow2_a;
	deg[1] += obj->sign * v0[1] * pt0[1] / obj->pow2_b;
	deg[1] = deg[1] * 2 - v0[2] / obj->c;
	deg[0] = pt0[3] / obj->pow2_a + obj->sign * pt0[4] / obj->pow2_b;
	deg[0] -= pt0[2] / obj->c;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float		*ft_hyperboloid(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[3];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	deg[2] = v0[3] / obj->pow2_a + v0[4] / obj->pow2_b - v0[5] / obj->pow2_c;
	deg[1] = v0[0] * pt0[0] / obj->pow2_a + v0[1] * pt0[1] / obj->pow2_b;
	deg[1] = (deg[1] - v0[2] * pt0[2] / obj->pow2_c) * 2;
	deg[0] = pt0[3] / obj->pow2_a + pt0[4] / obj->pow2_b;
	deg[0] += obj->sign * obj->pow2_r - pt0[5] / obj->pow2_c;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float		*ft_ellipsoid(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[3];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	deg[2] = v0[3] / obj->pow2_a + v0[4] / obj->pow2_b + v0[5] / obj->pow2_c;
	deg[1] = v0[0] * pt0[0] / obj->pow2_a + v0[1] * pt0[1] / obj->pow2_b;
	deg[1] = (deg[1] + v0[2] * pt0[2] / obj->pow2_c) * 2;
	deg[0] = pt0[3] / obj->pow2_a + pt0[4] / obj->pow2_b;
	deg[0] += pt0[5] / obj->pow2_c - obj->pow2_r;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}
