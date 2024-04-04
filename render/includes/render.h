/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:46 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/03 19:47:49 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../mlx/mlx.h"

# define HEIGHT 600
# define WIDTH 800

# define NO "texture/north.png" //0xFF0000
# define SO "texture/south.png" //0x00FF00
# define WE "texture/west.png" //0x0000FF
# define EA "texture/east.png" //0xFFFFFF

# define FL 0x169C01
# define CL 0x1FE5CF

# define TXT_WIDTH 32
# define ESC_KEY 53
# define KEY_EXIT 17
# define KEY_PRESS 2
# define FOV 67

typedef struct s_img
{
    void    *obj;
    char    *addr;
    int     bpp;
    int     len;
    int     endian;
    int     w;
    int     h;
}t_img;

//typedef struct s_r_vec
//{
//	double	x;
//	double	y;
//}t_r_vec;

//typedef struct s_z_vec
//{
//	int	x;
//	int	y;
//}t_z_vec;

//typedef struct s_player
//{
//	t_r_vec	pos;
//	t_r_vec	dir;
//	t_r_vec	plan;
//}t_player;

//typedef struct s_ray
//{
//	t_r_vec			vec;
//	unsigned int	dis;
//}t_ray;

// image struct 필요

//double	ray_casting(t_player *const player, t_ray const ray);
//double

#endif
