/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_make_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:51:46 by vlize             #+#    #+#             */
/*   Updated: 2016/02/15 11:34:35 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

static int	ft_end_with_oid(char *str)
{
	if (!ft_strcmp(str, HYPERBOLOID))
		return (1);
	if (!ft_strcmp(str, PARABOLOID))
		return (1);
	if (!ft_strcmp(str, ELLIPSOID))
		return (1);
	return (0);
}

static void ft_set_not_null(char *str, float *nbr, t_env *env)
{
	ft_set_nbr(0, str, nbr, env);
	if (*nbr != 0)
		return ;
	env->line_nbr--;
	exit(ft_put_error(env->name, INVALID, env));
}

static void	ft_make_obj1(t_obj *obj, t_env *env)
{
	ft_set_not_null(A, &obj->d, env);
	ft_set_not_null(B, &obj->e, env);
	ft_set_not_null(C, &obj->f, env);
	obj->pow2_d = powf(obj->d, 2);
	obj->pow2_e = powf(obj->e, 2);
	obj->pow2_f = powf(obj->f, 2);
	obj->sign = 1;
	if (obj->type[0] == HYPERBOLOID[0])
	{
		if (!ft_strcmp(env->line, SHEET1))
			obj->sign = -1;
		else if (ft_strcmp(env->line, SHEET2))
			exit(ft_put_error(env->name, INVALID, env));
		ft_inc_gnl(env);
	}
	else if (obj->type[0] == PARABOLOID[0])
	{
		if (!ft_strcmp(env->line, HYPERBOLIC))
			obj->sign = -1;
		else if (ft_strcmp(env->line, ELLIPTIC))
			exit(ft_put_error(env->name, INVALID, env));
		ft_inc_gnl(env);
	}
}

static void	ft_make_obj0(t_obj *obj, t_env *env)
{
	t_obj *tmp;

	if (!ft_strcmp(obj->type, CONE))
	{
		ft_set_nbr(1, R, &obj->r, env);
		obj->tan_r = tan(obj->r);
		obj->tan2_r = powf(obj->tan_r, 2);
	}
	else if (!ft_strcmp(obj->type, TORE))
	{
		ft_set_nbr(0, R, &obj->r, env);
		ft_set_nbr(0, RT, &obj->rt, env);
		obj->pow2_r = powf(obj->r, 2);
		obj->pow2_rt = powf(obj->rt, 2);
	}
	else if (ft_end_with_oid(obj->type))
		ft_make_obj1(obj, env);
	else if (ft_strcmp(obj->type, PLANE))
	{
		ft_set_nbr(0, R, &obj->r, env);
		obj->pow2_r = powf(obj->r, 2);
	}
	tmp = env->obj;
	env->obj = obj;
	obj->next = tmp;
}

void		ft_make_obj(t_env *env)
{
	t_obj *obj;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		exit(ft_perror(MALLOC, env));
	if (!(obj->type = ft_strdup(env->line)))
		exit(ft_perror(MALLOC, env));
	obj->next = NULL;
	obj->nbr = env->obj_nbr++;
	ft_inc_gnl(env);
	ft_set_hex(obj, env);
	ft_set_nbr(0, PX, &obj->px, env);
	ft_set_nbr(0, PY, &obj->py, env);
	ft_set_nbr(0, PZ, &obj->pz, env);
	if (ft_strcmp(obj->type, SPHERE))
	{
		ft_set_nbr(2, RX, obj->rx, env);
		ft_set_nbr(2, RY, obj->ry, env);
		ft_set_nbr(2, RZ, obj->rz, env);
		ft_vector_equation(obj);
	}
	return (ft_make_obj0(obj, env));
}
