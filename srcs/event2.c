/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:01:52 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/12 13:02:07 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_back(t_game *const game)
{
	t_move	m;

	m.diffx = game->posx - game->dirx * SPEED;
	m.diffy = game->posy - game->diry * SPEED;
	m.collx = (-SPEED) * (game->dirx < 0) + SPEED * (game->dirx > 0);
	m.colly = (-SPEED) * (game->diry < 0) + SPEED * (game->diry > 0);
	m.leftx = game->posx + game->diry * COLL - game->dirx * SPEED;
	m.lefty = game->posy - game->dirx * COLL - game->diry * SPEED;
	m.rightx = game->posx - game->diry * COLL - game->dirx * SPEED;
	m.righty = game->posy + game->dirx * COLL - game->diry * SPEED;
	if ((game->map.map[(int)m.lefty][(int)(m.leftx - m.collx)] != '1') \
	&& (game->map.map[(int)m.righty][(int)(m.rightx - m.collx)] != '1' \
	&& (game->map.map[(int)game->posy][(int)(m.diffx - m.collx)] != '1')))
		game->posx = m.diffx;
	if ((game->map.map[(int)(m.lefty - m.colly)][(int)m.leftx] != '1') \
	&& (game->map.map[(int)(m.righty - m.colly)][(int)m.rightx] != '1') \
	&& (game->map.map[(int)(m.diffy - m.colly)][(int)game->posx] != '1'))
		game->posy = m.diffy;
}

void	move_right(t_game *const game)
{
	t_move	m;

	m.diffx = game->posx - game->diry * SPEED;
	m.diffy = game->posy + game->dirx * SPEED;
	m.collx = (-SPEED) * (game->dirx < 0) + SPEED * (game->dirx > 0);
	m.colly = (-SPEED) * (game->diry < 0) + SPEED * (game->diry > 0);
	m.leftx = game->posx - game->dirx * COLL - game->diry * SPEED;
	m.lefty = game->posy + game->diry * COLL + game->dirx * SPEED;
	m.rightx = game->posx + game->dirx * COLL - game->diry * SPEED;
	m.righty = game->posy - game->diry * COLL + game->dirx * SPEED;
	if ((game->map.map[(int)m.lefty][(int)(m.leftx - m.colly)] != '1') \
	&& (game->map.map[(int)m.righty][(int)(m.rightx - m.colly)] != '1' \
	&& (game->map.map[(int)game->posy][(int)(m.diffx - m.colly)] != '1')))
		game->posx = m.diffx;
	if ((game->map.map[(int)(m.lefty + m.collx)][(int)m.leftx] != '1') \
	&& (game->map.map[(int)(m.righty + m.collx)][(int)m.rightx] != '1') \
	&& (game->map.map[(int)(m.diffy + m.collx)][(int)game->posx] != '1'))
		game->posy = m.diffy;
}

void	move_left(t_game *const game)
{
	t_move	m;

	m.diffx = game->posx + game->diry * SPEED;
	m.diffy = game->posy - game->dirx * SPEED;
	m.collx = (-SPEED) * (game->dirx < 0) + SPEED * (game->dirx > 0);
	m.colly = (-SPEED) * (game->diry < 0) + SPEED * (game->diry > 0);
	m.leftx = game->posx + game->dirx * COLL + game->diry * SPEED;
	m.lefty = game->posy - game->diry * COLL - game->dirx * SPEED;
	m.rightx = game->posx + game->dirx * COLL + game->diry * SPEED;
	m.righty = game->posy - game->diry * COLL - game->dirx * SPEED;
	if ((game->map.map[(int)m.lefty][(int)(m.leftx + m.colly)] != '1') \
	&& (game->map.map[(int)m.righty][(int)(m.rightx + m.colly)] != '1' \
	&& (game->map.map[(int)game->posy][(int)(m.diffx + m.colly)] != '1')))
		game->posx = m.diffx;
	if ((game->map.map[(int)(m.lefty - m.collx)][(int)m.leftx] != '1') \
	&& (game->map.map[(int)(m.righty - m.collx)][(int)m.rightx] != '1') \
	&& (game->map.map[(int)(m.diffy - m.collx)][(int)game->posx] != '1'))
		game->posy = m.diffy;
}
