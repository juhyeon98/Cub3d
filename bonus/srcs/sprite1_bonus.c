/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:26:56 by taeoh             #+#    #+#             */
/*   Updated: 2024/04/18 16:23:21 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	get_sprite_index(t_game *game)
{
	unsigned int	t;

	t = (game->time / 4) % 8;
	if (t > 4)
		return (8 - t);
	else
		return (t);
}

void	put_sprite(t_game *game)
{
	flush_image(&game->spr);
	//sprite 찾기
	game->spix = 26.5;
	game->spiy = 8.5;
	double	spx = game->spix - game->posx;
	double	spy = game->spiy - game->posy;
	double	inv_cam = 1.0 / (game->planx * game->diry - game->dirx * game->plany);
	double	camx = inv_cam * (game->diry * spx - game->dirx * spy); //player와 수직거리
	double	camy = inv_cam * (-game->plany * spx + game->planx * spy); //sprite의 수평거리(?)

	int	spscreen = (int)(WIDTH / 2 * (1 + camx / camy));

	int	spheight = (int)fabs(HEIGHT / camy);
	int spstarty = -spheight / 2 + HEIGHT / 2;
	if (spstarty < 0) spstarty = 0;
	int spendy = spheight / 2 + HEIGHT / 2;
	if (spendy >= HEIGHT) spendy = HEIGHT;//

	int spstartx = -spheight / 2 + spscreen;
	if (spstartx < 0) spstartx = 0;
	int spendx = spheight / 2 + spscreen;
	if (spendx >= WIDTH) spendx = WIDTH;//

	for (int i = spstartx; i < spendx; i++)
	{
		int texx = (int)(256 * (i - (-spheight / 2 + spscreen)) * 32 / spheight) / 256;
		if (camy >= 0 && i >= 0 && i <= WIDTH && camy < game->buffer[i])
			for (int y = spstarty; y < spendy; y++)
			{
				int d = y * 256 - HEIGHT * 128 + spheight * 128;
				int texy = ((d * 32) / spheight) / 256;
				char *image = get_addr(game->spr, y, i);
				// printf("1\n");
				char *texture = get_addr(game->coin[get_sprite_index(game)], texy, texx);
				// if (texy < game->coin.h && texx < game->coin.w)
				// printf("2\n");
				*(unsigned int *)(image) = *(unsigned int *)(texture);
			}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->spr.obj, 0, 0);
}
