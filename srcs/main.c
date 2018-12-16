/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaltsev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 11:33:00 by dmaltsev          #+#    #+#             */
/*   Updated: 2018/09/23 11:33:01 by dmaltsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom_nukem.h"

int				ft_textures(t_data *d)
{
	int			h;
	int			i;
	int			w;

	h = 64;
	w = 64;
	d->tex[0] = mlx_xpm_file_to_image(d->mlx, "pics/eagle.xpm", &w, &h);
	d->tex[1] = mlx_xpm_file_to_image(d->mlx, "pics/redbrick.xpm", &w, &h);
	d->tex[2] = mlx_xpm_file_to_image(d->mlx, "pics/purplestone.xpm", &w, &h);
	d->tex[3] = mlx_xpm_file_to_image(d->mlx, "pics/greystone.xpm", &w, &h);
	d->tex[4] = mlx_xpm_file_to_image(d->mlx, "pics/bluestone.xpm", &w, &h);
	d->tex[5] = mlx_xpm_file_to_image(d->mlx, "pics/mossy.xpm", &w, &h);
	d->tex[6] = mlx_xpm_file_to_image(d->mlx, "pics/wood.xpm", &w, &h);
	d->tex[7] = mlx_xpm_file_to_image(d->mlx, "pics/colorstone.xpm", &w, &h);
	i = -1;
	while (++i < 8)
		if (d->tex[i])
			d->ttr[i] = (int *)mlx_get_data_addr(d->tex[i], &d->bpp, &d->sln,
				&d->end);
		else
			return (ft_retval("Textures MIA! Shutting down..\n", -1));
	return (0);
}

int				ft_mouse(int x, int y, t_data *d)
{
	y += 0;
	d->dir[0] = d->bdir[0] * sin(((x * M_PI) / 900)) - d->bdir[1] * cos(((x * M_PI) / 900));
	d->dir[1] = d->bdir[0] * cos(((x * M_PI) / 900)) + d->bdir[1] * sin(((x * M_PI) / 900));
	d->pl[0] = d->bpl[0] * sin(((x * M_PI) / 900)) - d->bpl[1] * cos(((x * M_PI) / 900));
	d->pl[1] = d->bpl[0] * cos(((x * M_PI) / 900)) + d->bpl[1] * sin(((x * M_PI) / 900));
	return (0);
}

int				ft_keypress(int key, t_data *d)
{
	if (key == 0)
		d->pressflag[0] = 1;
	else if (key == 1)
		d->pressflag[1] = 1;
	else if (key == 2)
		d->pressflag[2] = 1;
	else if (key == 13)
		d->pressflag[3] = 1;
	else if (key == 123)
		d->pressflag[4] = 1;
	else if (key == 124)
		d->pressflag[5] = 1;
	else if (key == 257)
		d->pressflag[6] = 1;
	else if (key == 53)
		ft_close(d);
	return (0);
}

int				ft_keyrelease(int key, t_data *d)
{
	if (key == 0)
		d->pressflag[0] = 0;
	else if (key == 1)
		d->pressflag[1] = 0;
	else if (key == 2)
		d->pressflag[2] = 0;
	else if (key == 13)
		d->pressflag[3] = 0;
	else if (key == 123)
		d->pressflag[4] = 0;
	else if (key == 124)
		d->pressflag[5] = 0;
	else if (key == 257)
		d->pressflag[6] = 0;
	return (0);
}

int				main(int argc, char *argv[argc])
{
	t_data		d;

	ft_get_map(open((d.map = argv[1]), O_RDONLY), &d);
	d.mlx = mlx_init();
	d.img = mlx_new_image(d.mlx, W, H);
	d.end = 0;
	d.bpp = sizeof(int);
	d.sln = d.bpp * W;
	d.dir[0] = -1;
	d.dir[1] = 0;
	d.bdir[0] = d.dir[0];
	d.bdir[1] = d.dir[1];
	d.pl[0] = 0;
	d.pl[1] = 0.66;
	d.bpl[0] = d.pl[0];
	d.bpl[1] = d.pl[1];
	d.pos[0] = 1.5;
	d.pos[1] = 1.5;
	d.newtime = 0;
	if (ft_textures(&d) != 0)
		ft_close(&d);
	d.win = mlx_new_window(d.mlx, W, H, N);
	d.ptr = (int *)mlx_get_data_addr(d.img, &d.bpp, &d.sln, &d.end);
	mlx_hook(d.win, 2, (1L << 0), ft_keypress, &d);
	mlx_hook(d.win, 3, (1L << 1), ft_keyrelease, &d);
	mlx_hook(d.win, 6, (1L << 6), ft_mouse, &d);
	mlx_hook(d.win, 17, (1L << 17), ft_close, &d);
	mlx_loop_hook(d.mlx, ft_draw_prep, &d);
	mlx_loop(d.mlx);
	return (0);
}
