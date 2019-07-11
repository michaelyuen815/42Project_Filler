/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 15:21:38 by chyuen            #+#    #+#             */
/*   Updated: 2019/07/05 15:21:41 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_info	*ft_fillinfo_player(t_info *info)
{
	char	*line;

	if (!(line = ft_fillmain_search("$$$ exec p")))
		return (NULL);
	info->player = line[10] == '1' ? PLAY1 : PLAY2;
	free(line);
	info->opp = info->player == PLAY1 ? PLAY2 : PLAY1;
	return (info);
}

t_info	*ft_fillinfo_mapinit(t_info *info, int *size, char type)
{
	char	*line;
	int		tol;
	char	*map;

	if (!(line = ft_fillmain_search(type == T_MAP ? "Plateau" : "Piece")))
		return (NULL);
	size[AXIS_Y] = ft_atoi(ft_strchr(line, ' '));
	size[AXIS_X] = ft_atoi(ft_strrchr(line, ' '));
	tol = (size[AXIS_X] + 1) * size[AXIS_Y];
	map = ft_strnew(tol);
	if (type == T_MAP)
		info->map = map;
	else
		info->tetris = map;
	free(line);
	return (info);
}

t_info	*ft_fillinfo_readmap(t_info *info, char type)
{
	int		i;
	int		*size;
	char	*map;
	char	*line;

	i = -1;
	size = type == T_MAP ? info->z_map : info->z_tet;
	map = type == T_MAP ? info->map : info->tetris;
	if (type == T_MAP)
		line = ft_fillmain_search("000");
	else
		get_next_line(FD, &line);
	while (++i < size[AXIS_Y] && line)
	{
		ft_strncat(map, line + (type == T_MAP ? \
			(int)(ft_strchr(line, ' ') - line) + 1 : 0), size[AXIS_X]);
		ft_strcat(map, "\n");
		free(line);
		if (i < size[AXIS_Y] - 1)
			get_next_line(FD, &line);
	}
	return (info);
}

t_info	*ft_fillinfo_readtet(t_info *info)
{
	ft_strdel(&info->tetris);
	ft_fillinfo_mapinit(info, info->z_tet, T_TET);
	ft_fillinfo_readmap(info, T_TET);
	info->status[ST_PTCENTRE] = info->z_map[AXIS_X] / 2 + \
		info->z_map[AXIS_Y] / 2 * (info->z_map[AXIS_X] + 1);
	return (info);
}

t_info	*ft_fillinfo_init(void)
{
	t_info	*info;

	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (NULL);
	info = ft_fillinfo_player(info);
	info = ft_fillinfo_mapinit(info, info->z_map, T_MAP);
	info->tetris = NULL;
	return (info);
}
