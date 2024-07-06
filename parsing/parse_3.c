/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:48:34 by ymomen            #+#    #+#             */
/*   Updated: 2024/07/06 20:53:44 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	len_map(t_list *hd)
{
	int	len;
	int	max_len;

	max_len = 0;
	while (hd)
	{
		len = ft_strlen(hd->str);
		if (len > max_len)
			max_len = len;
		hd = hd->next;
	}
	return (max_len);
}

int	valid_chars(char c)
{
	if (c == '1' || c == '0')
		return (1);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

int	parce_color(char *line)
{
	int	i;
	int	color[3];
	int	j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		color[j] = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (!ft_isdigit(line[i]))
			return (-1);
		while (ft_isdigit(line[i]))
			color[j] = color[j] * 10 + line[i++] - '0';
		if ((line[i] == ',' && line[i + 1] == ',') || (line[i] == ',' && j > 1))
			return (-1);
		j++;
		i++;
	}
	if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255
		|| color[2] < 0 || color[2] > 255)
		return (-1);
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | 0x000000FF);
}

int	check_map_line(char *line)
{
	int	l;

	l = 0;
	while (line && line[l])
	{
		while (line[l] == ' ' || line[l] == '\t')
			l++;
		if (!valid_chars(line[l]) && line[l])
			return (0);
		if (!line[l])
			return (2);
		l++;
		while (line[l] == ' ' || line[l] == '\t' || line[l] == '\n')
			l++;
	}
	return (1);
}

void	trime(t_data *data)
{
	char	**map;
	int		r;
	int		c;

	map = data->map_info.map;
	c = 0;
	while (map[c])
	{
		r = 0;
		while (map[c][r])
		{
			if (map[c][r] == '\n')
			{
				map[c][r] = ' ';
				break ;
			}
			r++;
		}
		c++;
	}
	data->map_info.width_map--;
	data->map_info.map = map;
}
