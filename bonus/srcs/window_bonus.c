/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:07:29 by taeoh             #+#    #+#             */
/*   Updated: 2024/04/18 15:58:55 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <stdio.h>

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
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' \
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				game->posx = x + 0.5;
				game->posy = y + 0.5;
				game->dirx = -1 * (map[y][x] == 'W') + (map[y][x] == 'E');
				game->diry = -1 * (map[y][x] == 'N') + (map[y][x] == 'S');
				game->planx = -1 * game->diry * FOV;
				game->plany = game->dirx * FOV;
				return ;
			}
		}
		x = -1;
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
	game->coin[0].obj = mlx_xpm_file_to_image(game->mlx, "texture/a.xpm", &game->coin[0].w, &game->coin[0].h);
	if (game->coin[0].obj == NULL)
		print_error(E_XPM_FAIL);
	game->coin[0].addr = mlx_get_data_addr(game->coin[0].obj, &game->coin[0].bpp, \
									&game->coin[0].len, &game->coin[0].endian);
	game->coin[1].obj = mlx_xpm_file_to_image(game->mlx, "texture/b.xpm", &game->coin[1].w, &game->coin[1].h);
	if (game->coin[1].obj == NULL)
		print_error(E_XPM_FAIL);
	game->coin[1].addr = mlx_get_data_addr(game->coin[1].obj, &game->coin[1].bpp, \
									&game->coin[1].len, &game->coin[1].endian);
	game->coin[2].obj = mlx_xpm_file_to_image(game->mlx, "texture/c.xpm", &game->coin[2].w, &game->coin[2].h);
	if (game->coin[2].obj == NULL)
		print_error(E_XPM_FAIL);
	game->coin[2].addr = mlx_get_data_addr(game->coin[2].obj, &game->coin[2].bpp, \
									&game->coin[2].len, &game->coin[2].endian);
	game->coin[3].obj = mlx_xpm_file_to_image(game->mlx, "texture/d.xpm", &game->coin[3].w, &game->coin[3].h);
	if (game->coin[3].obj == NULL)
		print_error(E_XPM_FAIL);
	game->coin[3].addr = mlx_get_data_addr(game->coin[3].obj, &game->coin[3].bpp, \
									&game->coin[3].len, &game->coin[3].endian);
	game->coin[4].obj = mlx_xpm_file_to_image(game->mlx, "texture/e.xpm", &game->coin[4].w, &game->coin[4].h);
	if (game->coin[4].obj == NULL)
		print_error(E_XPM_FAIL);
	game->coin[4].addr = mlx_get_data_addr(game->coin[4].obj, &game->coin[4].bpp, \
									&game->coin[4].len, &game->coin[4].endian);
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

void	load_window(t_game *game)
{
	game->move_back = 0;
	game->move_front = 0;
	game->move_left = 0;
	game->move_right = 0;
	game->turn_left = 0;
	game->turn_right = 0;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		print_error(E_MLX);
	set_position(game, game->map.map);
	set_images(game, &game->screen, game->textures);
	game->door.obj = mlx_xpm_file_to_image(game->mlx, "texture/door.xpm", \
										&game->door.w, &game->door.h);
	if (!game->door.obj)
		print_error(E_MLX);
	game->door.addr = mlx_get_data_addr(game->door.obj, &game->door.bpp, \
										&game->door.len, &game->door.endian);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (game->win == NULL)
		print_error(E_MLX);
	init_window(game->mlx, game->win, &game->screen, &game->rsrc);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.obj, 0, 0);
}
