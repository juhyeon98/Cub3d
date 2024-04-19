/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map4_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:50:43 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/19 12:36:00 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	check_left(t_map const map, size_t const y, size_t const x)
{
	if (x == 0 || map.map[y][x + 1] == '\0')
		print_error(E_MAP_INVAL);
	else if (map.map[y][x - 1] == ' ')
		print_error(E_MAP_INVAL);
	return (map.map[y][x - 1] == '0' || is_player(map.map[y][x - 1]));
}
