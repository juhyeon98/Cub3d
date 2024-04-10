/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsrc1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:59:12 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/10 15:03:50 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_resource(t_rsrc *const rsrc, int const fd)
{
	char	*line;
	int		finished;
	t_type	type;

	finished = 0;
	while (finished < 6)
	{
		line = get_line(fd);
		if (!line)
			print_error(E_RSRC_LACK);
		line[ft_strlen(line) - 1] = '\0';
		type = get_type(line);
		if (type > T_NL)
			finished++;
		if (type >= T_NO && type <= T_EA)
			rsrc->textures[type] = set_texture(line + 2);
		else if (type == T_FL || type == T_CL)
			set_color(rsrc->colors[type - 4], line + 1);
		free(line);
	}
	rsrc->cl_color = (rsrc->colors[0][0] << 16) | (rsrc->colors[0][1] << 8);
	rsrc->cl_color = rsrc->cl_color | rsrc->colors[0][2];
	rsrc->fl_color = (rsrc->colors[1][0] << 16) | (rsrc->colors[1][1] << 8);
	rsrc->fl_color = rsrc->fl_color | rsrc->colors[1][2];
}

t_type	get_type(char const *str)
{
	if (*str == '\0')
		return (T_NL);
	while (*str && !is_white(*str))
		str++;
	if (str[-1] == 'F')
		return (T_FL);
	else if (str[-1] == 'C')
		return (T_CL);
	else if (str[-1] == 'O' && str[-2] == 'N')
		return (T_NO);
	else if (str[-1] == 'O' && str[-2] == 'S')
		return (T_SO);
	else if (str[-1] == 'E' && str[-2] == 'W')
		return (T_WE);
	else if (str[-1] == 'A' && str[-2] == 'E')
		return (T_EA);
	print_error(E_TYPE_INVAL);
	return (-2);
}

int	is_white(char const ch)
{
	return (ch == ' ' || (ch >= 9 && ch <= 13));
}

char	*set_texture(char const *str)
{
	char	*texture;
	size_t	index;

	while (*str && is_white(*str))
		str++;
	if (*str == '\0')
		print_error(E_TEXT_NOTFD);
	index = 0;
	while (str[index])
	{
		if (is_white(str[index]))
			print_error(E_TEXT_MANY);
		index++;
	}
	texture = ft_strdup(str);
	if (!texture)
		print_error(E_ALLOC);
	return (texture);
}

void	set_color(t_color *const color, char const *str)
{
	size_t	index;

	while (*str && is_white(*str))
		str++;
	if (*str == '\0')
		print_error(E_COL_NOTFD);
	index = 0;
	while (index < 3)
	{
		color[index] = convert_color(str);
		while (*str && ft_isdigit(*str))
			str++;
		if (index != 2 && *str != ',')
			print_error(E_COL_FORM);
		str++;
		if (index != 2 && *str == '\0')
			print_error(E_COL_LACK);
		index++;
	}
	if (*str != '\0')
		print_error(E_COL_FORM);
}
