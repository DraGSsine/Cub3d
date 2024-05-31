/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:36:46 by youchen           #+#    #+#             */
/*   Updated: 2024/05/31 13:56:00 by youchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# define MAP_WIDTH 15
# define MAP_HEIGHT 11
# define TILE_SIZE 64

typedef struct s_map_info
{
	int		map[MAP_HEIGHT][MAP_WIDTH];
	int		window_width;
	int		window_height;
	int		rays_num;
}	t_map_info;

typedef struct s_player
{
	float	x;
	float	y;
	float	dir;
	float	fov;
	int		move_speed;
	double	rotation_speed;
	double	rotation_angle;
}	t_player;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	t_map_info	map_info;
	t_player	player;
}	t_data;

typedef struct s_ray_horz
{
	int		was_hit_horizontal;
	int		wall_hit_x;
	int		wall_hit_y;
	int		found_hit;
}	t_ray_horz;

typedef struct s_ray_vert
{
	int		was_hit_vertical;
	int		wall_hit_x;
	int		wall_hit_y;
	int		found_hit;
}	t_ray_vert;

typedef struct s_ray
{
	int			was_hit_vertical;
	int			wall_hit_x;
	int			wall_hit_y;
	int			distance;
}	t_ray;

typedef struct s_horz_info
{
	int	x_step;
	int	y_step;
	int	x_intercept;
	int	y_intercept;
	int	next_horz_touch_x;
	int	next_horz_touch_y;
	int	down;
	int	up;
	int	right;
	int	left;
}	t_horz_info;

typedef struct s_vert_info
{
	int	x_step;
	int	y_step;
	int	x_intercept;
	int	y_intercept;
	int	next_vert_touch_x;
	int	next_vert_touch_y;
	int	right;
	int	left;
	int	down;
	int	up;
}	t_vert_info;

void		init_game(t_data *data);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			movement(int key, t_data *data);
int			hit_wall(t_data *data, int x, int y);
void		draw(t_data *data);
int			close_window(t_data *data);
void		cast_all_rays(t_data *data, t_ray *rays);
void		cast_ray(double ray_angle, t_data *data, t_ray *ray);
t_ray_horz	cast_horz_ray(double ray_angle, t_data *data);
t_ray_vert	cast_vert_ray(double ray_angle, t_data *data);
float		normalize_angle(double angle);
int			distance_between_points(int x1, int y1, int x2, int y2);
int			keep_checking(t_data *data, int x, int y);
int			hit_vert(t_data *data, t_vert_info info);
int			hit_horz(t_data *data, t_horz_info info);
void		render_walls(t_data *data, t_ray *rays);
/// to be deleted
void draw_ray_line(int xFrom, int yFrom, int xTo, int yTo,int color , t_data *data);
//
#endif
