/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:44:23 by dmaltsev          #+#    #+#             */
/*   Updated: 2018/11/28 16:44:27 by dmaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

void			ft_event3(t_data *d)
{
	if (d->pressflag[4] == 1)
	{
		d->old = d->dir[0];
		d->dir[0] = d->dir[0] * cos(d->rots) - d->dir[1] * sin(d->rots);
		d->dir[1] = d->old * sin(d->rots) + d->dir[1] * cos(d->rots);
		d->old = d->pl[0];
		d->pl[0] = d->pl[0] * cos(d->rots) - d->pl[1] * sin(d->rots);
		d->pl[1] = d->old * sin(d->rots) + d->pl[1] * cos(d->rots);
	}
	if (d->pressflag[5] == 1)
	{
		d->old = d->dir[0];
		d->dir[0] = d->dir[0] * cos(-d->rots) - d->dir[1] * sin(-d->rots);
		d->dir[1] = d->old * sin(-d->rots) + d->dir[1] * cos(-d->rots);
		d->old = d->pl[0];
		d->pl[0] = d->pl[0] * cos(-d->rots) - d->pl[1] * sin(-d->rots);
		d->pl[1] = d->old * sin(-d->rots) + d->pl[1] * cos(-d->rots);
	}
	return ;
}

void			ft_event2(t_data *d)
{
	if (d->pressflag[0] == 1)
	{
		d->wm[(int)(d->pos[0] - ((d->dir[1] * d->movs) + d->sn[1]))][(int)d->pos[1]] == 0 ?
			(d->pos[0] -= d->dir[1] * d->movs) :
			(d->pos[0] += round(d->pos[0]) - d->pos[0] + d->sn[1]);
		d->wm[(int)d->pos[0]][(int)(d->pos[1] + ((d->dir[0] * d->movs) + d->sn[0]))] == 0 ?
			(d->pos[1] += d->dir[0] * d->movs) :
			(d->pos[1] += round(d->pos[1]) - d->pos[1] - d->sn[0]);
	}
	if (d->pressflag[2] == 1)
	{
		d->wm[(int)(d->pos[0] + ((d->dir[1] * d->movs) + d->sn[1]))][(int)d->pos[1]] == 0 ?
		(d->pos[0] += d->dir[1] * d->movs) :
		(d->pos[0] += round(d->pos[0]) - d->pos[0] - d->sn[1]);
		d->wm[(int)d->pos[0]][(int)(d->pos[1] - ((d->dir[0] * d->movs) + d->sn[0]))] == 0 ?
		(d->pos[1] -= d->dir[0] * d->movs) :
		(d->pos[1] += round(d->pos[1]) - d->pos[1] + d->sn[0]);
	}
	ft_event3(d);
	return ;
}

int				ft_event(t_data *d)
{
	d->dir[0] >= 0 ? (d->sn[0] = 0.04) : (d->sn[0] = -0.04);
	d->dir[1] >= 0 ? (d->sn[1] = 0.04) : (d->sn[1] = -0.04);
	if (d->pressflag[1] == 1)
	{
		d->wm[(int)(d->pos[0] - ((d->dir[0] * d->movs) + d->sn[0]))][(int)d->pos[1]] == 0 ?
		(d->pos[0] -= d->dir[0] * d->movs) :
		(d->pos[0] += round(d->pos[0]) - d->pos[0] + d->sn[0]);
		d->wm[(int)d->pos[0]][(int)(d->pos[1] - ((d->dir[1] * d->movs) + d->sn[1]))] == 0 ?
		(d->pos[1] -= d->dir[1] * d->movs) :
		(d->pos[1] += round(d->pos[1]) - d->pos[1] + d->sn[1]);
	}
	if (d->pressflag[3] == 1)
	{
		d->wm[(int)(d->pos[0] + ((d->dir[0] * d->movs) + d->sn[0]))][(int)d->pos[1]] == 0 ?
		(d->pos[0] += d->dir[0] * d->movs) :
		(d->pos[0] += round(d->pos[0]) - d->pos[0] - d->sn[0]);
		d->wm[(int)d->pos[0]][(int)(d->pos[1] + ((d->dir[1] * d->movs) + d->sn[1]))] == 0 ?
		(d->pos[1] += d->dir[1] * d->movs) :
		(d->pos[1] += round(d->pos[1]) - d->pos[1] - d->sn[1]);
	}
	ft_event2(d);
	return (0);
}
