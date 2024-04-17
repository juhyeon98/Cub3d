/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:21:32 by taeoh             #+#    #+#             */
/*   Updated: 2024/04/17 12:03:04 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static double	dabs(double a)
{
	return ((a >= 0) * a - (a < 0) * a);
}

int	draw_player(t_game *const game, int x, int y)
{
	double	doffx;
	double	doffy;

	doffx = (game->posx + (-1) * game->mmap_grid / 2 \
	+ game->mmap_grid / game->mmap_size * x);
	doffy = (game->posy + (-1) * game->mmap_grid / 2 \
	+ game->mmap_grid / game->mmap_size * y);
	return ((dabs(game->posx - doffx) <= game->mmap_pdot) \
	&& (dabs(game->posy - doffy) <= game->mmap_pdot));
}

void	draw_minimap(t_game *const game, int x, int y)
{
	int	offx;
	int	offy;

	while (++y < game->mmap_size)
	{
		x = -1;
		while (++x < game->mmap_size)
		{
			offx = (int)(game->posx + (-1) * game->mmap_grid / 2 + \
			game->mmap_grid / game->mmap_size * x);
			offy = (int)(game->posy + (-1) * game->mmap_grid / 2 + \
			game->mmap_grid / game->mmap_size * y);
			if (draw_player(game, x, y))
				*(unsigned int *)(game->minimap.addr + y * game->minimap.len + \
				(game->minimap.bpp / 8) * x) = 0xDD0000;
			else if ((offx >= 0 && offy >= 0 && offx < (int)game->map.w && \
			offy < (int)game->map.h) && (game->map.map[offy][offx] == '1'))
				*(unsigned int *)(game->minimap.addr + y * game->minimap.len + \
				(game->minimap.bpp / 8) * x) = 0x333333 | game->map_opacity;
			else
				*(unsigned int *)(game->minimap.addr + y * game->minimap.len + \
				(game->minimap.bpp / 8) * x) = 0xFFFFFF | game->map_opacity;
		}
	}
}

void	put_minimap(t_game *const game)
{
	game->mmap_size = HEIGHT / 5;
	game->mmap_pos = HEIGHT / 50;
	game->mmap_grid = 9;
	game->mmap_pdot = 0.1;
	game->map_opacity = 0xDD000000;
	game->minimap.obj = mlx_new_image(game->mlx, game->mmap_size, \
	game->mmap_size);
	if (game->minimap.obj == NULL)
		print_error(E_XPM_FAIL);
	game->minimap.addr = mlx_get_data_addr(game->minimap.obj, \
	&game->minimap.bpp, &game->minimap.len, &game->minimap.endian);
	draw_minimap(game, -1, -1);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.obj, \
	game->mmap_pos, game->mmap_pos);
}
