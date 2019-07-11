/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler_opti.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 21:18:33 by chyuen            #+#    #+#             */
/*   Updated: 2019/07/09 21:18:36 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	ft_fillopti_effect(t_info *info, int index)
{
	int row;
	int col;
	int ret;

	row = ft_fillmath_row(info, index, T_MAP) \
			- ft_fillmath_row(info, info->status[ST_PTCENTRE], T_MAP);
	row *= row < 0 ? -1 : 1;
	col = ft_fillmath_col(info, index, T_MAP) \
			- ft_fillmath_col(info, info->status[ST_PTCENTRE], T_MAP);
	col *= col < 0 ? -1 : 1;
	ret = ft_fillmath_sqrt(row) + ft_fillmath_sqrt(col);
	if (ret >= info->check[CHK_PTAREA])
		return (0);
	info->check[CHK_PTAREA] = ret;
	return (1);
}

int	ft_fillopti_dtoe(t_info *info, int index)
{
	int steps;
	int ret;

	steps = info->status[ST_DTOEN];
	ret = 0;
	ret |= ft_fillmath_dist(info, index + 1, steps);
	ret |= ft_fillmath_dist(info, index - 1, steps);
	ret |= ft_fillmath_dist(info, index + info->z_map[AXIS_X] + 1, steps);
	ret |= ft_fillmath_dist(info, index - info->z_map[AXIS_X] - 1, steps);
	if (ret == info->check[CHK_PTTOEN])
		return (ft_fillopti_effect(info, index));
	else if (!ret)
		return (0);
	info->check[CHK_PTTOEN]++;
	info->check[CHK_PTAREA] = info->z_map[AXIS_X] * info->z_map[AXIS_X] + \
			info->z_map[AXIS_Y] * info->z_map[AXIS_Y];
	ft_fillopti_effect(info, index);
	return (1);
}

int	ft_fillopti_init(t_info *info, int *pt)
{
	int i;
	int index;
	int ret;

	i = -1;
	ret = 0;
	while (info->tetris[++i])
	{
		if (info->tetris[i] == '*')
		{
			index = pt[AXIS_X] + ft_fillmath_col(info, i, T_TET) + \
				(pt[AXIS_Y] + ft_fillmath_row(info, i, T_TET)) * \
				(info->z_map[AXIS_X] + 1);
			ret |= ft_fillopti_dtoe(info, index);
		}
	}
	return (ret);
}
