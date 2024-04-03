/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:12:19 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/03 17:37:06 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/render.h"
#include <math.h>

char	*g_map[] = {
	"        1111111111111111111111111",
	"        1000000000110000000000001",
	"        1011000001110000000000001",
	"        1001000000000000000000001",
	"111111111011000001110000000000001",
	"100000000011000001110111111111111",
	"11110111111111011100000010001    ",
	"11110111111111011101010010001    ",
	"11000000110101011100000010001    ",
	"10000000000000001101010010001    ",
	"11000001110101011111011110N0111  ",
	"11110111 1110101 101111010001    ",
	"11111111 1111111 111111111111    "
};

int	main(void)
{
	// player
	//double posx = 26, posy = 10;
	//double dirx = 0, diry = -1;
	//double planx = 0.66, plany = 0;

	// 창 초기화
	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, WIDTH, HEIGHT, "test");
	void	*img = mlx_new_image(mlx, WIDTH, HEIGHT);
	int		bpp, len, end;
	int	*add = (int *)mlx_get_data_addr(img, &bpp, &len, &end);

	//int	h, w;
	//void	*test = mlx_png_file_to_image(mlx, "eagle.png", &w, &h);

	for (int y = 0; y < HEIGHT / 2; y++)
		for (int x = 0; x < WIDTH; x++)
			add[y * WIDTH + x] = CL;
	for (int y = HEIGHT / 2; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			add[y * WIDTH + x] = FL;
/*
	// 충돌 감지
	for (int x = 0; x < WIDTH; x++)
	{
		// ray 벡터 구하기
		double camera_rate = 2 * (x / WIDTH) - 1;
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
		int	hit = 0;
		int	hit_side;
		while (hit == 0)
		{
			if (g_map[i_posy][i_posx] == '1')
				hit = 1;
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
			dis = (fabs(i_posx - posx + (1 - stepx) / 2)) / rayx;
		else
			dis = (fabs(i_posy - posy + (1 - stepy) / 2)) / rayy;

		// 거리 비율 구하기
		int	hrate = (int)(HEIGHT / dis);
		int	start = -hrate / 2 + HEIGHT / 2;
		if (start < 0)
			start = 0;
		int	end = hrate / 2 + HEIGHT / 2;
		if (end >= HEIGHT)
			end = HEIGHT - 1;

		// 그리기
		for (int i = start; i <= end; i++)
			add[WIDTH * i + x] = NO;
		mlx_put_image_to_window(mlx, win, img, 0, 0);
	}
*/
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
