/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:52:54 by vlize             #+#    #+#             */
/*   Updated: 2016/03/04 09:47:09 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

float	*ft_plane(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[3];
	float			k[2];

	ft_set_pt0(pt0, NULL, vec);
	k[1] = obj->a * vec->vx + obj->b * vec->vy;
	if (fabs(k[1] += obj->c * vec->vz) < EPSILON)
		return (NULL);
	k[0] = obj->a * pt0[0] + obj->b * pt0[1] + obj->c * pt0[2] + obj->d;
	if ((k[0] = 0 - (k[0] / k[1])) < EPSILON)
		return (NULL);
	pt1[0] = vec->vx * k[0] + vec->px;
	pt1[1] = vec->vy * k[0] + vec->py;
	pt1[2] = vec->vz * k[0] + vec->pz;
	return (pt1);
}

float	*ft_sphere(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[3];
	float			deg[3];
	float			*k;

	ft_set_pt0(pt0, obj, vec);
	deg[2] = vec->pow2_vx + vec->pow2_vy + vec->pow2_vz;
	deg[1] = vec->vx * pt0[0] + vec->vy * pt0[1];
	deg[1] = (deg[1] + vec->vz * pt0[2]) * 2;
	deg[0] = powf(pt0[0], 2) + powf(pt0[1], 2) + powf(pt0[2], 2) - obj->pow2_r;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	pt1[0] = vec->vx * k[0] + vec->px;
	pt1[1] = vec->vy * k[0] + vec->py;
	pt1[2] = vec->vz * k[0] + vec->pz;
	return (pt1);
}

float	*ft_cylinder(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[3];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	deg[2] = v0[3] + v0[4];
	deg[1] = (v0[0] * pt0[0] + v0[1] * pt0[1]) * 2;
	deg[0] = pt0[3] + pt0[4] - obj->pow2_r;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float	*ft_cone(t_obj *obj, t_vec *vec)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[3];
	float			*k;

	ft_set_v0(v0, vec);
	ft_rot_v0_pt0(v0, pt0, obj, vec);
	deg[2] = v0[3] + v0[4] - v0[5] * obj->tan2_r;
	deg[1] = v0[0] * pt0[0] + v0[1] * pt0[1] - v0[2] * pt0[2] * obj->tan2_r;
	deg[1] *= 2;
	deg[0] = pt0[3] + pt0[4] - pt0[5] * obj->tan2_r;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}
