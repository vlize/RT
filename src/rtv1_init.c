/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 09:36:58 by vlize             #+#    #+#             */
/*   Updated: 2016/02/15 11:34:15 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"
#include "mlx.h"

static void	ft_init_env0(t_env *env)
{
	int	l;

	if (!(env->vec0 = (t_vec *)malloc(sizeof(t_vec))))
		exit(ft_perror(MALLOC, env));
	if (!(env->vec = (t_vec *)malloc(sizeof(t_vec))))
		exit(ft_perror(MALLOC, env));
	if (!(env->cam = (t_cam *)malloc(sizeof(t_cam))))
		exit(ft_perror(MALLOC, env));
	if (!(env->mlx = mlx_init()))
		exit(ft_perror("mlx_init()", env));
	if (!(env->win = mlx_new_window(env->mlx, WIDTH, HEIGHT, PROG)))
		exit(ft_perror("mlx_new_window()", env));
	if (!(env->img = mlx_new_image(env->mlx, WIDTH, HEIGHT)))
		exit(ft_perror("mlx_new_image()", env));
	l = WIDTH * 4;
	if (!(env->addr = mlx_get_data_addr(env->img, &env->bpp, &l, &env->endian)))
		exit(ft_perror("mlx_get_data_addr()", env));
}

void		ft_init_env(t_env *env)
{
	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	env->addr = NULL;
	env->line = NULL;
	env->obj = NULL;
	env->cam = NULL;
	env->vec = NULL;
	env->vec0 = NULL;
	env->spot = NULL;
	env->spot_nbr = 0;
	env->line_nbr = 0;
	env->obj_nbr = 0;
	env->bpp = 4 * CHAR_BIT;
	env->endian = ft_endian();
	return (ft_init_env0(env));
}

void		ft_init_vector(t_cam *cam, t_env *env)
{
	int		i;
	int		j;

	env->width_2 = WIDTH / 2;
	env->height_2 = HEIGHT / 2;
	env->depth = env->height_2 / tan(FOV_2);
	i = -1;
	while ((i += 1) < WIDTH)
	{
		j = -1;
		while ((j += 1) < HEIGHT)
		{
			cam->vx[i][j] = env->depth;
			cam->vy[i][j] = env->width_2 - i;
			cam->vz[i][j] = env->height_2 - j;
			ft_rotation_matrix(&cam->vx[i][j], &cam->vy[i][j], cam->rz, 0);
			ft_rotation_matrix(&cam->vy[i][j], &cam->vz[i][j], cam->rx, 0);
			ft_rotation_matrix(&cam->vz[i][j], &cam->vx[i][j], cam->ry, 0);
			cam->pow2_vx[i][j] = powf(cam->vx[i][j], 2);
			cam->pow2_vy[i][j] = powf(cam->vy[i][j], 2);
			cam->pow2_vz[i][j] = powf(cam->vz[i][j], 2);
		}
	}
}
