/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:01:52 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/10 15:45:06 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_back(t_game *const game)
{
	double const	diffx = game->posx - game->dirx * SPEED;
	double const	diffy = game->posy - game->diry * SPEED;
	double const	xflag = \
				(-COLL) * (game->dirx < 0) + COLL * (game->dirx > 0);
	double const	yflag = \
				(-COLL) * (game->diry < 0) + COLL * (game->diry > 0);

	if (game->map.map[(int)game->posy][(int)(diffx - xflag)] != '1')
		game->posx = diffx;
	if (game->map.map[(int)(diffy - yflag)][(int)game->posx] != '1')
		game->posy = diffy;
}

void	move_right(t_game *const game)
{
	double const	diffx = game->posx - game->diry * SPEED;
	double const	diffy = game->posy + game->dirx * SPEED;
	double const	xflag = \
				(-COLL) * (game->dirx < 0) + COLL * (game->dirx > 0);
	double const	yflag = \
				(-COLL) * (game->diry < 0) + COLL * (game->diry > 0);

	if (game->map.map[(int)game->posy][(int)(diffx - yflag)] != '1')
		game->posx = diffx;
	if (game->map.map[(int)(diffy + xflag)][(int)game->posx] != '1')
		game->posy = diffy;
}

void	move_left(t_game *const game)
{
	double const	diffx = game->posx + game->diry * SPEED;
	double const	diffy = game->posy - game->dirx * SPEED;
	double const	xflag = \
				(-COLL) * (game->dirx < 0) + COLL * (game->dirx > 0);
	double const	yflag = \
				(-COLL) * (game->diry < 0) + COLL * (game->diry > 0);

	if (game->map.map[(int)game->posy][(int)(diffx + yflag)] != '1')
		game->posx = diffx;
	if (game->map.map[(int)(diffy - xflag)][(int)game->posx] != '1')
		game->posy = diffy;
}
