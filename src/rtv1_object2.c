/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_object2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 14:54:28 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 08:44:50 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

float	*ft_tore(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	obj->a = v0[3] * pt0[3] + v0[4] * pt0[4] + v0[5] * pt0[5];
	obj->b = -2 * obj->rt * sqrtf(v0[3] * pt0[3] + v0[4] * pt0[4]);
	obj->c = obj->pow2_rt * obj->pow2_r;
	if (!(k = ft_quadratic_equation(obj->a, obj->b, obj->c)))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float	*ft_paraboloid(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	obj->a = v0[3] / obj->pow2_d + obj->sign * v0[4] / obj->pow2_e;
	obj->b = v0[0] * pt0[0] / obj->pow2_d;
	obj->b += obj->sign * v0[1] * pt0[1] / obj->pow2_e;
	obj->b = obj->b * 2 - v0[2] / obj->f;
	obj->c = pt0[3] / obj->pow2_d + obj->sign * pt0[4] / obj->pow2_e;
	obj->c -= pt0[2] / obj->f;
	if (!(k = ft_quadratic_equation(obj->a, obj->b, obj->c)))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float	*ft_hyperboloid(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	obj->a = v0[3] / obj->pow2_d + v0[4] / obj->pow2_e - v0[5] / obj->pow2_f;
	obj->b = v0[0] * pt0[0] / obj->pow2_d + v0[1] * pt0[1] / obj->pow2_e;
	obj->b = (obj->b - v0[2] * pt0[2] / obj->pow2_f) * 2;
	obj->c = pt0[3] * obj->pow2_d + pt0[4] / obj->pow2_e;
	obj->c += obj->sign - pt0[5] / obj->pow2_f;
	if (!(k = ft_quadratic_equation(obj->a, obj->b, obj->c)))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float	*ft_ellipsoid(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	obj->a = v0[3] / obj->pow2_d + v0[4] / obj->pow2_e + v0[5] / obj->pow2_f;
	obj->b = v0[0] * pt0[0] / obj->pow2_d + v0[1] * pt0[1] / obj->pow2_e;
	obj->b = (obj->b + v0[2] * pt0[2] / obj->pow2_f) * 2;
	obj->c = pt0[3] * obj->pow2_d + pt0[4] / obj->pow2_e;
	obj->c += pt0[5] / obj->pow2_f - 1;
	if (!(k = ft_quadratic_equation(obj->a, obj->b, obj->c)))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float	*ft_mobius_strip(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			d[4];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	d[3] = v0[4] * (v0[1] - 2 * v0[2]) + v0[1] * (v0[0] + v0[2]);
	d[3] -= 2 * (v0[3] * v0[2]);
	d[0] = pt0[0] * v0[0] - pt0[2] + v0[2];
	d[2] = v0[1] * d[0] - v0[3] * (pt0[2] + v0[2]) + v0[0] * v0[2];
	d[2] = 2 * d[2] + pt0[1] * (3 * v0[4] + v0[3] - v0[5]);
	d[1] = pt0[1] * d[0] - v0[2] * (pt0[3] + pt0[0] + pt0[4]);
	d[1] -= pt0[2] * v0[0] * (2 * pt0[0] + 1);
	d[1] = 2 * d[1] + v0[2] * (3 * pt0[4] + pt0[3] + pt0[5] - obj->pow2_d);
	d[0] = pt0[4] * (pt0[1] - 2 * pt0[2]);
	d[0] += pt0[1] * (pt0[3] + pt0[5] - obj->pow2_d);
	d[0] -= 2 * pt0[0] * pt0[2] * (pt0[0] + 1);
	if (!(k = ft_quadratic_equation(obj->a, obj->b, obj->c)))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}
