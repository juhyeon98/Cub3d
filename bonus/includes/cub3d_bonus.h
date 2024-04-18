/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:43:32 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/18 17:27:34 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft_bonus.h"
# include "../../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>

# define BUFF_SZ 31

# define HEIGHT 720
# define WIDTH 1280
# define TXT_WIDTH 32
# define MAX_HEIGHT 10000

# define FL_RSRCS 0x3F

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define E 14
# define SPACE 49
# define LEFT 123
# define RIGHT 124
# define KEY_EXIT 17
# define KEY_PRESS 2

# define FOV 0.87
# define ANGLE 0.05
# define SPEED 0.05
# define COLL 0.01

# define RIGHT_DIR -1
# define LEFT_DIR 1
# define UP_DIR -1
# define DOWN_DIR 1

# define DETC_Y 0
# define DETC_X 1

enum e_error
{
	E_ALLOC,
	E_ARG_LACK,
	E_ARG_MANY,
	E_FILE_INVAL,
	E_FILE_FDERR,
	E_RSRC_LACK,
	E_RSRC_DUP,
	E_TYPE_INVAL,
	E_TEXT_NOTFD,
	E_TEXT_MANY,
	E_COL_NOTFD,
	E_COL_LACK,
	E_COL_FORM,
	E_COL_INVAL,
	E_XPM_NOTFE,
	E_XPM_FAIL,
	E_MAP_NOTFD,
	E_MAP_OTHEL,
	E_MAP_INVAL,
	E_MAP_EMPL,
	E_MAP_2BIG,
	E_MAP_2PLAYER,
	E_MAP_2COIN,
	E_MAP_NOPLAYER,
	E_MLX
};

typedef enum e_type
{
	T_NL = -1,
	T_NO,
	T_SO,
	T_WE,
	T_EA,
	T_FL,
	T_CL,
	D1
}t_type;

typedef unsigned int	t_color;

typedef struct s_resource
{
	char		*textures[4];
	t_color		colors[2];
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
	int		is_door;

	double	dis;
	double	over;
	int		to_draw;
	int		start;
	int		end;

	t_type	index;
	size_t	t_idx;
}t_ray;

typedef struct s_draw
{
	int		last_idx;
	int		draw_idx;
	char	*screen;
	char	*texture;
}t_draw;

typedef struct s_sprite
{
	double	spx;
	double	spy;
	double	inv_cam;
	double	camx;
	double	camy;
	int		screen;
	int		width;
	int		xstart;
	int		ystart;
	int		xend;
	int		yend;
	int		texx;
	int		texy;
}t_sprite;

typedef struct s_game
{
	t_rsrc	rsrc;
	t_map	map;

	t_img	screen;
	t_img	textures[4];
	t_img	fist[3];
	t_img	wall;
	t_img	door;

	t_img	minimap;
	int		mmap_size;
	int		mmap_pos;
	double	mmap_grid;
	double	mmap_pdot;
	t_color	map_opacity;

	void	*mlx;
	void	*win;

	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planx;
	double	plany;

	int		move_front;
	int		move_back;
	int		move_right;
	int		move_left;
	int		turn_left;
	int		turn_right;
	int		attack;

	t_ray	ray;

	t_img	spr;
	t_img	coin[5];
	t_color	time;
	double	spx;
	double	spy;
	double	buffer[WIDTH];
}t_game;

typedef struct s_move
{
	double	diffx;
	double	diffy;
	double	collx;
	double	colly;
	double	leftx;
	double	lefty;
	double	rightx;
	double	righty;
}t_move;

void	print_error(enum e_error num);
void	resource_error(enum e_error num);
void	map_error(enum e_error num);

char	*get_line(int const fd);
int		not_contain_nl(char const *str);
char	*merge(char *const s1, char const *const s2);
char	*extract(char const *const str);
void	organize(char *const str);

void	init_window(void *mlx, void *win, t_img *img, t_rsrc *rsrc);
void	set_position(t_game *game, char **map);
void	apply_position(t_game *game, char **map, size_t y, size_t x);
void	set_png_images(t_game *game, t_img *ts, int i);
void	set_images(t_game *game, t_img *sc, t_img *ts);
void	load_window(t_game *game);
void	load_sprite(t_img *const img, void *const mlx, char *file);

/* parsing */
void	parse(t_map *const map, t_rsrc *const rsrc, \
			char const *const file_name);
int		open_file(char const *const file_name);

void	init_resource(t_rsrc *const rsrc, int const fd);
t_type	get_type(char const *str);
int		is_white(char const ch);
char	*set_texture(char const *str);
t_color	set_color(char const *str);
t_color	convert_color(char const *const str);
void	clear_resource(t_rsrc *const rsrc);

void	init_map(t_map *const map, int const fd);
size_t	get_start_point(char const *str);
void	get_map_size(t_map *const map, char const *str);
void	convert_map(t_map *const map, char const *str);
size_t	get_line_len(char const *str);
void	check_elements(t_map const map);
int		is_player(char const el);
int		check_player(char const el);
int		check_coin(char const el);
void	check_surround(t_map const map);
int		check_visited(t_map const map, size_t *y, size_t *x);
void	copy_map(t_map *const dst, t_map const org);
void	clear_map(t_map const map);
void	check_around(t_map const map, size_t const y, size_t const x);
int		check_up(t_map const map, size_t const y, size_t const x);
int		check_left(t_map const map, size_t const y, size_t const x);
int		check_down(t_map const map, size_t const y, size_t const x);
int		check_right(t_map const map, size_t const y, size_t const x);

/* rendering */
int		next_frame(t_game *game);
void	flush_wall(t_img *const wall);
void	render(t_game *const game);
void	set_back(t_img *const img, size_t const h_idx, t_color const col);
void	init_ray(t_game const game, t_ray *const ray, size_t w_idx);
void	init_nearvec(t_ray *const ray, t_game const game);

void	detech_wall(t_ray *const ray, t_map const map);

void	set_distance(t_game *const game, t_ray *const ray);

void	select_texture(t_ray *const ray);
void	set_texture_index(t_game const game, t_ray *const ray);
void	draw_texture(t_game *const game, t_ray const ray, \
					size_t const w_idx);

char	*get_addr(t_img const img, size_t const y, size_t const x);

void	draw_fist(t_game *const game, t_img const fist);
void	animation_fist(t_game *const game);

/* event */
int		exit_program(void);
int		key_press(int keycode, t_game *const game);
int		key_release(int keycode, t_game *const game);
void	door_handling(t_game *const game);

void	turn(t_game *const game, double const diff);
void	move_forward(t_game *const game);
void	move_back(t_game *const game);
void	move_right(t_game *const game);
void	move_left(t_game *const game);

int		draw_player(t_game *const game, int x, int y);
void	draw_minimap(t_game *const game, int x, int y);
int		get_offset(t_game const game, double pos, int n);
void	put_minimap(t_game *const game);
void	put_sprite(t_game *const game);
void	flush_image(t_img *image);

#endif
