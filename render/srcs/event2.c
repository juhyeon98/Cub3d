/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:01:52 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/09 13:20:03 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/render.h"

void	move_back(t_game *const game)
{
	double const	diffx = game->posx - game->dirx * SPEED;
	double const	diffy = game->posy - game->diry * SPEED;

	if (game->map.map[(int)game->posy][(int)diffx] != '1')
		game->posx = diffx;
	if (game->map.map[(int)diffy][(int)game->posx] != '1')
		game->posy = diffy;
}

void	move_right(t_game *const game)
{
	double const	diffx = game->posx - game->diry * SPEED;
	double const	diffy = game->posy + game->dirx * SPEED;

	if (game->map.map[(int)game->posy][(int)diffx] != '1')
		game->posx = diffx;
	if (game->map.map[(int)diffy][(int)game->posx] != '1')
		game->posy = diffy;
}

void	move_left(t_game *const game)
{
	double const	diffx = game->posx + game->diry * SPEED;
	double const	diffy = game->posy - game->dirx * SPEED;

	if (game->map.map[(int)game->posy][(int)diffx] != '1')
		game->posx = diffx;
	if (game->map.map[(int)diffy][(int)game->posx] != '1')
		game->posy = diffy;
}
