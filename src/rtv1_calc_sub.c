/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_calc_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:18:18 by vlize             #+#    #+#             */
/*   Updated: 2016/02/16 09:39:52 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

void	ft_set_v0(float *v0, t_vec *vec)
{
	if (!v0 || !vec)
		return ;
	v0[0] = vec->vx;
	v0[1] = vec->vy;
	v0[2] = vec->vz;
}

void	ft_set_pt0(float *pt0, t_obj *obj, t_vec *vec)
{
	if (!pt0 || !vec)
		return ;
	if (obj)
	{
		pt0[0] = vec->px - obj->px;
		pt0[1] = vec->py - obj->py;
		pt0[2] = vec->pz - obj->pz;
		return ;
	}
	pt0[0] = vec->px;
	pt0[1] = vec->py;
	pt0[2] = vec->pz;
}

void	ft_rot_v0_pt0(float *v0, float *pt0, t_obj *obj, t_vec *vec)
{
	if (!v0 || !pt0 || !obj || !vec)
		return ;
	ft_vector_rotation(v0, NULL, obj, 1);
	ft_vector_rotation(pt0, vec, obj, 1);
	v0[3] = powf(v0[0], 2);
	v0[4] = powf(v0[1], 2);
	v0[5] = powf(v0[2], 2);
	pt0[3] = powf(pt0[0], 2);
	pt0[4] = powf(pt0[1], 2);
	pt0[5] = powf(pt0[2], 2);
}

float	*ft_rot_pt1(float *pt1, t_obj *obj)
{
	if (!pt1 || !obj)
		return (pt1);
	ft_vector_rotation(pt1, NULL, obj, 0);
	pt1[0] += obj->px;
	pt1[1] += obj->py;
	pt1[2] += obj->pz;
	return (pt1);
}

void	ft_normal_direction(float *n, t_vec *vec)
{
	float	k;

	k = (vec->vx * n[0]) + (vec->vy * n[1]) + (vec->vz * n[2]);
	if (k <= 0)
		return ;
	n[0] = 0 - n[0];
	n[1] = 0 - n[1];
	n[2] = 0 - n[2];
}
