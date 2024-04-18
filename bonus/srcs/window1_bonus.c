/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:07:29 by taeoh             #+#    #+#             */
/*   Updated: 2024/04/18 17:34:02 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_window(void *mlx, void *win, t_img *img, t_rsrc *rsrc)
{
	size_t	x;
	size_t	y;

	mlx_clear_window(mlx, win);
	x = -1;
	y = -1;
	while (++y < HEIGHT / 2)
	{
		while (++x < WIDTH)
			*(unsigned int *)(img->addr + y * img->len + (img->bpp / 8) * x) \
				= rsrc->colors[1];
		x = -1;
	}
	x = -1;
	y -= 1;
	while (++y < HEIGHT)
	{
		while (++x < WIDTH)
			*(unsigned int *)(img->addr + y * img->len + (img->bpp / 8) * x) \
				= rsrc->colors[0];
		x = -1;
	}
}

void	set_position(t_game *game, char **map)
{
	size_t	x;
	size_t	y;

	x = -1;
	y = -1;
	while (++y < game->map.h)
	{
		while (++x < game->map.w)
			apply_position(game, map, y, x);
		x = -1;
	}
}

void	apply_position(t_game *game, char **map, size_t y, size_t x)
{
	if (is_player(map[y][x]))
	{
		game->posx = x + 0.5;
		game->posy = y + 0.5;
		game->dirx = -1 * (map[y][x] == 'W') + (map[y][x] == 'E');
		game->diry = -1 * (map[y][x] == 'N') + (map[y][x] == 'S');
		game->planx = -1 * game->diry * FOV;
		game->plany = game->dirx * FOV;
	}
	else if (map[y][x] == 'A')
	{
		game->spx = x + 0.5;
		game->spy = y + 0.5;
	}
}

void	set_png_images(t_game *game, t_img *ts, int i)
{
	size_t	len;

	len = ft_strlen(game->rsrc.textures[i]);
	if (len < 4)
		print_error(E_XPM_NOTFE);
	if (ft_strncmp(game->rsrc.textures[i] + (len - 4), ".xpm", 4) != 0)
		print_error(E_XPM_NOTFE);
	ts[i].obj = mlx_xpm_file_to_image(game->mlx, \
					game->rsrc.textures[i], &ts[i].w, &ts[i].h);
	if (ts[i].obj == NULL)
		print_error(E_XPM_FAIL);
	ts[i].addr = mlx_get_data_addr(ts[i].obj, &ts[i].bpp, \
					&ts[i].len, &ts[i].endian);
}

void	flush_image(t_img *image)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < HEIGHT)
	{
		while (++x < WIDTH)
			*(unsigned int *)(image->addr + y * image->len + (image->bpp / 8) * x) \
				= 0xFF000000;
		x = -1;
	}
}
void	sprite_images(t_game *game)
{
	game->spr.obj = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->spr.obj == NULL)
		print_error(E_XPM_FAIL);
	game->spr.addr = mlx_get_data_addr(game->spr.obj, &game->spr.bpp, \
									&game->spr.len, &game->spr.endian);
	flush_image(&game->spr);
	load_sprite(&game->coin[0], game->mlx, "texture/a.xpm");
	load_sprite(&game->coin[1], game->mlx, "texture/b.xpm");
	load_sprite(&game->coin[2], game->mlx, "texture/c.xpm");
	load_sprite(&game->coin[3], game->mlx, "texture/d.xpm");
	load_sprite(&game->coin[4], game->mlx, "texture/e.xpm");
}

void	set_images(t_game *game, t_img *sc, t_img *ts)
{
	sc->obj = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (sc->obj == NULL)
		print_error(E_XPM_FAIL);
	game->wall.obj = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	sc->addr = mlx_get_data_addr(sc->obj, &sc->bpp, &sc->len, &sc->endian);
	game->wall.addr = mlx_get_data_addr(game->wall.obj, &game->wall.bpp, \
										&game->wall.len, &game->wall.endian);
	set_png_images(game, ts, 0);
	set_png_images(game, ts, 1);
	set_png_images(game, ts, 2);
	set_png_images(game, ts, 3);
	sprite_images(game);
}
