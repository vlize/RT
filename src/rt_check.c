/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 11:09:00 by vlize             #+#    #+#             */
/*   Updated: 2016/03/10 13:57:24 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rt.h"

int		ft_is_object(char *str)
{
	if (!ft_strcmp(str, "plane"))
		return (PLANE);
	if (!ft_strcmp(str, "sphere"))
		return (SPHERE);
	if (!ft_strcmp(str, "cone"))
		return (CONE);
	if (!ft_strcmp(str, "cylinder"))
		return (CYLINDER);
	if (!ft_strcmp(str, "ellipsoid"))
		return (ELLIPSOID);
	if (!ft_strcmp(str, "paraboloid"))
		return (PARABOLOID);
	if (!ft_strcmp(str, "hyperboloid"))
		return (HYPERBOLOID);
	if (!ft_strcmp(str, "torus"))
		return (TORUS);
	if (!ft_strcmp(str, "ding-dong"))
		return (DING_DONG);
	if (!ft_strcmp(str, "Möbius strip"))
		return (MOBIUS_STRIP);
	return (0);
}

int		ft_end_with_oid(int type)
{
	if ((type == HYPERBOLOID) || (type == PARABOLOID) || (type == ELLIPSOID))
		return (1);
	return (0);
}

void	ft_check_color(int *color)
{
	if (!color)
		return ;
	if (color[0] > 0xFF)
		color[0] = 0xFF;
	else if (color[0] < 0)
		color[0] = 0;
	if (color[1] > 0xFF)
		color[1] = 0xFF;
	else if (color[1] < 0)
		color[1] = 0;
	if (color[2] > 0xFF)
		color[2] = 0xFF;
	else if (color[2] < 0)
		color[2] = 0;
}
