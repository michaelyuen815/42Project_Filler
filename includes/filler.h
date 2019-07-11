/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chyuen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 16:07:03 by chyuen            #+#    #+#             */
/*   Updated: 2019/07/03 16:07:04 by chyuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define AXIS_X 0
# define AXIS_Y 1

# define ST_STAGE	0
# define ST_PTCENTRE 1
# define ST_DTOEN	2

# define CHK_PT		0
# define CHK_PTTOEN 1
# define CHK_PTAREA	2

# define PLAY1	111
# define PLAY2	120
# define BL_PLAY(ch) (ch + (BL_UP(ch) ? 32 : 0))

# define T_MAP	77
# define T_TET	84
# define FD		0

typedef struct s_info	t_info;

struct	s_info
{
	char	player;
	char	*map;
	char	*tetris;
	int		z_map[2];
	int		z_tet[2];
	char	opp;
	int		status[3];
	int		check[3];
	int		print[2];
};

char	*ft_fillmain_search(char *key);

t_info	*ft_fillinfo_readmap(t_info *info, char type);
t_info	*ft_fillinfo_readtet(t_info *info);
t_info	*ft_fillinfo_init(void);

int		ft_fillreact_solve(t_info *info);

int		ft_fillmath_col(t_info *info, int index, char type);
int		ft_fillmath_row(t_info *info, int index, char type);
int		ft_fillmath_sqrt(int nbr);
int		ft_fillmath_dist(t_info *info, int i, int steps);

int		ft_fillopti_init(t_info *info, int *pt);

#endif
