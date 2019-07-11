/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler_math.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:46:16 by chyuen            #+#    #+#             */
/*   Updated: 2019/07/08 13:46:18 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	ft_fillmath_col(t_info *info, int index, char type)
{
	if (type == T_MAP)
		return (index % (info->z_map[AXIS_X] + 1));
	else
		return (index % (info->z_tet[AXIS_X] + 1));
}

int	ft_fillmath_row(t_info *info, int index, char type)
{
	if (type == T_MAP)
		return (index / (info->z_map[AXIS_X] + 1));
	else
		return (index / (info->z_tet[AXIS_X] + 1));
}

int	ft_fillmath_sqrt(int nbr)
{
	int	ret;

	ret = 0;
	if (!nbr)
		return (0);
	while (ret * ret <= nbr)
		ret++;
	return (ret - 1);
}

int	ft_fillmath_dist(t_info *info, int i, int steps)
{
	if (ft_fillmath_col(info, i, T_MAP) == info->z_map[AXIS_X] || \
		i > info->z_map[AXIS_Y] * (info->z_map[AXIS_X] + 1) || i < 0)
		return (0);
	if (BL_PLAY(info->map[i]) == info->opp)
		return (1);
	if (!steps || BL_PLAY(info->map[i]) == info->player)
		return (0);
	steps--;
	if (ft_fillmath_dist(info, i + 1, steps))
		return (1);
	if (ft_fillmath_dist(info, i - 1, steps))
		return (1);
	if (ft_fillmath_dist(info, i + 1 + info->z_map[AXIS_X], steps))
		return (1);
	if (ft_fillmath_dist(info, i - 1 - info->z_map[AXIS_X], steps))
		return (1);
	return (0);
}
