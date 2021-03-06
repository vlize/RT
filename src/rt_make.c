/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_make.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:51:46 by vlize             #+#    #+#             */
/*   Updated: 2016/03/10 13:59:21 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

static void	ft_set_not_null(char *str, float *nbr, t_env *env)
{
	ft_set_nbr(0, str, nbr, env);
	if (*nbr != 0)
		return ;
	env->line_nbr--;
	exit(ft_put_error(env->name, INVALID, env));
}

static void	ft_make_obj2(t_obj *obj, t_env *env)
{
	obj->sign = 1;
	if (obj->type == HYPERBOLOID)
	{
		if (!ft_strcmp(env->line, "one sheet"))
			obj->sign = -1;
		else if (ft_strcmp(env->line, "two sheets"))
			exit(ft_put_error(env->name, INVALID, env));
		ft_inc_gnl(env);
		return ;
	}
	if (!ft_strcmp(env->line, "hyperbolic"))
		obj->sign = -1;
	else if (ft_strcmp(env->line, "elliptic"))
		exit(ft_put_error(env->name, INVALID, env));
	ft_inc_gnl(env);
}

static void	ft_make_obj1(t_obj *obj, t_env *env)
{
	ft_set_not_null(A, &obj->a, env);
	ft_set_not_null(B, &obj->b, env);
	ft_set_not_null(C, &obj->c, env);
	obj->pow2_a = powf(obj->a, 2);
	obj->pow2_b = powf(obj->b, 2);
	obj->pow2_c = powf(obj->c, 2);
	if (obj->type != PARABOLOID)
	{
		ft_set_not_null(R, &obj->r, env);
		obj->pow2_r = powf(obj->r, 2);
	}
	if (obj->type != ELLIPSOID)
		return (ft_make_obj2(obj, env));
}

static void	ft_make_obj0(t_obj *obj, t_env *env)
{
	t_obj *tmp;

	if (obj->type == CONE)
	{
		ft_set_nbr(1, R, &obj->r, env);
		obj->tan_r = tan(obj->r);
		obj->tan2_r = powf(obj->tan_r, 2);
	}
	else if (obj->type == TORUS)
	{
		ft_set_nbr(0, R, &obj->r, env);
		ft_set_nbr(0, RT, &obj->rt, env);
		obj->pow2_r = powf(obj->r, 2);
		obj->pow2_rt = powf(obj->rt, 2);
	}
	else if (ft_end_with_oid(obj->type))
		ft_make_obj1(obj, env);
	else if (obj->type != PLANE)
	{
		ft_set_nbr(0, R, &obj->r, env);
		obj->pow2_r = powf(obj->r, 2);
	}
	tmp = env->obj;
	env->obj = obj;
	obj->next = tmp;
}

void		ft_make_obj(t_env *env, int type)
{
	t_obj *obj;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		exit(ft_perror(MALLOC, env));
	obj->type = type;
	obj->next = NULL;
	obj->nbr = env->obj_nbr++;
	ft_inc_gnl(env);
	ft_set_hex(obj, env);
	ft_set_nbr(0, PX, &obj->px, env);
	ft_set_nbr(0, PY, &obj->py, env);
	ft_set_nbr(0, PZ, &obj->pz, env);
	if (obj->type != SPHERE)
	{
		ft_set_nbr(2, RX, obj->rx, env);
		ft_set_nbr(2, RY, obj->ry, env);
		ft_set_nbr(2, RZ, obj->rz, env);
		ft_vector_equation(obj);
	}
	return (ft_make_obj0(obj, env));
}
