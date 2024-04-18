/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:55:33 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/18 17:24:12 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	flush_wall(t_img *const wall)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < HEIGHT)
	{
		while (++x < WIDTH)
			*(unsigned int *)(wall->addr + y * wall->len + (wall->bpp / 8) * x) \
				= 0xFF000000;
		x = -1;
	}
}

void	render(t_game *game)
{
	size_t	w_idx;

	init_window(game->mlx, game->win, &game->screen, &game->rsrc);
	flush_wall(&game->wall);
	w_idx = 0;
	while (w_idx < WIDTH)
	{
		init_ray(*game, &game->ray, w_idx);
		detech_wall(&game->ray, game->map);
		set_distance(game, &game->ray);
		game->buffer[w_idx] = game->ray.dis;
		select_texture(&game->ray);
		set_texture_index(*game, &game->ray);
		draw_texture(game, game->ray, w_idx);
		w_idx++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.obj, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->wall.obj, 0, 0);
	put_sprite(game);
	put_minimap(game);
	if (game->attack == 0)
		draw_fist(game, game->fist[0]);
	else
		animation_fist(game);
	mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, game->win);
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
