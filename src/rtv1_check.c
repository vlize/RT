/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 11:09:00 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 11:18:51 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "rtv1.h"

int		ft_is_object(char *str)
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

int		ft_end_with_oid(char *str)
{
	if (!ft_strcmp(str, HYPERBOLOID))
		return (1);
	if (!ft_strcmp(str, PARABOLOID))
		return (1);
	if (!ft_strcmp(str, ELLIPSOID))
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
