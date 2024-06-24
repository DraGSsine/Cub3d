/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:40:46 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/24 22:40:19 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void read_file(char *file, t_list **head)
{
    int fd;
    char *line;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        error_and_exit("Error\nCan't open file\n", -9);
    while ((line = get_next_line(fd)))
        ft_lstadd_back(head, ft_lstnew(line));
    close(fd);
    if (!head || !*head)
        error_and_exit("Error\nEmpty file\n", -9);
}
void trim_map(t_list **head)
{
    t_list *tmp;
    t_list *delete;
    t_list *prev;
    int i;
    delete = NULL;
    prev = NULL;
    tmp = *head;
    while (tmp)
    {
        i = 0;
        tmp->content = ft_strtrim(tmp->content, "\n");
        while(tmp->content[i] == ' ' || tmp->content[i] == '\n' || tmp->content[i] == '\t')
            i++;
        if (tmp->content[i] == '\0')
        {
            delete = tmp;
            if (tmp == *head)
                *head = tmp->next;
            else
                tmp = tmp->next;
            if (prev)
                prev->next = tmp;
            free(delete->content);
            free(delete);
            continue;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

int parce_color(char *line)
{
    int i;
    int color[3];
    int j;

    i = 0;
    j = 0;
    while ( j < 3)
    {
        color[j] = 0;
        if (!ft_isdigit(line[i]))
            error_and_exit("Error\nWrong Color\n", -9);
        while (ft_isdigit(line[i]))
        {
            color[j] = color[j] * 10 + line[i] - '0';
            i++;
        }
        if (line[i] != ',' && j < 2)
            error_and_exit("Error\nWrong Color\n", -9);
        i++;
        j++;
    }
    if (color[0] < 0 || color[0] > 255 || color[1] < 0 || color[1] > 255 || color[2] < 0 || color[2] > 255)
        error_and_exit("Error\nWrong Color\n", -9);
    return (color[0] << 16 | color[1] << 8 | color[2]);

}
int open_texture(t_data *data, char **diraction)
{
    int i;
    t_map_info *map;

    i = 0;
    map = &data->map_info;
    map->north = open(diraction[0], O_RDONLY);
    map->south = open(diraction[1], O_RDONLY);
    map->west = open(diraction[2], O_RDONLY);
    map->east = open(diraction[3], O_RDONLY);  
    if (map->north < 0 || map->south < 0 || map->west < 0 || map->east < 0)
        {
            close(map->north);
            close(map->south);
            close(map->west);
            close(map->east);
            while (i < 4)
                free(diraction[i++]);
            error_and_exit("Error\nCan't open textures\n", -9);
        }
    return (1);
}

size_t len_map(t_list *head)
{
    int len;
    int max_len;

    max_len = 0;
    while (head)
    {
        len = ft_strlen(head->content);
        if (len > max_len)
            max_len = len;
        head = head->next;
    }
    return (max_len);
}
void init_maps(int *map, size_t width)
{
    size_t i;

    i = 0;
    while (i < width)
    {
        map[i] = ' ';
        i++;
    }
}
int handle_map(t_list *head, t_data *data)
{
    int i;
    int **map_tmp;
    t_map_info *map;

    map = &data->map_info;
    map->height_map = ft_lstsize(head);
    map->width_map = len_map(head);
    map_tmp = (int **)malloc(sizeof(int *) * map->height_map);
    if (!map_tmp)
        return (0);
    i = 0;
    while (head)
    {
       int j = 0;
        map_tmp[i] = (int *)malloc(sizeof(int) * map->width_map);
        if (!map_tmp[i])
            return (0);
        init_maps(map_tmp[i], map->width_map);
        while (head->content[j])
        {
            if (head->content[j] == '1')
                map_tmp[i][j] = 1;
            else if (head->content[j] == ' ')
                map_tmp[i][j] = ' ';
            else if (head->content[j] == '0')
                map_tmp[i][j] = 0;
            else if (head->content[j] == '\t')
                map_tmp[i][j] = ' ';
            else if (head->content[j] == 'N' || head->content[j] == 'S' || head->content[j] == 'W' || head->content[j] == 'E')
           {
                map_tmp[i][j] = 3;
                data->player.x = j;
                data->player.y = i;
                data->player.position_side = head->content[j];
           }
            else
                return (0);
            j++;
        }
        i++;
        head = head->next;
    }
    map->map = map_tmp;
    return (1);
}

void parse_map(t_list *head, t_data *data)
{
    char *diraction[4];
    t_map_info *map;

    map = &data->map_info;
    while (head)
    {
       if (!ft_strncmp(head->content,"NO", 2) && ft_strlen(head->content) > 3)
            diraction[0] = ft_monstrdup(head->content + 3, ft_strlen(head->content) - 3);
        else if (!ft_strncmp(head->content,"SO", 2) && ft_strlen(head->content) > 3)
            diraction[1] = ft_monstrdup(head->content + 3, ft_strlen(head->content) - 3);
        else if (!ft_strncmp(head->content,"WE", 2) && ft_strlen(head->content) > 3)
            diraction[2] = ft_monstrdup(head->content + 3, ft_strlen(head->content) - 3);
        else if (!ft_strncmp(head->content,"EA", 2) && ft_strlen(head->content) > 3)
            diraction[3] = ft_monstrdup(head->content + 3, ft_strlen(head->content) - 3);
        else if (!ft_strncmp(head->content,"F", 1) && ft_strlen(head->content) > 2)
            map->floor = parce_color(head->content + 2);
        else if (!ft_strncmp(head->content,"C", 1) && ft_strlen(head->content) > 2)
            map->ceiling = parce_color(head->content + 2);
        else
            break;
        head = head->next;
    }
    open_texture(data, diraction);
    if (!handle_map(head, data))
    {
        ft_lstclear(&head);
        error_and_exit("Error\nCan't handle map\n", -9);
    }
}

void read_map (int ac, char **av, t_data *data)
{
    int len;
    t_list *head;

    if (ac != 2)
        error_and_exit("Error\nWorng Number of arguments", -9);
    len = ft_strlen(av[1]);
    if (len < 4 || ft_strcmp(&av[1][len - 4], ".cub"))
        error_and_exit("Error\nWorng Map\n", -9);
    
    head = NULL;
    read_file(av[1], &head);
    trim_map(&head);
    parse_map(head, data);
    ft_lstclear(&head);
}
