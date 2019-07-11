/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler_react.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:34:47 by chyuen            #+#    #+#             */
/*   Updated: 2019/07/05 16:34:49 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_fillreact_checkpt(t_info *info, int i, int *pt)
{
	int ret;

	if (pt[AXIS_Y] + ft_fillmath_row(info, i, T_TET) >= info->z_map[AXIS_Y] \
		|| pt[AXIS_Y] + ft_fillmath_row(info, i, T_TET) < 0 || \
		pt[AXIS_X] + ft_fillmath_col(info, i, T_TET) < 0 || \
		pt[AXIS_X] + ft_fillmath_col(info, i, T_TET) >= info->z_map[AXIS_X])
		return (-1);
	ret = pt[AXIS_X] + ft_fillmath_col(info, i, T_TET) + \
			(pt[AXIS_Y] + ft_fillmath_row(info, i, T_TET)) \
			* (info->z_map[AXIS_X] + 1);
	if (BL_PLAY(info->map[ret]) == info->opp)
		return (-1);
	return (ret);
}

int		ft_fillreact_check(t_info *info, int *pt)
{
	int i;
	int	cal;
	int count;

	i = -1;
	count = 0;
	while (info->tetris[++i])
	{
		if (info->tetris[i] == '*')
		{
			if ((cal = ft_fillreact_checkpt(info, i, pt)) == -1)
				return (0);
			if (BL_PLAY(info->map[cal]) == info->player)
				count++;
			if (count > 1)
				return (0);
		}
	}
	if (!count)
		return (0);
	return (1);
}

t_info	*ft_fillreact_init(t_info *info)
{
	info->check[CHK_PT] = 0;
	info->status[ST_DTOEN] = 5;
	info->check[CHK_PTTOEN] = 0;
	info->check[CHK_PTAREA] = info->z_map[AXIS_X] * info->z_map[AXIS_X] + \
			info->z_map[AXIS_Y] * info->z_map[AXIS_Y];
	return (info);
}

int		ft_fillreact_solve(t_info *info)
{
	int		pt[2];

	pt[AXIS_Y] = (info->z_tet[AXIS_Y] + 1) * -1;
	ft_fillreact_init(info);
	while (++pt[AXIS_Y] < info->z_map[AXIS_X])
	{
		pt[AXIS_X] = (info->z_tet[AXIS_X] + 1) * -1;
		while (++pt[AXIS_X] < info->z_map[AXIS_X])
		{
			if (ft_fillreact_check(info, pt))
			{
				if (ft_fillopti_init(info, pt))
				{
					info->check[CHK_PT] = 1;
					info->print[AXIS_X] = pt[AXIS_X];
					info->print[AXIS_Y] = pt[AXIS_Y];
				}
			}
		}
	}
	if (info->check[CHK_PT])
		return (1);
	return (0);
}
