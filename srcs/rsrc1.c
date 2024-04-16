/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsrc1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:59:12 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/16 16:06:58 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_resource(t_rsrc *const rsrc, int const fd)
{
	unsigned char	to_check;
	char			*line;
	t_type			type;

	to_check = 0;
	while (to_check < FL_RSRCS)
	{
		line = get_line(fd);
		if (!line)
			print_error(fd);
		line[ft_strlen(line) - 1] = '\0';
		type = get_type(line);
		if ((to_check >> type) & 1)
			print_error(E_RSRC_DUP);
		to_check |= (1 << type);
		if (type >= T_NO && type <= T_EA)
			rsrc->textures[type] = set_texture(line + 2);
		else if (type == T_FL || type == T_CL)
			rsrc->colors[type - T_FL] = set_color(line + 1);
		free(line);
	}
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

t_color	set_color(char const *str)
{
	unsigned char	colors[3];
	size_t			index;

	while (*str && is_white(*str))
		str++;
	if (*str == '\0')
		print_error(E_COL_NOTFD);
	index = 0;
	while (index < 2)
	{
		colors[index] = convert_color(str);
		while (*str && ft_isdigit(*str))
			str++;
		if (*str != ',')
			print_error(E_COL_FORM);
		str++;
		index++;
	}
	colors[index] = convert_color(str);
	while (*str && ft_isdigit(*str))
		str++;
	if (*str != '\0')
		print_error(E_COL_FORM);
	return (colors[0] << 16 | colors[1] << 8 | colors[2]);
}
