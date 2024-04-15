/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:08 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/15 12:42:04 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_loop(game.mlx);
	exit(0);
}

void	parse(t_map *const map, t_rsrc *const rsrc, \
			char const *const file_name)
{
	int const	fd = open_file(file_name);

	init_resource(rsrc, fd);
	ft_putendl_fd("success load resource", STDOUT_FILENO);
	init_map(map, fd);
	ft_putendl_fd("success load map", STDOUT_FILENO);
	close(fd);
}

char	*get_addr(t_img const img, size_t const y, size_t const x)
{
	return (img.addr + (y * img.len + x * (img.bpp / 8)));
}
