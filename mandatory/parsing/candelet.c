/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   candelet.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:29:41 by ymomen            #+#    #+#             */
/*   Updated: 2024/07/05 22:00:09 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_texture(t_map_info *map, t_data *data)
{
	int	i;

	i = 0;
	printf("player info\n");
	printf("x: %f\n", data->player.x);
	printf("y: %f\n", data->player.y);
	printf("fov: %f\n", data->player.fov);
	printf("move_speed: %f\n", data->player.move_speed);
	printf("rotation_speed: %f\n", data->player.rotation_speed);
	printf("rotation_angle: %f\n", data->player.rotation_angle);
	printf("position_side: %d\n", data->player.position_side);
	printf("valid map\n");
	printf("NO: %s\n", map->north_txt);
	printf("SO: %s\n", map->south_txt);
	printf("WE: %s\n", map->west_txt);
	printf("EA: %s\n", map->east_txt);
	printf("F: %d\n", map->floor_clr);
	printf("C: %d\n", map->ceiling_clr);
	while (map->map && map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

// typedef struct s_img
// {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_m_pixel;
// 	int		line_length;
// 	int		line_width;
// 	int		line_heigth;
// 	int		size_len;
// 	int		endian;
// }	t_img;
// int	handle_map(t_list *hd, t_data *data)
// {
// 	int		i;
// 	int		j;
// 	char	**map;

// 	data->map_info.height_map = ft_lstsize(hd);
// 	data->map_info.width_map = len_map(hd);
// 	map = (char **)malloc(sizeof(char *) * (data->map_info.height_map + 1));
// 	if (!map)
// 		return (0);
// 	i = 0;
// 	while (hd)
// 	{
// 		map[i] = ft_monstrdup(hd->str, data->map_info.width_map);
// 		j = 0;
// 		while (hd->str && hd->str[j])
// 		{
// 			if (hd->str[j] != '0' && hd->str[j] != '1' && hd->str[j] != 'N' && hd->str[j] != 'S' && hd->str[j] != 'W' && hd->str[j] != 'E' && hd->str[j] != ' ' && hd->str[j] != '\t')
// 				return (0);
// 			if (hd->str[j] == 'N' || hd->str[j] == 'S' || hd->str[j] == 'W' || hd->str[j] == 'E')
// 			{
// 				data->player.x = j;
// 				data->player.y = i;
// 				data->player.dir = hd->str[j];
// 				map[i][j] = hd->str[j];
// 			}
// 			j++;
// 		}
// 		hd = hd->next;
// 		i++;
// 	}
// 	map[i] = NULL;
// 	data->map_info.map = map;
// 	return (1);
// }

// int	parse_map(t_list *hd, t_data *data)
// {
// 	char	*diraction[4];
	
// 	while (hd)
// 	{
// 		while (*(hd->str) == ' ')
// 			(hd->str)++;
// 		if (!ft_strncmp(hd->str, "NO", 2) && ft_strlen(hd->str) > 3)
// 			diraction[0] = ft_monstrdup(hd->str + 3, ft_strlen(hd->str) - 3);
// 		else if (!ft_strncmp(hd->str, "SO", 2) && ft_strlen(hd->str) > 3)
// 			diraction[1] = ft_monstrdup(hd->str + 3, ft_strlen(hd->str) - 3);
// 		else if (!ft_strncmp(hd->str, "WE", 2) && ft_strlen(hd->str) > 3)
// 			diraction[2] = ft_monstrdup(hd->str + 3, ft_strlen(hd->str) - 3);
// 		else if (!ft_strncmp(hd->str, "EA", 2) && ft_strlen(hd->str) > 3)
// 			diraction[3] = ft_monstrdup(hd->str + 3, ft_strlen(hd->str) - 3);
// 		else if (!ft_strncmp(hd->str, "F", 1) && ft_strlen(hd->str) > 2)
// 			data->map_info.floor_clr = parce_color(hd->str + 1);
// 		else if (!ft_strncmp(hd->str, "C", 1) && ft_strlen(hd->str) > 2)
// 			data->map_info.ceiling_clr = parce_color(hd->str + 1);
// 		else
// 			break ;
// 		hd = hd->next;
// 	}
// 	if (!open_texture(data, diraction) || !handle_map(hd, data))
// 		return (0);
// 	return (1);
// }