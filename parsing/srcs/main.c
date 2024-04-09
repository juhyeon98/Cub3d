/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:08 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/09 13:08:00 by taeoh            ###   ########.fr       */
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
	return (0);
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
