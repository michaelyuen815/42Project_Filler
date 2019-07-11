/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:06:47 by chyuen            #+#    #+#             */
/*   Updated: 2019/07/03 16:06:48 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	*ft_fillmain_search(char *key)
{
	char	*line;

	line = NULL;
	while (get_next_line(FD, &line) > 0)
	{
		if (ft_strstr(line, key))
			return (line);
		free(line);
	}
	return (NULL);
}

int		main(void)
{
	t_info	*info;

	if (!(info = ft_fillinfo_init()))
		return (0);
	while (1)
	{
		ft_fillinfo_readmap(info, T_MAP);
		ft_fillinfo_readtet(info);
		if (!ft_fillreact_solve(info))
		{
			ft_strdel(&info->map);
			ft_strdel(&info->tetris);
			ft_printf("%d %d\n", 0, 0);
			return (0);
		}
		ft_printf("%d %d\n", info->print[AXIS_Y], info->print[AXIS_X]);
		ft_strclr(info->map);
	}
	return (0);
}
