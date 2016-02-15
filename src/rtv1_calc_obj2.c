/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_calc_obj2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 14:54:28 by vlize             #+#    #+#             */
/*   Updated: 2016/02/15 11:37:58 by vlize            ###   ########.fr       */
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
	float			k[2];

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	k[1] = v0[3] * pt0[3] / obj->pow2_d;
	k[1] += obj->sign * (v0[4] * pt0[4] / obj->pow2_e);
	if (fabs(k[1]) < EPSILON)
		return (NULL);
	k[0] = (v0[2] * pt0[2]) / (obj->f * k[1]);
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
	obj->a = (v0[3] * pt0[3] / obj->pow2_e) + (v0[4] * pt0[4] / obj->pow2_d);
	obj->a -= v0[5] * pt0[5] / obj->pow2_f;
	if (!(k = ft_quadratic_equation(obj->a, 0, obj->sign)))
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
	obj->a = (v0[3] * pt0[3] / obj->pow2_e) + (v0[4] * pt0[4] / obj->pow2_d);
	obj->a += v0[5] * pt0[5] / obj->pow2_f;
	if (!(k = ft_quadratic_equation(obj->a, 0, -1)))
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
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	obj->a = (v0[3] * pt0[3]) + (v0[4] * pt0[4]) + (v0[5] * pt0[5]);
	obj->b = v0[2] * pt0[2] * ((v0[3] * pt0[3]) + (v0[4] * pt0[4]));
	obj->a = (v0[1] * pt0[1] * obj->a) - (2 * obj->b);
	obj->b = -2 * obj->r * v0[0] * pt0[0] * v0[2] * pt0[2];
	obj->c = -obj->pow2_r * v0[1] * pt0[1];
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
