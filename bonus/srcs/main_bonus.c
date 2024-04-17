/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:08 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/17 12:03:08 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc < 2)
		print_error(E_ARG_LACK);
	else if (argc > 2)
		print_error(E_ARG_MANY);
	parse(&game.map, &game.rsrc, argv[1]);
	load_window(&game);
	render(&game);
	mlx_hook(game.win, KEY_EXIT, 0, exit_program, NULL);
	mlx_hook(game.win, KEY_PRESS, 0, key_handling, &game);
	mlx_key_hook(game.win, door_handling, &game);
	mlx_key_hook(game.win, key_handling2, &game);
	mlx_loop_hook(game.mlx, next_frame, &game);
	mlx_loop(game.mlx);
	exit(0);
}

void	parse(t_map *const map, t_rsrc *const rsrc, \
			char const *const file_name)
{
	int const	fd = open_file(file_name);

	init_resource(rsrc, fd);
	init_map(map, fd);
	close(fd);
}

char	*get_addr(t_img const img, size_t const y, size_t const x)
{
	return (img.addr + (y * img.len + x * (img.bpp / 8)));
}

int	key_handling2(int keycode, t_game *const game)
{
	if (keycode == RIGHT)
		game->turn_right = 0;
	else if (keycode == LEFT)
		game->turn_left = 0;
	else if (keycode == W)
		game->move_front = 0;
	else if (keycode == S)
		game->move_back = 0;
	else if (keycode == D)
		game->move_right = 0;
	else if (keycode == A)
		game->move_left = 0;
	return (0);
}

int	next_frame(t_game *game)
{
	if (game->turn_right)
		turn_right(game);
	if (game->turn_left)
		turn_left(game);
	if (game->move_front)
		move_forward(game);
	if (game->move_back)
		move_back(game);
	if (game->move_right)
		move_right(game);
	if (game->move_left)
		move_left(game);
	render(game);
	return (0);
}
