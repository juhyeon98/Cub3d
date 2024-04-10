/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:33:32 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/10 15:23:40 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_elements(t_map const map)
{
	size_t	h;
	size_t	w;
	int		p_one;

	h = 0;
	while (h < map.h)
	{
		w = 0;
		while (w < map.w)
		{
			p_one = check_player(map.map[h][w]);
			if (map.map[h][w] != '1' && map.map[h][w] != '0' && \
				map.map[h][w] != ' ' && !is_player(map.map[h][w]))
				print_error(E_MAP_OTHEL);
			w++;
		}
		h++;
	}
	if (p_one == 0)
		print_error(E_MAP_NOPLAYER);
}

int	is_player(char const el)
{
	return (el == 'N' || el == 'E' || el == 'S' || el == 'W');
}

int	check_player(char const el)
{
	static int	num_p;

	if (is_player(el))
	{
		if (num_p != 0)
			print_error(E_MAP_2PLAYER);
		num_p = 1;
	}
	return (num_p);
}

void	check_surround(t_map const map)
{
	size_t	px;
	size_t	py;
	t_map	cmap;

	find_player(map, &py, &px);
	copy_map(&cmap, map);
	while (py > 1 && cmap.map[py - 1][px] != '1')
		py--;
	check_around(cmap, py, px);
	clear_map(cmap);
}

void	find_player(t_map const map, size_t *const y, size_t *const x)
{
	*y = 0;
	while (*y < map.h)
	{
		*x = 0;
		while (*x < map.w)
		{
			if (is_player(map.map[*y][*x]))
				return ;
			(*x)++;
		}
		(*y)++;
	}
}
