/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:21:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/15 11:54:31 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_map(t_map *const map, int const fd)
{
	char	*line;
	char	*map_str;
	size_t	start_point;

	line = NULL;
	map_str = NULL;
	while (1)
	{
		line = get_line(fd);
		if (!line)
			break ;
		map_str = merge(map_str, line);
		free(line);
	}
	if (!map_str)
		print_error(E_MAP_NOTFD);
	start_point = get_start_point(map_str);
	get_map_size(map, map_str + start_point);
	convert_map(map, map_str + start_point);
	check_elements(*map);
	check_surround(*map);
	free(map_str);
}

size_t	get_start_point(char const *str)
{
	size_t	start_point;

	start_point = 0;
	while (str[start_point] && str[start_point] == '\n')
		start_point++;
	return (start_point);
}

void	get_map_size(t_map *const map, char const *str)
{
	size_t	index;
	size_t	line_len;

	map->h = 0;
	index = -1;
	while (str[++index])
		if (str[index] == '\n')
			map->h++;
	if (str[index - 1] != '\n')
		map->h++;
	map->w = 0;
	while (*str)
	{
		line_len = get_line_len(str);
		if (line_len == 0)
			print_error(E_MAP_EMPL);
		if (map->w < line_len)
			map->w = line_len;
		str += (line_len + 1);
	}
	if (map->h < 3 || map->w < 3)
		print_error(E_MAP_INVAL);
	if (map->h * map->w > 10000)
		print_error(E_MAP_2BIG);
}

void	convert_map(t_map *const map, char const *str)
{
	size_t	index;
	size_t	line_len;

	map->map = (char **)malloc(sizeof(char *) * (map->h));
	if (!map->map)
		print_error(E_ALLOC);
	index = 0;
	while (index < map->h)
	{
		map->map[index] = (char *)malloc(sizeof(char) * (map->w + 1));
		if (!map->map[index])
			print_error(E_ALLOC);
		line_len = get_line_len(str);
		ft_strlcpy(map->map[index], str, line_len + 1);
		ft_memset(map->map[index] + line_len, ' ', map->w - line_len);
		map->map[index][map->w] = '\0';
		str += (line_len + 1);
		index++;
	}
}

size_t	get_line_len(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}
