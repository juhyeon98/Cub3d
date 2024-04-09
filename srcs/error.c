/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:17:13 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/09 12:54:47 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(enum e_error num)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (num == E_ALLOC)
		ft_putendl_fd(strerror(ENOMEM), STDERR_FILENO);
	else if (num == E_ARG_LACK)
		ft_putendl_fd(strerror(ENOENT), STDERR_FILENO);
	else if (num == E_ARG_MANY)
		ft_putendl_fd(strerror(E2BIG), STDERR_FILENO);
	else if (num == E_FILE_INVAL)
		ft_putendl_fd("Is not .cub file", STDERR_FILENO);
	else if (num == E_FILE_FDERR)
		ft_putendl_fd("File descriptor is negative", STDERR_FILENO);
	resource_error(num);
	map_error(num);
	exit(EXIT_FAILURE);
}

void	resource_error(enum e_error num)
{
	if (num == E_RSRC_LACK)
		ft_putendl_fd("Need more map information", STDERR_FILENO);
	else if (num == E_TYPE_INVAL)
		ft_putendl_fd("Invalid type", STDERR_FILENO);
	else if (num == E_TEXT_NOTFD)
		ft_putendl_fd("Not contain texture file name", STDERR_FILENO);
	else if (num == E_TEXT_MANY)
		ft_putendl_fd("Too many texture", STDERR_FILENO);
	else if (num == E_COL_NOTFD)
		ft_putendl_fd("Not contain color data", STDERR_FILENO);
	else if (num == E_COL_LACK)
		ft_putendl_fd("Need more color", STDERR_FILENO);
	else if (num == E_COL_MANY)
		ft_putendl_fd("Too many color", STDERR_FILENO);
	else if (num == E_COL_INVAL)
		ft_putendl_fd("Invalid color", STDERR_FILENO);
	else if (num == E_PNG_FAIL)
		ft_putendl_fd("Faied to load png file", STDERR_FILENO);
}

void	map_error(enum e_error num)
{
	if (num == E_MAP_NOTFD)
		ft_putendl_fd("Not contain map data", STDERR_FILENO);
	else if (num == E_MAP_OTHEL)
		ft_putendl_fd("There is other element", STDERR_FILENO);
	else if (num == E_MAP_INVAL)
		ft_putendl_fd("Invalid map", STDERR_FILENO);
	else if (num == E_MAP_2PLAYER)
		ft_putendl_fd("Too many player in map", STDERR_FILENO);
	else if (num == E_MAP_NOPLAYER)
		ft_putendl_fd("Not contain player in map", STDERR_FILENO);
	else if (num == E_MLX)
		ft_putendl_fd("MLX error", STDERR_FILENO);
}
