/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/02/15 11:35:28 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

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
	cam->pow2_px = powf(cam->px, 2);
	cam->pow2_py = powf(cam->py, 2);
	cam->pow2_pz = powf(cam->pz, 2);
}

static int	ft_is_object(char *str)
{
	if (!ft_strcmp(str, SPHERE) || !ft_strcmp(str, PLANE))
		return (1);
	if (!ft_strcmp(str, CYLINDER) || !ft_strcmp(str, CONE))
		return (1);
	if (!ft_strcmp(str, TORE) || !ft_strcmp(str, HYPERBOLOID))
		return (1);
	if (!ft_strcmp(str, PARABOLOID) || !ft_strcmp(str, ELLIPSOID))
		return (1);
	if (!ft_strcmp(str, MOBIUS_STRIP))
		return (1);
	return (0);
}

void		ft_read_file(t_env *env)
{
	ft_make_cam(env->cam, env);
	while (ft_inc_gnl(env) > 0)
	{
		if (!ft_strcmp(env->line, SPOT))
			ft_make_spot(env);
		else if (ft_is_object(env->line))
			ft_make_obj(env);
		if (env->line && (env->line[0] != '\0') && (env->line[0] != '#'))
			exit(ft_put_error(env->name, INVALID, env));
	}
	if (env->gnl < 0)
		exit(ft_perror(GNL, env));
	if (!env->spot_nbr)
		env->spot_nbr++;
	env->specular_coef = LIGHT_INT / env->spot_nbr;
}
