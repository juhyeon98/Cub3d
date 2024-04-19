/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fist_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:26:42 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/19 10:25:28 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_fist(t_game *const game, t_img const fist)
{
	mlx_put_image_to_window(game->mlx, game->win, fist.obj, \
	0, HEIGHT - fist.h);
}

void	animation_fist(t_game *const game)
{
	static size_t	frame;

	if (frame < 2)
		draw_fist(game, game->fist[1]);
	else if (frame < 4)
		draw_fist(game, game->fist[2]);
	else if (frame < 6)
		draw_fist(game, game->fist[1]);
	else
	{
		frame = 0;
		game->attack = 0;
		return ;
	}
	frame++;
}
