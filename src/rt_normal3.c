/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_normal3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:10:26 by vlize             #+#    #+#             */
/*   Updated: 2016/03/10 13:53:25 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static void	ft_mobius_strip_normal(float *n, t_env *env)
{
	float	p[3];
	float	pow2_p[3];

	ft_vector_rotation(p, env->vec, env->obj0, 1);
	pow2_p[0] = powf(p[0], 2);
	pow2_p[1] = powf(p[1], 2);
	pow2_p[2] = powf(p[2], 2);
	n[0] = 2 * (p[0] * (p[1] - 2 * p[2]) - env->obj0->d * p[2]);
	n[1] = 3 * pow2_p[1] - 2 * p[2] * p[1] + pow2_p[0] + pow2_p[2];
	n[1] -= env->obj0->pow2_r;
	n[2] = 2 * (p[1] * p[2] - pow2_p[1] - pow2_p[0] - env->obj0->d * p[0]);
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_ding_dong_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->vec, env->obj0, 1);
	n[0] *= 2;
	n[1] *= 2;
	n[2] = (3 * n[2] - 2) * n[2];
	ft_vector_rotation(n, NULL, env->obj0, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

void		ft_normal3(float *n, t_env *env)
{
	if (env->obj0->type == MOBIUS_STRIP)
		ft_mobius_strip_normal(n, env);
	else
		ft_ding_dong_normal(n, env);
	ft_normal_direction(n, env->vec0);
}
