/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_construct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 09:49:45 by dmaltsev          #+#    #+#             */
/*   Updated: 2018/09/24 09:49:47 by dmaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

int			ft_retval(char *str, int ret)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
		write(1, &str[i], 1);
	return (ret);
}

void		ft_put_floor(t_site *cd)
{
	double	curfloor[2];
	double	weight;
	int		floortex[2];
	int		y;

	y = cd->draw[1];
	while (++y < H)
	{
		cd->vardist[2] = H / (2.0 * y - H);
		weight = (cd->vardist[2] - cd->vardist[1]) /
		(cd->vardist[0] - cd->vardist[1]);
		curfloor[0] = weight * cd->fw[0] + (1.0 - weight) * cd->d->pos[0];
		curfloor[1] = weight * cd->fw[1] + (1.0 - weight) * cd->d->pos[1];
		floortex[0] = (int)(curfloor[0] * 64) % 64;
		floortex[1] = (int)(curfloor[1] * 64) % 64;
		cd->d->ptr[cd->x + ((y - 1) * W)] =
		(cd->d->ttr[3][64 * floortex[1] + floortex[0]] >> 1) & 8355711;
		cd->d->ptr[cd->x + ((H - y) * W)] =
		cd->d->ttr[6][64 * floortex[1] + floortex[0]];
	}
	return ;
}

void		ft_floor_texture(t_site *cd)
{
	if (cd->side == 0 && cd->raydir[0] > 0)
	{
		cd->fw[0] = cd->map[0];
		cd->fw[1] = cd->map[1] + cd->old;
	}
	else if (cd->side == 0 && cd->raydir[0] < 0)
	{
		cd->fw[0] = cd->map[0] + 1.0;
		cd->fw[1] = cd->map[1] + cd->old;
	}
	else if (cd->side == 1 && cd->raydir[1] > 0)
	{
		cd->fw[0] = cd->map[0] + cd->old;
		cd->fw[1] = cd->map[1];
	}
	else
	{
		cd->fw[0] = cd->map[0] + cd->old;
		cd->fw[1] = cd->map[1] + 1.0;
	}
	cd->vardist[0] = cd->pwd;
	cd->vardist[1] = 0.0;
	ft_put_floor(cd);
	return ;
}

void		ft_wall_texture(t_site *cd)
{
	int		d;
	int		tex[2];
	int		texnum;

	texnum = ((abs(cd->d->wm[cd->map[0]][cd->map[1]])) + cd->side2) % 8;
	cd->side == 0 ? (cd->old = cd->d->pos[1] + cd->pwd * cd->raydir[1]) :
	(cd->old = cd->d->pos[0] + cd->pwd * cd->raydir[0]);
	cd->old -= floor((cd->old));
	tex[0] = (int)(cd->old * (double)(TW));
	if (cd->side == 0 && cd->raydir[0] > 0)
		tex[0] = TW - tex[0];
	if (cd->side == 1 && cd->raydir[1] < 0)
		tex[0] = TW - tex[0];
	cd->y = cd->draw[0] - 0.1;
	while (++cd->y < cd->draw[1])
	{
		d = cd->y * 256 - H * 128 + cd->lh * 128;
		tex[1] = ((d * TH) / cd->lh) / 256;
		cd->col = cd->d->ttr[texnum][(tex[1] * TW) + tex[0]];
		if ((cd->side2 % 2) == 0)
			cd->col = (cd->col >> 1) & 8355711;
		cd->d->ptr[cd->x + (cd->y * W)] = cd->col;
	}
	return ;
}

int			ft_get_map(int fd, t_data *d)
{
	int		i[3];
	char	**tab;
	char	*line;

	i[1] = -1;
	ft_null_map(d);
	while ((i[2] = get_next_line(fd, &line)) == 1)
	{
		if ((++i[1]) < 24 && (i[0] = -1) != -2)
		{
			tab = ft_strsplit(line, ' ');
			while (tab[++i[0]] && i[0] < 24)
				d->wm[i[1]][i[0]] = ft_atoi(tab[i[0]]);
			tab ? ft_freestrarr(tab) : 0;
		}
		line ? ft_strdel(&line) : 0;
	}
	line ? ft_strdel(&line) : 0;
	ft_check_bounds(d);
	i[1] = close(fd);
	if (i[1] != 0 || i[2] != 0)
		return (ft_retval("Map is missing.\n", i[1] != 0 ? i[1] : i[2]));
	return (0);
}
