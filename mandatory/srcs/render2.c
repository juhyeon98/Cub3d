/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:31:36 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/09 16:38:23 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	detech_wall(t_ray *const ray, t_map const map)
{
	while (1)
	{
		if (map.map[ray->posy][ray->posx] == '1')
			break ;
		if (ray->nearx < ray->neary)
		{
			ray->nearx += ray->farx;
			ray->posx += ray->stepx;
			ray->hit_side = DETC_Y;
		}
		else
		{
			ray->neary += ray->fary;
			ray->posy += ray->stepy;
			ray->hit_side = DETC_X;
		}
	}
}

void	set_distance(t_game const game, t_ray *const ray)
{
	double const	rayx = ray->rayx;
	double const	rayy = ray->rayy;
	int const		stepx = ray->stepx;
	int const		stepy = ray->stepy;

	if (ray->hit_side == DETC_Y)
		ray->dis = (ray->posx - game.posx + (1 - stepx) / 2) / rayx;
	else
		ray->dis = (ray->posy - game.posy + (1 - stepy) / 2) / rayy;
	ray->to_draw = abs((int)(HEIGHT / ray->dis));
	ray->over = (double)ray->to_draw / HEIGHT;
	ray->start = -ray->to_draw / 2 + HEIGHT / 2;
	if (ray->start < 0)
		ray->start = 0;
	ray->end = ray->to_draw / 2 + HEIGHT / 2;
	if (ray->end >= HEIGHT)
		ray->end = HEIGHT;
}

void	select_texture(t_ray *const ray)
{
	if (ray->hit_side == DETC_Y && ray->rayx < 0)
		ray->index = T_EA;
	else if (ray->hit_side == DETC_Y && ray->rayx >= 0)
		ray->index = T_WE;
	else if (ray->hit_side == DETC_X && ray->rayy < 0)
		ray->index = T_SO;
	else if (ray->hit_side == DETC_X && ray->rayy >= 0)
		ray->index = T_NO;
}

void	set_texture_index(t_game const game, t_ray *const ray)
{
	double	wallx;

	if (ray->hit_side == DETC_Y)
		wallx = game.posy + ray->dis * ray->rayy;
	else
		wallx = game.posx + ray->dis * ray->rayx;
	wallx -= floor(wallx);
	ray->t_idx = (int)(wallx * (double)(TXT_WIDTH));
	if (ray->hit_side == DETC_Y && ray->rayx > 0)
		ray->t_idx = TXT_WIDTH - ray->t_idx - 1;
	else if (ray->hit_side == DETC_X && ray->rayy < 0)
		ray->t_idx = TXT_WIDTH - ray->t_idx - 1;
}

void	draw_texture(t_game *const game, t_ray const ray, \
					size_t const w_idx)
{
	int		last_idx;
	int		draw_idx;
	char	*screen;
	char	*texture;

	draw_idx = ray.start;
	while (draw_idx < ray.end)
	{
		if (ray.over < 1)
			last_idx = TXT_WIDTH * (draw_idx - ray.start) \
						/ (ray.end - ray.start);
		else
			last_idx = (int)((TXT_WIDTH - (double)TXT_WIDTH / ray.over) \
						/ 2 + ((double)TXT_WIDTH / ray.over) \
						* (draw_idx - ray.start) / \
						(double)(ray.end - ray.start));
		screen = get_addr(game->screen, draw_idx, w_idx);
		texture = get_addr(game->textures[ray.index], last_idx, 31 - ray.t_idx);
		*(unsigned int *)(screen) = *(unsigned int *)(texture);
		draw_idx++;
	}
}
