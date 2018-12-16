/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_fixer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:53:01 by dmaltsev          #+#    #+#             */
/*   Updated: 2018/10/11 21:53:03 by dmaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

int			ft_close(t_data *d)
{
	d->img ? mlx_destroy_image(d->mlx, d->img) : 0;
	d->tex[0] ? mlx_destroy_image(d->mlx, d->tex[0]) : 0;
	d->tex[1] ? mlx_destroy_image(d->mlx, d->tex[1]) : 0;
	d->tex[2] ? mlx_destroy_image(d->mlx, d->tex[2]) : 0;
	d->tex[3] ? mlx_destroy_image(d->mlx, d->tex[3]) : 0;
	d->tex[4] ? mlx_destroy_image(d->mlx, d->tex[4]) : 0;
	d->tex[5] ? mlx_destroy_image(d->mlx, d->tex[5]) : 0;
	d->tex[6] ? mlx_destroy_image(d->mlx, d->tex[6]) : 0;
	d->tex[7] ? mlx_destroy_image(d->mlx, d->tex[7]) : 0;
	exit(0);
	return (0);
}

void		ft_check_bounds(t_data *d)
{
	int		i[2];

	i[1] = -1;
	while (++i[1] < 24 && (i[0] = -1) != -2)
		while (++i[0] < 24)
		{
			if ((i[0] == 0 || i[0] == 23 || i[1] == 0 || i[1] == 23) &&
				d->wm[i[1]][i[0]] == 0)
				d->wm[i[1]][i[0]] = 2;
			if ((i[0] == 22 && i[1] == 22) || (i[0] == 21 && i[1] == 21) ||
				(i[0] == 21 && i[1] == 22) || (i[0] == 22 && i[1] == 21))
				d->wm[i[1]][i[0]] = 0;
		}
	return ;
}

void		ft_null_map(t_data *d)
{
	int		i[2];

	i[1] = -1;
	while (++i[1] < 24 && (i[0] = -1) != -2)
		while (++i[0] < 24)
			d->wm[i[1]][i[0]] = 0;
	return ;
}

/*void		ft_create_map(t_data *d)
{

}*/