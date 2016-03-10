/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 12:48:38 by vlize             #+#    #+#             */
/*   Updated: 2016/03/10 13:22:28 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

float		*ft_ding_dong(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			d[5];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	d[3] = pow(v0[2], 3);
	d[0] = 3 * pt0[2] - 1;
	d[2] = v0[3] + v0[4] + v0[5] * d[0];
	d[1] = pt0[0] * v0[0] + pt0[1] * v0[1] + pt0[2] * v0[2] * d[0];
	d[0] = pt0[3] + pt0[4] - pt0[5] + pow(pt0[2], 3);
	if (!(k = ft_cubic_equation(d, &d[4])))
		return (NULL);
	if (!ft_cubic_roots(k, &d[4]))
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

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
	if (!ft_cubic_roots(k, &d[4]))
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}
