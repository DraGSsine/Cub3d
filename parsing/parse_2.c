/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:29:48 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/26 21:50:38 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	read_map(int fd, t_list **head, char *line)
{
	int	flag;

	while (line)
	{
		flag = check_map_line(line);
		if (flag == 1)
			ft_lstadd_back(head, ft_lstnew(line));
		free (line);
		if (flag == 0)
			return (0);
		line = get_next_line(fd);
	}
	return (1);
}

int	list_to_2darray(t_list *head, t_data *data)
{
	int		i;
	char	**map;

	i = 0;
	data->map_info.height_map = ft_lstsize(head);
	data->map_info.width_map = len_map(head);
	map = (char **)malloc(sizeof(char *) * (data->map_info.height_map + 1));
	if (!map)
		return (0);
	while (i < data->map_info.height_map && head)
	{
		map[i] = (char *)malloc(sizeof(char) * (data->map_info.width_map));
		if (!map[i])
			return (free_it_v2(map, i), 0);
		ft_memset(map[i], ' ', data->map_info.width_map);
		map[i][data->map_info.width_map - 1] = '\0';
		ft_strlcpy(map[i], head->str, data->map_info.width_map);
		head = head->next;
		i++;
	}
	map[i] = NULL;
	data->map_info.map = map;
	return (1);
}

int	plyr_pos(t_map_info mi, int r, int c)
{
	char	**map;

	map = mi.map;
	if (r == 0 || c == 0 || r == mi.width_map - 1 || c == mi.height_map - 1)
		return (1);
	if (map[c - 1][r] == ' ' || map[c + 1][r] == ' ' || \
	map[c][r - 1] == ' ' || map[c][r + 1] == ' ')
		return (1);
	return (0);
}

int	check_valid_map(t_data *data)
{
	int		c;
	int		r;

	c = -1;
	while (++c < data->map_info.height_map)
	{
		r = -1;
		while (++r < data->map_info.width_map)
		{
			if (ft_strchr("0NSEW", data->map_info.map[c][r])
			&& plyr_pos(data->map_info, r, c))
				return (0);
			else if (ft_strchr("NSEW", data->map_info.map[c][r]))
			{
				if (data->player.position_side)
					return (0);
				data->player.x = r;
				data->player.y = c;
				data->player.position_side = data->map_info.map[c][r];
			}
		}
	}
	if (!data->player.position_side)
		return (0);
	return (1);
}

void	second_parse(int fd, t_data *data, char *line)
{
	t_list	*head;

	head = NULL;
	if (!read_map(fd, &head, line) || !list_to_2darray(head, data))
	{
		free_map_info(data);
		ft_lstclear(&head);
		close(fd);
		error_and_exit("Error\nsomething wrong in the map.\n", -9);
	}
	close(fd);
	ft_lstclear(&head);
	trime(data);
	if (!check_valid_map(data))
	{
		free_map_info(data);
		error_and_exit("Error\nduplicate player or not found.\n", -9);
	}
}
