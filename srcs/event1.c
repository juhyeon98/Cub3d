/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:48:12 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/12 12:16:30 by taeoh            ###   ########.fr       */
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
	t_move	m;

	m.diffx = game->posx + game->dirx * SPEED;
	m.diffy = game->posy + game->diry * SPEED;
	m.collx = (-SPEED) * (game->dirx < 0) + COLL * (game->dirx > 0);
	m.colly = (-SPEED) * (game->diry < 0) + COLL * (game->diry > 0);
	m.leftx = game->posx + game->diry * COLL + game->dirx * SPEED;
	m.lefty = game->posy - game->dirx * COLL + game->diry * SPEED;
	m.rightx = game->posx - game->diry * COLL + game->dirx * SPEED;
	m.righty = game->posy + game->dirx * COLL + game->diry * SPEED;
	if ((game->map.map[(int)m.lefty][(int)(m.leftx + m.collx)] != '1') \
	&& (game->map.map[(int)m.righty][(int)(m.rightx + m.collx)] != '1' \
	&& (game->map.map[(int)game->posy][(int)(m.diffx + m.collx)] != '1')))
		game->posx = m.diffx;
	if ((game->map.map[(int)(m.lefty + m.colly)][(int)m.leftx] != '1') \
	&& (game->map.map[(int)(m.righty + m.colly)][(int)m.rightx] != '1') \
	&& (game->map.map[(int)(m.diffy + m.colly)][(int)game->posx] != '1'))
		game->posy = m.diffy;
}
