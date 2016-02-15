/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_calc_spot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 10:38:16 by vlize             #+#    #+#             */
/*   Updated: 2016/02/15 11:37:28 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

static void	ft_spot_light(int *color, float *k, t_env *env)
{
	k[0] = (env->vec0->vx * env->vec->vx) + (env->vec0->vy * env->vec->vy);
	if ((k[0] += env->vec0->vz * env->vec->vz) <= EPSILON)
		return ;
	if ((k[1] = k[2] * sqrtf(k[3])) <= EPSILON)
		return ;
	if ((k[0] /= k[1]) > 1)
		k[0] = 1;
	k[1] = SPOT_LIGHT_INT * powf(k[0], SPOT_LIGHT_POW);
	color[0] += k[1];
	color[1] += k[1];
	color[2] += k[1];
}

static void	ft_spot_collision(int *color, float *k, t_env *env)
{
	float	pt[4];
	float	*pt1;
	t_obj	*obj;
	int		i;

	i = 0;
	pt[3] = env->vec->pow2_vx + env->vec->pow2_vy + env->vec->pow2_vz;
	obj = env->obj;
	while (obj)
	{
		pt1 = ft_ray_collision(obj, env->vec);
		if (ft_nearest_point(pt, pt1, env->vec))
			i = 1;
		obj = obj->next;
	}
	if (i)
		return ;
	k[3] = pt[3];
	return (ft_spot_light(color, k, env));
}

void		ft_spot_tracing(int *color, t_env *env)
{
	float	k[4];

	env->spot0 = env->spot;
	env->vec->px = env->vec0->px;
	env->vec->py = env->vec0->py;
	env->vec->pz = env->vec0->pz;
	env->vec->pow2_px = env->vec0->pow2_px;
	env->vec->pow2_py = env->vec0->pow2_py;
	env->vec->pow2_pz = env->vec0->pow2_pz;
	k[2] = sqrtf(env->vec0->pow2_vx + env->vec0->pow2_vy + env->vec0->pow2_vz);
	while (env->spot0)
	{
		env->vec->vx = env->spot0->px - env->vec->px;
		env->vec->vy = env->spot0->py - env->vec->py;
		env->vec->vz = env->spot0->pz - env->vec->pz;
		env->vec->pow2_vx = powf(env->vec->vx, 2);
		env->vec->pow2_vy = powf(env->vec->vy, 2);
		env->vec->pow2_vz = powf(env->vec->vz, 2);
		ft_spot_collision(color, k, env);
		env->spot0 = env->spot0->next;
	}
}
