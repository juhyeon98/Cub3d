/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:12:19 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/09 13:19:40 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"

char	*g_map[] = {
    "        1111111111111111111111111",
    "        1000000000110000000000001",
    "        1011000001110000000000001",
    "        1001000000000000000000001",
    "111111111011000001110000000000001",
    "100000000011000001110111110111111",
    "11110111111111011100000010001    ",
    "11110111111111011101010010001    ",
    "11000000110101011100000010001    ",
    "10000000000000001100000010001    ",
    "10000000000000001101010010001    ",
    "11000001110101011111011110N0111  ",
    "11110111 1110101 101111110001    ",
    "11111111 1111111 111111111111    "
};

int	main(void)
{
	t_game	game;

	init_game(&game);
	render(&game);
	mlx_hook(game.win, KEY_EXIT, 0, close, NULL);
	mlx_hook(game.win, KEY_PRESS, 0, key_handling, &game);
	mlx_loop(game.mlx);
	return (0);
}

void	init_game(t_game *const game)
{
	game->posx = 26;
	game->posy = 11;
	game->dirx = 0;
	game->diry = -1;
	game->planx = 0.87;
	game->plany = 0;
	game->mlx = mlx_init();
	game->screen.obj = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->screen.addr = mlx_get_data_addr(game->screen.obj, \
		&(game->screen.bpp), &(game->screen.len), &(game->screen.endian));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	game->map.map = g_map;
	init_rsrcs(game->mlx, game->textures);
}

void	init_rsrcs(void *mlx, t_img *rsrcs)
{
	rsrcs[T_NO].obj = \
		mlx_png_file_to_image(mlx, NO, &rsrcs[T_NO].w, &rsrcs[T_NO].h);
	rsrcs[T_NO].addr = mlx_get_data_addr(rsrcs[T_NO].obj, &rsrcs[T_NO].bpp, \
										&rsrcs[T_NO].len, &rsrcs[T_NO].endian);
	rsrcs[T_SO].obj = \
		mlx_png_file_to_image(mlx, SO, &rsrcs[T_SO].w, &rsrcs[T_SO].h);
	rsrcs[T_SO].addr = mlx_get_data_addr(rsrcs[T_SO].obj, &rsrcs[T_SO].bpp, \
										&rsrcs[T_SO].len, &rsrcs[T_SO].endian);
	rsrcs[T_WE].obj = \
		mlx_png_file_to_image(mlx, WE, &rsrcs[T_WE].w, &rsrcs[T_WE].h);
	rsrcs[T_WE].addr = mlx_get_data_addr(rsrcs[T_WE].obj, &rsrcs[T_WE].bpp, \
										&rsrcs[T_WE].len, &rsrcs[T_WE].endian);
	rsrcs[T_EA].obj = \
		mlx_png_file_to_image(mlx, EA, &rsrcs[T_EA].w, &rsrcs[T_EA].h);
	rsrcs[T_EA].addr = mlx_get_data_addr(rsrcs[T_EA].obj, &rsrcs[T_EA].bpp, \
										&rsrcs[T_EA].len, &rsrcs[T_EA].endian);
}

char	*get_addr(t_img const img, size_t const y, size_t const x)
{
	return (img.addr + (y * img.len + x * (img.bpp / 8)));
}