/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsrc2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:04:10 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/17 12:03:00 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

t_color	convert_color(char const *str)
{
	unsigned char	color;
	char			*col_str;

	color = ft_atoi(str);
	col_str = ft_itoa(color);
	if (!col_str)
		print_error(E_ALLOC);
	if (ft_strncmp(str, col_str, ft_strlen(str)) != 0 && \
		ft_strncmp(str, col_str, ft_strlen(str)) != ',')
		print_error(E_COL_INVAL);
	free(col_str);
	return (color);
}

void	clear_resource(t_rsrc *const rsrc)
{
	free(rsrc->textures[0]);
	free(rsrc->textures[1]);
	free(rsrc->textures[2]);
	free(rsrc->textures[3]);
}

int	check_down(t_map const map, size_t const y, size_t const x)
{
	if (y == 0 || y + 1 == map.h)
		print_error(E_MAP_INVAL);
	else if (map.map[y + 1][x] == ' ')
		print_error(E_MAP_INVAL);
	return (map.map[y + 1][x] == '0' || is_player(map.map[y + 1][x]));
}

int	check_right(t_map const map, size_t const y, size_t const x)
{
	if (x == 0 || map.map[y][x] == '\0')
		print_error(E_MAP_INVAL);
	else if (map.map[y][x + 1] == ' ')
		print_error(E_MAP_INVAL);
	return (map.map[y][x + 1] == '0' || is_player(map.map[y][x + 1]));
}

int	open_file(char const *const file_name)
{
	size_t const	len = ft_strlen(file_name);
	int				fd;

	if (len < 4)
		print_error(E_FILE_INVAL);
	if (ft_strncmp(file_name + (len - 4), ".cub", 4) != 0)
		print_error(E_FILE_INVAL);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		print_error(E_FILE_FDERR);
	return (fd);
}
