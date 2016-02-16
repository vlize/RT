/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_calc_lux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 09:23:06 by vlize             #+#    #+#             */
/*   Updated: 2016/02/16 09:53:00 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

static void	ft_ambient_light(int *color, t_env *env)
{
	color[0] = env->obj0->red * AMBIANT;
	color[1] = env->obj0->green * AMBIANT;
	color[2] = env->obj0->blue * AMBIANT;
	color[3] = (env->obj0->red - color[0]) / env->spot_nbr;
	color[4] = (env->obj0->green - color[1]) / env->spot_nbr;
	color[5] = (env->obj0->blue - color[2]) / env->spot_nbr;
}

static void	ft_specular_highlight(int *color, float *k, float *n, t_env *env)
{
	float	r[3];
	float	v[3];

	v[0] = 0 - env->vec0->vx;
	v[1] = 0 - env->vec0->vy;
	v[2] = 0 - env->vec0->vz;
	k[1] = 2 * k[0] * k[2] / k[3];
	r[0] = k[1] * n[0] - env->vec->vx;
	r[1] = k[1] * n[1] - env->vec->vy;
	r[2] = k[1] * n[2] - env->vec->vz;
	k[0] = (v[0] * r[0]) + (v[1] * r[1]) + (v[2] * r[2]);
	if (k[0] <= EPSILON)
		return ;
	k[2] = sqrtf(env->vec0->pow2_vx + env->vec0->pow2_vy + env->vec0->pow2_vz);
	k[3] = sqrtf(env->vec->pow2_vx + env->vec->pow2_vy + env->vec->pow2_vz);
	if ((k[1] = k[2] * k[3]) <= EPSILON)
		return ;
	if ((k[0] /= k[1]) > 1)
		k[0] = 1;
	k[1] = env->specular_coef * powf(k[0], SPECULAR_POW);
	color[0] += k[1];
	color[1] += k[1];
	color[2] += k[1];
}

static void	ft_diffuse_light(int *color, t_env *env)
{
	t_vec	*lux;
	float	n[6];
	float	k[4];

	ft_normal(n, env);
	lux = env->vec;
	k[0] = (lux->vx * n[0]) + (lux->vy * n[1]) + (lux->vz * n[2]);
	if (k[0] <= EPSILON)
		return ;
	k[2] = sqrtf(lux->pow2_vx + lux->pow2_vy + lux->pow2_vz);
	k[3] = sqrtf(n[3] + n[4] + n[5]);
	if ((k[1] = k[2] * k[3]) <= EPSILON)
		return ;
	k[0] /= k[1];
	color[0] += color[3] * k[0];
	color[1] += color[4] * k[0];
	color[2] += color[5] * k[0];
	return (ft_specular_highlight(color, k, n, env));
}

static void	ft_lux_collision(int *color, t_env *env)
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
	return (ft_diffuse_light(color, env));
}

void		ft_lux_tracing(int *color, float *pt, t_env *env)
{
	if (!env->obj0)
		return ;
	ft_ambient_light(color, env);
	env->spot0 = env->spot;
	env->vec->px = pt[0];
	env->vec->py = pt[1];
	env->vec->pz = pt[2];
	env->vec->pow2_px = powf(pt[0], 2);
	env->vec->pow2_py = powf(pt[1], 2);
	env->vec->pow2_pz = powf(pt[2], 2);
	while (env->spot0)
	{
		env->vec->vx = env->spot0->px - pt[0];
		env->vec->vy = env->spot0->py - pt[1];
		env->vec->vz = env->spot0->pz - pt[2];
		env->vec->pow2_vx = powf(env->vec->vx, 2);
		env->vec->pow2_vy = powf(env->vec->vy, 2);
		env->vec->pow2_vz = powf(env->vec->vz, 2);
		ft_lux_collision(color, env);
		env->spot0 = env->spot0->next;
	}
}
