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

void	init_window(void *mlx, void *win, void *img)
{
	int	bpp, len, end;
	char	*add = mlx_get_data_addr(img, &bpp, &len, &end);

	mlx_clear_window(mlx, win);
	for (int y = 0; y < HEIGHT / 2; y++)
		for (int x = 0; x < WIDTH; x++)
			*(unsigned int *)(add + y * len + (bpp / 8) * x) = CL;
	for (int y = HEIGHT / 2; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			*(unsigned int *)(add + y * len + (bpp / 8) * x) = FL;
}

int	main(void)
{
	// player
	double posx = 4, posy = 2;
	double dirx = 0, diry = 1;
	double planx = 0.66, plany = 0;

	// 창 초기화
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, WIDTH, HEIGHT, "test");
	void	*img = mlx_new_image(mlx, WIDTH, HEIGHT);

	//int	h, w;
	//void	*test = mlx_png_file_to_image(mlx, "eagle.png", &w, &h);

	init_window(mlx, win, img);
	// 충돌 감지
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
		//printf("[%d] hrate : %d | %d ~ %d\n", x, hrate, start, end);

		// 컬러 판단
		int	color = 0;
		if (hit_side == 0 && rayx < 0)
			color = EA;
		else if (hit_side == 0 && rayx >= 0)
			color = WE;
		else if (hit_side == 1 && rayy < 0)
			color = SO;
		else if (hit_side == 1 && rayy >= 0)
			color = NO;

		// 그리기
		int	bpp, len, endian;
		char	*addr = mlx_get_data_addr(img, &bpp, &len, &endian);
		for (int index = start; index < end; index++)
		{
			char	*col = addr + (index * len + x * (bpp / 8));
			*(unsigned int *)col = color;
		}
	}
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	//printf("\n%d\n", x);
	mlx_loop(mlx);
	return (0);
}
