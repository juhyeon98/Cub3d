/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:55:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/09 14:09:49 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render(t_game *game)
{
	t_ray	ray;
	size_t	w_idx;

	init_window(game->mlx, game->win, &game->screen, &game->rsrc);
	w_idx = 0;
	while (w_idx < WIDTH)
	{
		init_ray(*game, &ray, w_idx);
		detech_wall(&ray, game->map);
		set_distance(*game, &ray);
		select_texture(&ray);
		set_texture_index(*game, &ray);
		draw_texture(game, ray, w_idx);
		w_idx++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.obj, 0, 0);
}

void	set_back(t_img *const img, size_t const h_idx, t_color const col)
{
	char	*addr;
	size_t	w_idx;

	w_idx = 0;
	while (w_idx < WIDTH)
	{
		addr = get_addr(*img, h_idx, w_idx);
		*(unsigned int *)addr = col;
		w_idx++;
	}
}

void	init_ray(t_game const game, t_ray *const ray, size_t w_idx)
{
	double const	camera_rate = 2 * ((double)w_idx / WIDTH) - 1;

	ray->rayx = game.dirx + game.planx * camera_rate;
	ray->rayy = game.diry + game.plany * camera_rate;
	if (ray->rayx == 0)
		ray->fary = 0;
	else if (ray->rayy == 0)
		ray->fary = 1;
	else
		ray->fary = fabs(1 / ray->rayy);
	if (ray->rayy == 0)
		ray->farx = 0;
	else if (ray->rayx == 0)
		ray->farx = 1;
	else
		ray->farx = fabs(1 / ray->rayx);
	init_nearvec(ray, game);
}

void	init_nearvec(t_ray *const ray, t_game const game)
{
	ray->posx = game.posx;
	ray->posy = game.posy;
	if (ray->rayx < 0)
	{
		ray->stepx = RIGHT_DIR;
		ray->nearx = (game.posx - ray->posx) * ray->farx;
	}
	else
	{
		ray->stepx = LEFT_DIR;
		ray->nearx = (ray->posx + 1.0 - game.posx) * ray->farx;
	}
	if (ray->rayy < 0)
	{
		ray->stepy = UP_DIR;
		ray->neary = (game.posy - ray->posy) * ray->fary;
	}
	else
	{
		ray->stepy = DOWN_DIR;
		ray->neary = (ray->posy + 1.0 - game.posy) * ray->fary;
	}
}
