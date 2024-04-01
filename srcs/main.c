/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:14:08 by juhyelee          #+#    #+#             */
/*   Updated: 2024/03/28 17:16:18 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_rsrc	rsrc;
	t_map	map;

	if (argc < 2)
		print_error(E_ARG_LACK);
	else if (argc > 2)
		print_error(E_ARG_MANY);
	parse(&map, &rsrc, argv[1]);
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
