/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:48:12 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/17 13:54:48 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <stdio.h>

int	exit_program(void)
{
	exit(0);
	return (0);
}

int	key_press(int keycode, t_game *const game)
{
	if (keycode == ESC_KEY)
		exit(1);
	if (keycode == RIGHT)
		game->turn_right = 1;
	else if (keycode == LEFT)
		game->turn_left = 1;
	else if (keycode == W)
		game->move_front = 1;
	else if (keycode == S)
		game->move_back = 1;
	else if (keycode == D)
		game->move_right = 1;
	else if (keycode == A)
		game->move_left = 1;
	return (0);
}

void	door_handling(t_game *const game)
{
	int	x;
	int	y;

	x = game->posx + game->dirx;
	y = game->posy + game->diry;
	if (game->map.map[y][x] == 'D')
		game->map.map[y][x] = 'O';
	else if (game->map.map[y][x] == 'O')
		game->map.map[y][x] = 'D';
}

void	turn(t_game *const game, double const diff)
{
	double const	olddirx = game->dirx;
	double const	olddiry = game->diry;
	double const	oldplanx = game->planx;
	double const	oldplany = game->plany;

	game->dirx = olddirx * cos(ANGLE * diff) - olddiry * sin(ANGLE * diff);
	game->diry = olddirx * sin(ANGLE * diff) + olddiry * cos(ANGLE * diff);
	game->planx = oldplanx * cos(ANGLE * diff) - oldplany * sin(ANGLE * diff);
	game->plany = oldplanx * sin(ANGLE * diff) + oldplany * cos(ANGLE * diff);
}

void	move_forward(t_game *const game)
{
	t_move	m;

	m.diffx = game->posx + game->dirx * SPEED;
	m.diffy = game->posy + game->diry * SPEED;
	m.collx = (-SPEED) * (game->dirx < 0) + SPEED * (game->dirx > 0);
	m.colly = (-SPEED) * (game->diry < 0) + SPEED * (game->diry > 0);
	m.leftx = game->posx + game->diry * COLL + game->dirx * SPEED;
	m.lefty = game->posy - game->dirx * COLL + game->diry * SPEED;
	m.rightx = game->posx - game->diry * COLL + game->dirx * SPEED;
	m.righty = game->posy + game->dirx * COLL + game->diry * SPEED;
	if (game->map.map[(int)m.lefty][(int)(m.leftx + m.collx)] != '1' \
	&& game->map.map[(int)m.righty][(int)(m.rightx + m.collx)] != '1' \
	&& game->map.map[(int)game->posy][(int)(m.diffx + m.collx)] != '1' \
	&& game->map.map[(int)m.lefty][(int)(m.leftx + m.collx)] != 'D' \
	&& game->map.map[(int)m.righty][(int)(m.rightx + m.collx)] != 'D' \
	&& game->map.map[(int)game->posy][(int)(m.diffx + m.collx)] != 'D')
		game->posx = m.diffx;
	if (game->map.map[(int)(m.lefty + m.colly)][(int)m.leftx] != '1' \
	&& game->map.map[(int)(m.righty + m.colly)][(int)m.rightx] != '1' \
	&& game->map.map[(int)(m.diffy + m.colly)][(int)game->posx] != '1' \
	&& game->map.map[(int)(m.lefty + m.colly)][(int)m.leftx] != 'D' \
	&& game->map.map[(int)(m.righty + m.colly)][(int)m.rightx] != 'D' \
	&& game->map.map[(int)(m.diffy + m.colly)][(int)game->posx] != 'D')
		game->posy = m.diffy;
}
