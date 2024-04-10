/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:48:12 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/10 15:37:47 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	exit_program(void)
{
	exit(0);
	return (0);
}

int	key_handling(int keycode, t_game *const game)
{
	if (keycode == ESC_KEY)
		exit(1);
	if (keycode == RIGHT)
		turn_right(game);
	else if (keycode == LEFT)
		turn_left(game);
	else if (keycode == W)
		move_forward(game);
	else if (keycode == S)
		move_back(game);
	else if (keycode == D)
		move_right(game);
	else if (keycode == A)
		move_left(game);
	render(game);
	return (0);
}

void	turn_right(t_game *const game)
{
	double const	olddirx = game->dirx;
	double const	olddiry = game->diry;
	double const	oldplanx = game->planx;
	double const	oldplany = game->plany;

	game->dirx = olddirx * cos(ANGLE) - olddiry * sin(ANGLE);
	game->diry = olddirx * sin(ANGLE) + olddiry * cos(ANGLE);
	game->planx = oldplanx * cos(ANGLE) - oldplany * sin(ANGLE);
	game->plany = oldplanx * sin(ANGLE) + oldplany * cos(ANGLE);
}

void	turn_left(t_game *const game)
{
	double const	olddirx = game->dirx;
	double const	olddiry = game->diry;
	double const	oldplanx = game->planx;
	double const	oldplany = game->plany;

	game->dirx = olddirx * cos(-ANGLE) - olddiry * sin(-ANGLE);
	game->diry = olddirx * sin(-ANGLE) + olddiry * cos(-ANGLE);
	game->planx = oldplanx * cos(-ANGLE) - oldplany * sin(-ANGLE);
	game->plany = oldplanx * sin(-ANGLE) + oldplany * cos(-ANGLE);
}

void	move_forward(t_game *const game)
{
	double const	diffx = game->posx + game->dirx * SPEED;
	double const	diffy = game->posy + game->diry * SPEED;

	if (game->map.map[(int)game->posy][(int)diffx] != '1')
		game->posx = diffx;
	if (game->map.map[(int)diffy][(int)game->posx] != '1')
		game->posy = diffy;
}
