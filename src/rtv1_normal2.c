/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_normal2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 14:16:08 by vlize             #+#    #+#             */
/*   Updated: 2016/02/15 12:09:48 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

static void	ft_tore_normal(float *n, t_env *env)
{
	float	k;

	n[0] = env->vec->px - env->obj0->px;
	n[1] = env->vec->py - env->obj0->py;
	n[2] = env->vec->pz - env->obj0->pz;
	ft_rotation_matrix(&n[0], &n[1], env->obj0->rz, 1);
	ft_rotation_matrix(&n[2], &n[0], env->obj0->ry, 1);
	ft_rotation_matrix(&n[1], &n[2], env->obj0->rx, 1);
	k = 0;
	if (n[0] || n[1])
		k = 1 - sqrtf(env->obj0->rt / (hypot(n[0], n[1])));
	n[0] *= k;
	n[1] *= k;
	ft_rotation_matrix(&n[1], &n[2], env->obj0->rx, 0);
	ft_rotation_matrix(&n[2], &n[0], env->obj0->ry, 0);
	ft_rotation_matrix(&n[0], &n[1], env->obj0->rz, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_paraboloid_normal(float *n, t_env *env)
{
	n[0] = env->vec->px - env->obj0->px;
	n[1] = env->vec->py - env->obj0->py;
	n[2] = env->vec->pz - env->obj0->pz;
	ft_rotation_matrix(&n[0], &n[1], env->obj0->rz, 1);
	ft_rotation_matrix(&n[2], &n[0], env->obj0->ry, 1);
	ft_rotation_matrix(&n[1], &n[2], env->obj0->rx, 1);
	n[0] = 2 * n[0] / env->obj0->pow2_d;
	n[1] = env->obj0->sign * 2 * n[1] / env->obj0->pow2_e;
	n[2] = -1 / env->obj0->f;
	ft_rotation_matrix(&n[1], &n[2], env->obj0->rx, 0);
	ft_rotation_matrix(&n[2], &n[0], env->obj0->ry, 0);
	ft_rotation_matrix(&n[0], &n[1], env->obj0->rz, 0);
}

static void	ft_hyperboloid_normal(float *n, t_env *env)
{
	n[0] = env->vec->px - env->obj0->px;
	n[1] = env->vec->py - env->obj0->py;
	n[2] = env->vec->pz - env->obj0->pz;
	ft_rotation_matrix(&n[0], &n[1], env->obj0->rz, 1);
	ft_rotation_matrix(&n[2], &n[0], env->obj0->ry, 1);
	ft_rotation_matrix(&n[1], &n[2], env->obj0->rx, 1);
	n[0] = 2 * n[0] / env->obj0->pow2_d;
	n[1] = 2 * n[1] / env->obj0->pow2_e;
	n[2] = -2 * n[2] / env->obj0->pow2_f;
	ft_rotation_matrix(&n[1], &n[2], env->obj0->rx, 0);
	ft_rotation_matrix(&n[2], &n[0], env->obj0->ry, 0);
	ft_rotation_matrix(&n[0], &n[1], env->obj0->rz, 0);
}

static void	ft_mobius_strip_normal(float *n, t_env *env)
{
	if (n && env)
		return ;
}

void		ft_normal2(float *n, t_env *env)
{
	if (!ft_strcmp(env->obj0->type, TORE))
		ft_tore_normal(n, env);
	else if (!ft_strcmp(env->obj0->type, PARABOLOID))
		ft_paraboloid_normal(n, env);
	else if (!ft_strcmp(env->obj0->type, HYPERBOLOID))
		ft_hyperboloid_normal(n, env);
	else if (!ft_strcmp(env->obj0->type, MOBIUS_STRIP))
		ft_mobius_strip_normal(n, env);
}
