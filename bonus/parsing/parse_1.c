/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:40:46 by ymomen            #+#    #+#             */
/*   Updated: 2024/07/10 18:01:35 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_values(t_data *data)
{
	data->map_info.window_width = WIN_WIDTH;
	data->map_info.window_height = WIN_HEIGHT;
	data->map_info.rays_num = WIN_WIDTH;
	data->map_info.north_txt = NULL;
	data->map_info.south_txt = NULL;
	data->map_info.west_txt = NULL;
	data->map_info.east_txt = NULL;
	data->map_info.floor_clr = 0;
	data->map_info.ceiling_clr = 0;
	data->map_info.map = NULL;
	data->player.x = -1;
	data->player.y = -1;
	data->player.position_side = 0;
	data->rand = true;
}

char	*identifier_parse(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	str = ft_monstrdup(&line[i], ft_strlen(&line[i]) - 1);
	return (str);
}

int	check_txure(t_data *data, char *idx)
{
	t_map_info	*mi;

	mi = &data->map_info;
	while (*idx == ' ' || *idx == '\t')
		idx++;
	if (!ft_strncmp(idx, "NO ", 3) && ft_strlen(idx) > 4 && !mi->north_txt)
		mi->north_txt = identifier_parse(idx + 2);
	else if (!ft_strncmp(idx, "SO ", 3) && ft_strlen(idx) > 4 && !mi->south_txt)
		mi->south_txt = identifier_parse(idx + 2);
	else if (!ft_strncmp(idx, "WE ", 3) && ft_strlen(idx) > 4 && !mi->west_txt)
		mi->west_txt = identifier_parse(idx + 2);
	else if (!ft_strncmp(idx, "EA ", 3) && ft_strlen(idx) > 4 && !mi->east_txt)
		mi->east_txt = identifier_parse(idx + 2);
	else if (!ft_strncmp(idx, "F ", 2) && ft_strlen(idx) > 3
		&& mi->floor_clr == 0)
		mi->floor_clr = parce_color(idx + 1);
	else if (!ft_strncmp(idx, "C ", 2) && ft_strlen(idx) > 3
		&& mi->ceiling_clr == 0)
		mi->ceiling_clr = parce_color(idx + 1);
	else if (ft_strcmp(idx, "\n"))
		return (0);
	return (1);
}

void	first_parse(int fd, t_data *data, char **line)
{
	char	*idx;

	*line = get_next_line(fd);
	while (line)
	{
		idx = *line;
		if (!check_txure(data, idx))
			break ;
		free(*line);
		*line = get_next_line(fd);
	}
	if (!data->map_info.north_txt || !data->map_info.south_txt \
	|| !data->map_info.east_txt || !data->map_info.west_txt || \
	data->map_info.floor_clr == 0 || data->map_info.ceiling_clr == 0)
	{
		free_map_info(data);
		error_and_exit("Error\nMissing textures or colors\n", -9);
	}
}

void	read_file_parse(int ac, char **av, t_data *data)
{
	int		len;
	int		fd;
	char	*last_line;

	if (ac != 2)
		error_and_exit("Error\nWorng Number of arguments", -9);
	init_values(data);
	len = ft_strlen(av[1]);
	if (len < 4 || ft_strcmp(&av[1][len - 4], ".cub"))
		error_and_exit("Error\nWorng Map\n", -9);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		error_and_exit("Error\nCan't open file\n", -9);
	first_parse(fd, data, &last_line);
	second_parse(fd, data, last_line);
	set_retation(data);
	
}
