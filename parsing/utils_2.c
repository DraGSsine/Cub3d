/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:04:05 by ymomen            #+#    #+#             */
/*   Updated: 2024/07/01 19:03:34 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	free_map_info(t_data *data)
{
	t_map_info	*map;

	map = &data->map_info;
	if (map->north_txt)
		free(map->north_txt);
	if (map->south_txt)
		free(map->south_txt);
	if (map->west_txt)
		free(map->west_txt);
	if (map->east_txt)
		free(map->east_txt);
	if (map->map)
		free_it_v2(map->map, map->height_map);
}

void	free_it_v2(char **s, int i)
{
	while (i-- && s[i])
		free(s[i]);
	free(s);
}
