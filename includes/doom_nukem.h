/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:24:03 by dmaltsev          #+#    #+#             */
/*   Updated: 2018/11/28 14:24:05 by dmaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include "../libft/libft.h"

# define H 720
# define MH 24
# define MW 24
# define N "Doom Nukem"
# define TH 64
# define TW 64
# define W 1280

typedef struct	s_data
{
	double		bdir[2];
	double		bpl[2];
	double		old;
	double		frametime;
	double		movs;
	double		rots;
	double		dir[2];
	double		pos[2];
	double		pl[2];
	double		sn[2];
	char		*map;
	int			bpp;
	int			end;
	int			sln;
	int			*ptr;
	int			keys[300];
	int			*ttr[8];
	int			wm[MH][MW];
	int			x;
	time_t		oldtime;
	time_t		newtime;
	void		*img;
	void		*mlx;
	void		*tex[8];
	void		*win;
}				t_data;

typedef struct	s_site
{
	double		old;
	double		cam;
	double		pwd;
	double		ddist[2];
	double		fw[2];
	double		raydir[2];
	double		sidedist[2];
	double		vardist[3];
	int			col;
	int			draw[2];
	int			hit;
	int			lh;
	int			map[2];
	int			side;
	int			side2;
	int			step[2];
	int			x;
	int			y;
	t_data		*d;
}				t_site;

void			ft_check_bounds(t_data *d);
int				ft_close(t_data *d);
void			ft_construct(t_site *cd);
int				ft_draw_prep(t_data *d);
int				ft_get_map(int fd, t_data *d);
void			ft_null_map(t_data *d);
void			ft_wall_texture(t_site *cd);
void			ft_floor_texture(t_site *cd);
int				ft_retval(char *str, int ret);
int				ft_event(t_data *d);

#endif
