/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_normal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 14:58:06 by vlize             #+#    #+#             */
/*   Updated: 2016/03/10 13:14:04 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static void	ft_plane_normal(float *n, t_env *env)
{
	n[0] = env->obj0->a;
	n[1] = env->obj0->b;
	n[2] = env->obj0->c;
	n[3] = env->obj0->pow2_a;
	n[4] = env->obj0->pow2_b;
	n[5] = env->obj0->pow2_c;
}

static void	ft_sphere_normal(float *n, t_env *env)
{
	n[0] = env->vec->px - env->obj0->px;
	n[1] = env->vec->py - env->obj0->py;
	n[2] = env->vec->pz - env->obj0->pz;
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_cylinder_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->vec, env->obj0, 1);
	n[2] = 0;
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_cone_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->vec, env->obj0, 1);
	n[3] = env->obj0->tan_r * hypot(n[0], n[1]);
	if (n[2] < 0)
		n[2] = n[3];
	else
		n[2] = 0 - n[3];
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

void		ft_normal(float *n, t_env *env)
{
	if (env->obj0->type == PLANE)
		ft_plane_normal(n, env);
	else if (env->obj0->type == SPHERE)
		ft_sphere_normal(n, env);
	else if (env->obj0->type == CONE)
		ft_cone_normal(n, env);
	else if (env->obj0->type == CYLINDER)
		ft_cylinder_normal(n, env);
	else
		return (ft_normal2(n, env));
	ft_normal_direction(n, env->vec0);
}
