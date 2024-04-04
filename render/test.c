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

char	*g_map[] = {
	"1111111",
	"1000001",
	"100E001",
	"1000001",
	"1010101",
	"1010101",
	"1111111",
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

int	main(void)
{
	// player
	double posx = 4, posy = 2;
	double dirx = -1, diry = 0;
	double planx = 0, plany = 0.66;

	// 창 초기화
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, WIDTH, HEIGHT, "test");
	t_img	img;

	init_img(mlx, &img);
	init_window(mlx, win, &img);

	// 텍스처 로딩
	t_img	rsrcs[4];
	init_rsrcs(mlx, rsrcs);

	// 렌더링
	int x;
	for (x = 0; x < WIDTH; x++)
	{
		// ray 벡터 구하기
		double camera_rate = 2 * ((double)x / WIDTH) - 1;
		double rayx = dirx + planx * camera_rate;
		double rayy = diry + plany * camera_rate;

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
		int i_posx = (int)posx, i_posy = (int)posy;
		if (rayx < 0)
		{
			stepx = -1; // 오른쪽 방향
			nearx = (posx - i_posx) * farx;
		}
		else
		{
			stepx = 1; // 왼쪽 방향
			nearx = (i_posx + 1.0 - posx) * farx;
		}
		if (rayy < 0)
		{
			stepy = -1; // 위쪽 방향
			neary = (posy - i_posy) * fary;
		}
		else
		{
			stepy = 1; // 아래쪽 방향
			neary = (i_posy + 1.0 - posy) * fary;
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
			dis = (i_posx - posx + (1 - stepx) / 2) / rayx;
		else
			dis = (i_posy - posy + (1 - stepy) / 2) / rayy;
		// 거리 비율 구하기
		int	hrate = (int)(HEIGHT / dis);
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
			wallx = posy + dis * rayy;
		else
			wallx = posx + dis * rayx;
		wallx -= floor(wallx);
		
		int textx = (int)(wallx * (double)(TXT_WIDTH));
		if (hit_side == 0 && rayx > 0)
			textx = TXT_WIDTH - textx - 1;
		else if (hit_side == 1 && rayy < 0)
			textx = TXT_WIDTH - textx - 1;

		// 그리기
		for (int s_idx = start; s_idx < end; s_idx++)
		{
			int	i32 = TXT_WIDTH * (s_idx - start) / (end - start);
			char	*screen = img.addr + (s_idx * img.len + x * (img.bpp / 8));
			char	*text = rsrcs[index].addr + (i32 * rsrcs[index].len + textx * (rsrcs[index].bpp / 8));
			*(unsigned int *)(screen) = *(unsigned int *)(text);
		}
	}
	mlx_put_image_to_window(mlx, win, img.obj, 0, 0);
	// 렌더링은 특별한 이벤트가 없다면 동일한 화면 유지(렌더링 x)

	// 이벤트 처리
	mlx_loop(mlx);
	return (0);
}
