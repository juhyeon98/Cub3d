/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:12:19 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/03 19:53:09 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/render.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char	*g_map[] = {
    "        1111111111111111111111111",
    "        1000000000110000000000001",
    "        1011000001110000000000001",
    "        1001000000000000000000001",
    "111111111011000001110000000000001",
    "100000000011000001110111110111111",
    "11110111111111011100000010001    ",
    "11110111111111011101010010001    ",
    "11000000110101011100000010001    ",
    "10000000000000001100000010001    ",
    "10000000000000001101010010001    ",
    "11000001110101011111011110N0111  ",
    "11110111 1110101 101111110001    ",
    "11111111 1111111 111111111111    "
};

void	init_window(void *mlx, void *win, t_img *img)
{
	mlx_clear_window(mlx, win);
	for (int y = 0; y < HEIGHT / 2; y++)
		for (int x = 0; x < WIDTH; x++)
			*(unsigned int *)(img->addr + y * img->len + (img->bpp / 8) * x) = CL;
	for (int y = HEIGHT / 2; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			*(unsigned int *)(img->addr + y * img->len + (img->bpp / 8) * x) = FL;
}

void	init_img(void *mlx, t_img *img)
{
	img->obj = mlx_new_image(mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->obj, &(img->bpp), &(img->len), &(img->endian));
}

void	init_rsrcs(void *mlx, t_img *rsrcs)
{
	rsrcs[0].obj = mlx_png_file_to_image(mlx, NO, &rsrcs[0].w, &rsrcs[0].h);
	rsrcs[0].addr = mlx_get_data_addr(rsrcs[0].obj, &rsrcs[0].bpp, &rsrcs[0].len, &rsrcs[0].endian);
	
	rsrcs[1].obj = mlx_png_file_to_image(mlx, SO, &rsrcs[1].w, &rsrcs[1].h);
	rsrcs[1].addr = mlx_get_data_addr(rsrcs[1].obj, &rsrcs[1].bpp, &rsrcs[1].len, &rsrcs[1].endian);
	
	rsrcs[2].obj = mlx_png_file_to_image(mlx, WE, &rsrcs[2].w, &rsrcs[2].h);
	rsrcs[2].addr = mlx_get_data_addr(rsrcs[2].obj, &rsrcs[2].bpp, &rsrcs[2].len, &rsrcs[2].endian);
	
	rsrcs[3].obj = mlx_png_file_to_image(mlx, EA, &rsrcs[3].w, &rsrcs[3].h);
	rsrcs[3].addr = mlx_get_data_addr(rsrcs[3].obj, &rsrcs[3].bpp, &rsrcs[3].len, &rsrcs[3].endian);
}

void	render(t_game *game)
{
	init_window(game->mlx, game->win, &game->screen);

	int x;
	for (x = 0; x < WIDTH; x++)
	{
		// ray 벡터 구하기
		double camera_rate = 2 * ((double)x / WIDTH) - 1;
		double rayx = game->dirx + game->planx * camera_rate;
		double rayy = game->diry + game->plany * camera_rate;

		// 측정용 벡터 구하기
		double	farx, fary;
		if (rayx == 0)
			fary = 0;
		else if (rayy == 0)
			fary = 1;
		else
			fary = fabs(1 / rayy);
		if (rayy == 0)
			farx = 0;
		else if (rayx == 0)
			farx = 1;
		else
			farx = fabs(1 / rayx);
		double	nearx, neary;
		int	stepx, stepy;
		int i_posx = (int)game->posx, i_posy = (int)game->posy;
		if (rayx < 0)
		{
			stepx = -1; // 오른쪽 방향
			nearx = (game->posx - i_posx) * farx;
		}
		else
		{
			stepx = 1; // 왼쪽 방향
			nearx = (i_posx + 1.0 - game->posx) * farx;
		}
		if (rayy < 0)
		{
			stepy = -1; // 위쪽 방향
			neary = (game->posy - i_posy) * fary;
		}
		else
		{
			stepy = 1; // 아래쪽 방향
			neary = (i_posy + 1.0 - game->posy) * fary;
		}

		// dda
		int	hit_side;
		while (1)
		{
			if (g_map[i_posy][i_posx] == '1')
				break ;
			if (nearx < neary)
			{
				nearx += farx;
				i_posx += stepx;
				hit_side = 0; // y축에 충돌
			}
			else
			{
				neary += fary;
				i_posy += stepy;
				hit_side =  1; // x축에 충돌
			}
		}

		// 거리 구하기
		double dis;
		if (hit_side == 0)
			dis = (i_posx - game->posx + (1 - stepx) / 2) / rayx;
		else
			dis = (i_posy - game->posy + (1 - stepy) / 2) / rayy;
		// 거리 비율 구하기
		int	hrate = abs((int)(HEIGHT / dis));
		double h_over = (double)hrate / HEIGHT; //1이상인 경우 화면 넘는 것임
		int	start = -hrate / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int	end = hrate / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;

		// 컬러 판단
		size_t	index = 0;
		if (hit_side == 0 && rayx < 0)
			index = 3;
		else if (hit_side == 0 && rayx >= 0)
			index = 2;
		else if (hit_side == 1 && rayy < 0)
			index = 1;
		else if (hit_side == 1 && rayy >= 0)
			index = 0;

		// 그릴 위치 구하기
		double	wallx;
		if (hit_side == 0)
			wallx = game->posy + dis * rayy;
		else
			wallx = game->posx + dis * rayx;
		wallx -= floor(wallx);
		
		int textx = (int)(wallx * (double)(TXT_WIDTH));
		if (hit_side == 0 && rayx > 0)
			textx = TXT_WIDTH - textx - 1;
		else if (hit_side == 1 && rayy < 0)
			textx = TXT_WIDTH - textx - 1;

		// 그리기
		// 맨 아래 픽셀
		int	i32;
		for (int s_idx = start; s_idx < end; s_idx++)
		{
			if (h_over < 1) i32 = TXT_WIDTH * (s_idx - start) / (end - start); //height
			else i32 = (int)((TXT_WIDTH - (double)TXT_WIDTH / h_over) / 2 + ((double)TXT_WIDTH / h_over) * (s_idx - start) / (double)(end - start));
			char	*screen = game->screen.addr + (s_idx * game->screen.len + x * (game->screen.bpp / 8));
			char	*text = game->textures[index].addr + (i32 * game->textures[index].len + (31 - textx) * (game->textures[index].bpp / 8));
			*(unsigned int *)(screen) = *(unsigned int *)(text);
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.obj, 0, 0);
}

void	close(void)
{
	exit(0);
}

void	key_handling(int keycode, t_game *const game)
{
	if (keycode == ESC_KEY)
		exit(1);
	if (keycode == RIGHT)
	{
		double	olddirx = game->dirx;
		double olddiry = game->diry;
		game->dirx = olddirx * cos(ANGLE) - olddiry * sin(ANGLE);
		game->diry = olddirx * sin(ANGLE) + olddiry * cos(ANGLE);
		double	oldplanx = game->planx;
		double oldplany = game->plany;
		game->planx = oldplanx * cos(ANGLE) - oldplany * sin(ANGLE);
		game->plany = oldplanx * sin(ANGLE) + oldplany * cos(ANGLE);
	}
	else if (keycode == LEFT)
	{
		double	olddirx = game->dirx;
		double olddiry = game->diry;
		game->dirx = olddirx * cos(-ANGLE) - olddiry * sin(-ANGLE);
		game->diry = olddirx * sin(-ANGLE) + olddiry * cos(-ANGLE);
		double	oldplanx = game->planx;
		double oldplany = game->plany;
		game->planx = oldplanx * cos(-ANGLE) - oldplany * sin(-ANGLE);
		game->plany = oldplanx * sin(-ANGLE) + oldplany * cos(-ANGLE);
	}
	else if (keycode == W)
	{
		printf("%c\n", g_map[(int)game->posy][(int)game->posx]);
		printf("%lf %lf\n", game->posx, game->posy);
		if (g_map[(int)(game->posy)][(int)(game->posx + game->dirx * SPEED)] != '1')
			game->posx += (game->dirx * SPEED);
		if (g_map[(int)(game->posy + game->diry * SPEED)][(int)(game->posx)] != '1')
			game->posy += (game->diry * SPEED);
	}
	else if (keycode == S)
	{
		if (g_map[(int)(game->posy)][(int)(game->posx - game->dirx * SPEED)] != '1')
			game->posx -= (game->dirx * SPEED);
		if (g_map[(int)(game->posy - game->diry * SPEED)][(int)(game->posx)] != '1')
			game->posy -= (game->diry * SPEED);
	}
	else if (keycode == D)
	{
		if (g_map[(int)(game->posy)][(int)(game->posx - game->diry * SPEED)] != '1')
			game->posx -= (game->diry * SPEED);
		if (g_map[(int)(game->posy + game->dirx * SPEED)][(int)(game->posx)] != '1')
			game->posy += (game->dirx * SPEED);
	}
	else if (keycode == A)
	{
		if (g_map[(int)(game->posy)][(int)(game->posx + game->diry * SPEED)]!= '1')
			game->posx += (game->diry * SPEED);
		if (g_map[(int)(game->posy - game->dirx * SPEED)][(int)(game->posx)] != '1')
			game->posy -= (game->dirx * SPEED);
	}
	render(game);
}

int	main(void)
{
	t_game	game;

// init
	// player
	game.posx = 26;
	game.posy = 11;
	game.dirx = 0;
	game.diry = -1;
	game.planx = 0.87;
	game.plany = 0;

	// 창 초기화
	game.mlx = mlx_init();
	init_img(game.mlx, &game.screen);
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");

	// 텍스처 로딩
	init_rsrcs(game.mlx, game.textures);

// play
	render(&game);

	// 이벤트 처리
	// x 버튼 눌렀을 때
	mlx_hook(game.win, KEY_EXIT, 0, close, NULL);
	// 키보드 입력
	mlx_hook(game.win, KEY_PRESS, 0, key_handling, &game);
	mlx_loop(game.mlx);
	return (0);
}