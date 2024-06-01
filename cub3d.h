/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchen <youchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:36:46 by youchen           #+#    #+#             */
/*   Updated: 2024/06/01 10:48:55 by youchen          ###   ########.fr       */
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
	double	x;
	double	y;
	double	dir;
	double	fov;
	double	move_speed;
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
	double		wall_hit_x;
	double		wall_hit_y;
	double		found_hit;
}	t_ray_horz;

typedef struct s_ray_vert
{
	double		wall_hit_x;
	double		wall_hit_y;
	double		found_hit;
}	t_ray_vert;

typedef struct s_ray
{
	double			was_hit_vertical;
	double			wall_hit_x;
	double			wall_hit_y;
	double			distance;
	double			ray_angle;
}	t_ray;

typedef struct s_horz_info
{
	double	x_step;
	double	y_step;
	double	x_intercept;
	double	y_intercept;
	double	next_horz_touch_x;
	double	next_horz_touch_y;
	double	down;
	double	up;
	double	right;
	double	left;
}	t_horz_info;

typedef struct s_vert_info
{
	double	x_step;
	double	y_step;
	double	x_intercept;
	double	y_intercept;
	double	next_vert_touch_x;
	double	next_vert_touch_y;
	double	right;
	double	left;
	double	down;
	double	up;
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
double		normalize_angle(double angle);
double		distance_between_points(double x1, double y1, double x2, double y2);
int			keep_checking(t_data *data, int x, int y);
int			hit_vert(t_data *data, t_vert_info info);
int			hit_horz(t_data *data, t_horz_info info);
void		render_walls(t_data *data, t_ray *rays);
/// to be deleted
void	draw_ray_line(double x0, double y0, double x1, double y1, int color, t_data *data);
//
#endif
