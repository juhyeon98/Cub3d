/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:26:00 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/17 16:12:27 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	copy_map(t_map *const dst, t_map const org)
{
	size_t	index;

	dst->h = org.h;
	dst->w = org.w;
	dst->map = (char **)malloc(sizeof(char *) * org.h);
	if (!dst->map)
		print_error(E_ALLOC);
	index = 0;
	while (index < org.h)
	{
		dst->map[index] = ft_strdup(org.map[index]);
		if (!dst->map[index])
			print_error(E_ALLOC);
		index++;
	}
}

void	clear_map(t_map const map)
{
	size_t	index;

	index = 0;
	while (index < map.h)
	{
		free(map.map[index]);
		index++;
	}
	free(map.map);
}

void	check_around(t_map const map, size_t const y, size_t const x)
{
	map.map[y][x] = '1';
	if (check_up(map, y, x))
		check_around(map, y - 1, x);
	if (check_left(map, y, x))
		check_around(map, y, x - 1);
	if (check_down(map, y, x))
		check_around(map, y + 1, x);
	if (check_right(map, y, x))
		check_around(map, y, x + 1);
}

int	check_up(t_map const map, size_t const y, size_t const x)
{
	if (y == 0 || y + 1 == map.h)
		print_error(E_MAP_INVAL);
	else if (map.map[y - 1][x] == ' ')
		print_error(E_MAP_INVAL);
	return (map.map[y - 1][x] == 'C' || map.map[y - 1][x] == '0' || is_player(map.map[y - 1][x]));
}

int	check_left(t_map const map, size_t const y, size_t const x)
{
	if (x == 0 || map.map[y][x] == '\0')
		print_error(E_MAP_INVAL);
	else if (map.map[y][x - 1] == ' ')
		print_error(E_MAP_INVAL);
	return (map.map[y - 1][x] == 'C' || map.map[y][x - 1] == '0' || is_player(map.map[y][x - 1]));
}
