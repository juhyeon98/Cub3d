/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:33:32 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/18 16:49:57 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	check_elements(t_map const map)
{
	size_t	h;
	size_t	w;
	int		p_one;
	int		c_one;

	h = 0;
	while (h < map.h)
	{
		w = 0;
		while (w < map.w)
		{
			p_one = check_player(map.map[h][w]);
			c_one = check_coin(map.map[h][w]);
			if (map.map[h][w] != '1' && map.map[h][w] != '0' && \
				map.map[h][w] != ' ' && map.map[h][w] != 'D' && \
				map.map[h][w] != 'A' && !is_player(map.map[h][w]))
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

int	check_coin(char const el)
{
	static int	num_c;

	if (el == 'A')
	{
		if (num_c != 0)
			print_error(E_MAP_2COIN);
		num_c = 1;
	}
	return (num_c);
}

int	check_visited(t_map const map, size_t *y, size_t *x)
{
	size_t	h;
	size_t	w;

	h = 0;
	while (h < map.h)
	{
		w = 0;
		while (w < map.w)
		{
			if (map.map[h][w] == '0' || map.map[h][w] == 'D' || \
				map.map[h][w] == 'A' || is_player(map.map[h][w]))
			{
				*x = w;
				*y = h;
				return (0);
			}
			w++;
		}
		h++;
	}
	return (1);
}
