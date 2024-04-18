/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:26:56 by taeoh             #+#    #+#             */
/*   Updated: 2024/04/18 17:39:35 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	get_spr_i(t_game *game)
{
	unsigned int	t;

	t = (game->time / 4) % 8;
	if (t > 4)
		return (8 - t);
	else
		return (t);
}

void	init_sprite(t_game *const game, t_sprite *const s)
{
	s->spx = game->spx - game->posx;
	s->spy = game->spy - game->posy;
	s->inv_cam = 1.0 / (game->planx * game->diry - game->dirx * game->plany);
	s->camx = s->inv_cam * (game->diry * s->spx - game->dirx * s->spy);
	s->camy = s->inv_cam * (-game->plany * s->spx + game->planx * s->spy);
	s->screen = (int)(WIDTH / 2 * (1 + s->camx / s->camy));
	s->width = (int)fabs(HEIGHT / s->camy);
	s->ystart = -s->width / 2 + HEIGHT / 2;
	if (s->ystart < 0)
		s->ystart = 0;
	s->yend = s->width / 2 + HEIGHT / 2;
	if (s->yend >= HEIGHT)
		s->yend = HEIGHT;
	s->xstart = -s->width / 2 + s->screen;
	if (s->xstart < 0)
		s->xstart = 0;
	s->xend = s->width / 2 + s->screen;
	if (s->xend >= WIDTH)
		s->xend = WIDTH;
}

void	insert_sprite(t_game *const game, t_sprite *const s)
{
	int		i;
	int		j;
	char	*image;
	char	*tex;
	int		d;

	i = s->xstart - 1;
	while (++i < s->xend)
	{
		s->texx = i - (-s->width / 2 + s->screen) * 32 / s->width;
		if (s->camy >= 0 && i >= 0 && i <= WIDTH && s->camy < game->buffer[i])
		{
			j = s->ystart - 1;
			while (++j < s->yend)
			{
				d = j * 256 - HEIGHT * 128 + s->width * 128;
				s->texy = ((d * 32) / s->width) / 256;
				image = get_addr(game->spr, j, i);
				tex = get_addr(game->coin[get_spr_i(game)], s->texy, s->texx);
				*(unsigned int *)(image) = *(unsigned int *)(tex);
			}
		}
	}
}

void	put_sprite(t_game *const game)
{
	t_sprite	s;

	flush_image(&game->spr);
	init_sprite(game, &s);
	insert_sprite(game, &s);
	mlx_put_image_to_window(game->mlx, game->win, game->spr.obj, 0, 0);
}
