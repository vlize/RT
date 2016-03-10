/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_normal2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 14:16:08 by vlize             #+#    #+#             */
/*   Updated: 2016/03/10 13:14:15 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static void	ft_torus_normal(float *n, t_env *env)
{
	float	k;

	ft_vector_rotation(n, env->vec, env->obj0, 1);
	k = 0;
	if (n[0] || n[1])
		k = 1 - sqrtf(env->obj0->rt / (hypot(n[0], n[1])));
	n[0] *= k;
	n[1] *= k;
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_paraboloid_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->vec, env->obj0, 1);
	n[0] = 2 * n[0] / env->obj0->pow2_a;
	n[1] = env->obj0->sign * 2 * n[1] / env->obj0->pow2_b;
	n[2] = -1 / env->obj0->c;
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_hyperboloid_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->vec, env->obj0, 1);
	n[0] = 2 * n[0] / env->obj0->pow2_a;
	n[1] = 2 * n[1] / env->obj0->pow2_b;
	n[2] = -2 * n[2] / env->obj0->pow2_c;
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_ellipsoid_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->vec, env->obj0, 1);
	n[0] = 2 * n[0] / env->obj0->pow2_a;
	n[1] = 2 * n[1] / env->obj0->pow2_b;
	n[2] = 2 * n[2] / env->obj0->pow2_c;
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

void		ft_normal2(float *n, t_env *env)
{
	if (env->obj0->type == TORUS)
		ft_torus_normal(n, env);
	else if (env->obj0->type == PARABOLOID)
		ft_paraboloid_normal(n, env);
	else if (env->obj0->type == HYPERBOLOID)
		ft_hyperboloid_normal(n, env);
	else if (env->obj0->type == ELLIPSOID)
		ft_ellipsoid_normal(n, env);
	else
		return (ft_normal3(n, env));
	ft_normal_direction(n, env->vec0);
}
