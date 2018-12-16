/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 13:19:02 by dmaltsev          #+#    #+#             */
/*   Updated: 2018/09/23 13:19:03 by dmaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void			ft_construct(t_site *cd)
{
	cd->lh = (H / cd->pwd);
	cd->draw[0] = -cd->lh / 2 + H / 2;
	if (cd->draw[0] < 0)
		cd->draw[0] = 0;
	cd->draw[1] = cd->lh / 2 + H / 2;
	if (cd->draw[1] >= H)
		cd->draw[1] = H - 1;
	ft_wall_texture(cd);
	ft_floor_texture(cd);
	return ;
}

void			ft_hit(t_site *cd)
{
	while (cd->hit == 0)
	{
		if (cd->sidedist[0] < cd->sidedist[1])
		{
			cd->side = 0;
			(1 / cd->raydir[0]) > 0 ? (cd->side2 = 1) :
			(cd->side2 = 0);
			cd->sidedist[0] += cd->ddist[0];
			cd->map[0] += cd->step[0];
		}
		else if (cd->sidedist[0] >= cd->sidedist[1])
		{
			cd->side = 1;
			(1 / cd->raydir[1]) > 0 ? (cd->side2 = 3) :
			(cd->side2 = 2);
			cd->sidedist[1] += cd->ddist[1];
			cd->map[1] += cd->step[1];
		}
		cd->d->wm[cd->map[0]][cd->map[1]] != 0 ? (cd->hit = 1) : 0;
	}
	return ;
}

void			ft_raydir(t_site *cd)
{
	if (cd->raydir[0] < 0 && (cd->step[0] = -1) != 0)
		cd->sidedist[0] = (cd->d->pos[0] - cd->map[0]) * cd->ddist[0];
	else if (cd->raydir >= 0 && (cd->step[0] = 1) != 0)
		cd->sidedist[0] = (cd->map[0] + 1.0 - cd->d->pos[0]) * cd->ddist[0];
	if (cd->raydir[1] < 0 && (cd->step[1] = -1) != 0)
		cd->sidedist[1] = (cd->d->pos[1] - cd->map[1]) * cd->ddist[1];
	else if (cd->raydir[1] >= 0 && (cd->step[1] = 1) != 0)
		cd->sidedist[1] = (cd->map[1] + 1.0 - cd->d->pos[1]) * cd->ddist[1];
	return ;
}

void			ft_screen_site(t_site *cd)
{
	while (++cd->x < W)
	{
		cd->cam = 2 * cd->x / (double)W - 1;
		cd->raydir[0] = cd->d->dir[0] + cd->d->pl[0] * cd->cam;
		cd->raydir[1] = cd->d->dir[1] + cd->d->pl[1] * cd->cam;
		cd->map[0] = (int)cd->d->pos[0];
		cd->map[1] = (int)cd->d->pos[1];
		cd->ddist[0] = fabs(1 / cd->raydir[0]);
		cd->ddist[1] = fabs(1 / cd->raydir[1]);
		cd->hit = 0;
		ft_raydir(cd);
		ft_hit(cd);
		cd->side == 0 ? (cd->pwd = (cd->map[0] - cd->d->pos[0] +
			(1 - cd->step[0]) / 2) / cd->raydir[0]) : (cd->pwd =
		(cd->map[1] - cd->d->pos[1] + (1 - cd->step[1]) / 2) / cd->raydir[1]);
		ft_construct(cd);
	}
	return ;
}

int				ft_draw_prep(t_data *d)
{
	t_site		cd;
	char		*time;

	cd.x = -1;
	cd.d = d;
	ft_event(d);
	ft_screen_site(&cd);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	d->oldtime = d->newtime;
	d->newtime = clock();
	d->frametime = (double)(d->newtime - d->oldtime)
	/ CLOCKS_PER_SEC;
	time = ft_itoa((1.0 / d->frametime));
	mlx_string_put(d->mlx, d->win, 6, 0, 0xFFFFFF, time);
	time ? free(time) : 0;
	(d->pressflag[6] == 1 && d->pressflag[0] == 0 && d->pressflag[1] == 0 &&
		d->pressflag[2] == 0) ? (d->movs = d->frametime * 7.0) :
	((d->pressflag[0] == 1 && (d->pressflag[1] == 1 || d->pressflag[3] == 1)) ||
		(d->pressflag[2] == 1 && (d->pressflag[1] == 1 || d->pressflag[3] == 1))) ?
	(d->movs = d->frametime * 3.0) : (d->movs = d->frametime * 4.0);
	d->rots = d->frametime * 2.0;
	return (0);
}
