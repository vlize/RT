/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/02/15 11:33:42 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"
#include "mlx.h"

int			ft_nearest_point(float pt[4], float *pt1, t_vec *vec)
{
	float	k;

	if (!pt1)
		return (0);
	k = powf((pt1[0] - vec->px), 2) + powf((pt1[1] - vec->py), 2);
	k += powf((pt1[2] - vec->pz), 2);
	if (pt[3] <= k)
		return (0);
	pt[0] = pt1[0];
	pt[1] = pt1[1];
	pt[2] = pt1[2];
	pt[3] = k;
	return (1);
}

float		*ft_ray_collision(t_obj *obj, t_vec *vec)
{
	if (!obj || !vec)
		return (NULL);
	if (!ft_strcmp(obj->type, PLANE))
		return (ft_plane(obj, vec));
	else if (!ft_strcmp(obj->type, SPHERE))
		return (ft_sphere(obj, vec));
	else if (!ft_strcmp(obj->type, CYLINDER))
		return (ft_cylinder(obj, vec));
	else if (!ft_strcmp(obj->type, CONE))
		return (ft_cone(obj, vec));
	else if (!ft_strcmp(obj->type, TORE))
		return (ft_tore(obj, vec));
	else if (!ft_strcmp(obj->type, ELLIPSOID))
		return (ft_ellipsoid(obj, vec));
	else if (!ft_strcmp(obj->type, PARABOLOID))
		return (ft_paraboloid(obj, vec));
	else if (!ft_strcmp(obj->type, HYPERBOLOID))
		return (ft_hyperboloid(obj, vec));
	else if (!ft_strcmp(obj->type, MOBIUS_STRIP))
		return (ft_mobius_strip(obj, vec));
	return (NULL);
}

static void	ft_set_cam_vector(int i, int j, t_vec *vec0, t_cam *cam)
{
	vec0->px = cam->px;
	vec0->py = cam->py;
	vec0->pz = cam->pz;
	vec0->vx = cam->vx[i][j];
	vec0->vy = cam->vy[i][j];
	vec0->vz = cam->vz[i][j];
	vec0->pow2_px = cam->pow2_px;
	vec0->pow2_py = cam->pow2_py;
	vec0->pow2_pz = cam->pow2_pz;
	vec0->pow2_vx = cam->pow2_vx[i][j];
	vec0->pow2_vy = cam->pow2_vy[i][j];
	vec0->pow2_vz = cam->pow2_vz[i][j];
}

static void	ft_ray_tracing(int i, int j, int *color, t_env *env)
{
	float		pt[4];
	float		*pt1;
	t_obj		*obj;

	color[0] = RED_0;
	color[1] = BLUE_0;
	color[2] = GREEN_0;
	env->obj0 = NULL;
	pt[3] = DBL_MAX;
	obj = env->obj;
	ft_set_cam_vector(i, j, env->vec0, env->cam);
	while (obj)
	{
		pt1 = ft_ray_collision(obj, env->vec0);
		if (ft_nearest_point(pt, pt1, env->vec0))
			env->obj0 = obj;
		obj = obj->next;
	}
	return (ft_lux_tracing(color, pt, env));
}

void		ft_draw(t_env *env)
{
	int	color[6];
	int	pix;
	int	i;
	int	j;

	j = -1;
	pix = 0;
	while ((j += 1) < HEIGHT)
	{
		i = -1;
		while ((i += 1) < WIDTH)
		{
			ft_ray_tracing(i, j, color, env);
			ft_spot_tracing(color, env);
			ft_check_color(color);
			ft_memcpy(&env->addr[pix], &color[2], 1);
			ft_memcpy(&env->addr[pix + 1], &color[1], 1);
			ft_memcpy(&env->addr[pix + 2], &color[0], 1);
			pix += 4;
		}
	}
}
