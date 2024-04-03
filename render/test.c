/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:12:19 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/03 13:04:49 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx/mlx.h"

int	main(void)
{
	void	*win;
	void	*mlx;

	void	*img;
	int		w, h;

	char	*addr;
	int		bpp, len, end;

	char	*loc;

	// 창 초기화
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "test");

	// 이미지 가져오기
	img = mlx_png_file_to_image(mlx, "eagle.png", &w, &h);

	// 화면에 뿌리기
	addr = mlx_get_data_addr(img, &bpp, &len, &end);
	loc = addr + (50 * len + 50 * (bpp / 8));
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	printf("%p\n", addr);

	mlx_loop(mlx);
	return (0);
}
