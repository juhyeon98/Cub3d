/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:46 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/09 13:24:30 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define NO "texture/north.png"
# define SO "texture/south.png"
# define WE "texture/west.png"
# define EA "texture/east.png"

# define FL 0x169C01
# define CL 0x1FE5CF

# define HEIGHT 1080
# define WIDTH 1920
# define TXT_WIDTH 32

# define ESC_KEY 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define KEY_EXIT 17
# define KEY_PRESS 2
# define FOV 67

# define ANGLE 0.1
# define SPEED 0.3
# define COLLISION 0.5

# define RIGHT_DIR -1
# define LEFT_DIR 1
# define UP_DIR -1
# define DOWN_DIR 1

# define DETC_Y 0
# define DETC_X 1

typedef enum e_type
{
	T_NL = -1,
	T_NO,
	T_SO,
	T_WE,
	T_EA,
	T_FL,
	T_CL
}t_type;

typedef unsigned int	t_color;

typedef struct s_resource
{
	char		*textures[4];
	t_color		colors[2][3];
	t_color		fl_color;
	t_color		cl_color;
}t_rsrc;

typedef struct s_map
{
	char	**map;
	size_t	h;
	size_t	w;
}t_map;

typedef struct s_img
{
	void	*obj;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	int		w;
	int		h;
}t_img;

typedef struct s_game
{
	t_rsrc	rsrc;
	t_map	map;

	void	*mlx;
	void	*win;
	t_img	screen;
	t_img	textures[4];

	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planx;
	double	plany;
}t_game;

typedef struct s_ray
{
	double	rayx;
	double	rayy;
	double	farx;
	double	fary;
	double	nearx;
	double	neary;
	int		posx;
	int		posy;
	int		stepx;
	int		stepy;

	int		hit_side;

	double	dis;
	double	over;
	int		to_draw;
	int		start;
	int		end;

	t_type	index;
	size_t	t_idx;
}t_ray;

/* init game */
void	init_game(t_game *const game);
void	init_rsrcs(void *const mlx, t_img *const rsrcs);

/* ray casting */
void	render(t_game *const game);
void	init_window(void *const mlx, void *constwin, t_img *const img);
void	set_back(t_img *const img, size_t const h_idx, t_color const col);
void	init_ray(t_game const game, t_ray *const ray, size_t w_idx);
void	init_nearvec(t_ray *const ray, t_game const game);

void	detech_wall(t_ray *const ray, t_map const map);

void	set_distance(t_game const game, t_ray *const ray);

void	select_texture(t_ray *const ray);
void	set_texture_index(t_game const game, t_ray *const ray);
void	draw_texture(t_game *const game, t_ray const ray, \
					size_t const w_idx);
char	*get_addr(t_img const img, size_t const y, size_t const x);

/* event */
int		close(void);
int		key_handling(int keycode, t_game *const game);
void	turn_right(t_game *const game);
void	turn_left(t_game *const game);
void	move_forward(t_game *const game);
void	move_back(t_game *const game);
void	move_right(t_game *const game);
void	move_left(t_game *const game);

#endif
