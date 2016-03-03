/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/03/03 08:39:11 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static void	ft_make_spot(t_env *env)
{
	t_spot	*spot;
	t_spot	*tmp;

	if (!(spot = (t_spot *)malloc(sizeof(t_spot))))
		exit(ft_perror(MALLOC, env));
	spot->next = NULL;
	ft_inc_gnl(env);
	ft_set_nbr(0, PX, &spot->px, env);
	ft_set_nbr(0, PY, &spot->py, env);
	ft_set_nbr(0, PZ, &spot->pz, env);
	env->spot_nbr++;
	tmp = env->spot;
	env->spot = spot;
	spot->next = tmp;
}

static void	ft_make_cam(t_cam *cam, t_env *env)
{
	while ((ft_inc_gnl(env) > 0) && ft_strcmp(env->line, CAM))
	{
		if (env->line && (env->line[0] != '\0') && (env->line[0] != '#'))
			exit(ft_put_error(env->name, INVALID, env));
	}
	if (env->gnl < 0)
		exit(ft_perror(GNL, env));
	else if (env->gnl == 0)
		exit(ft_put_error(env->name, INVALID, env));
	ft_inc_gnl(env);
	ft_set_nbr(0, PX, &cam->px, env);
	ft_set_nbr(0, PY, &cam->py, env);
	ft_set_nbr(0, PZ, &cam->pz, env);
	ft_set_nbr(2, RX, cam->rx, env);
	ft_set_nbr(2, RY, cam->ry, env);
	ft_set_nbr(2, RZ, cam->rz, env);
}

void		ft_read_file(t_env *env)
{
	int	type;

	ft_make_cam(env->cam, env);
	while (ft_inc_gnl(env) > 0)
	{
		if (!ft_strcmp(env->line, SPOT))
			ft_make_spot(env);
		else if ((type = ft_is_object(env->line)))
			ft_make_obj(env, type);
		if (env->line && (env->line[0] != '\0') && (env->line[0] != '#'))
			exit(ft_put_error(env->name, INVALID, env));
	}
	if (env->gnl < 0)
		exit(ft_perror(GNL, env));
	if (!env->spot_nbr)
		env->spot_nbr++;
	env->specular_coef = LIGHT_INT / env->spot_nbr;
}
