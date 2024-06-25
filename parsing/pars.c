/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:40:46 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/25 10:02:45 by ymomen           ###   ########.fr       */
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
    t_map_info *map = &data->map_info;

    i = 0;
    map->north_txt = open(diraction[0], O_RDONLY);
    map->south_txt = open(diraction[1], O_RDONLY);
    map->west_txt = open(diraction[2], O_RDONLY);
    map->east_txt = open(diraction[3], O_RDONLY);  
    if (map->north_txt < 0 || map->south_txt < 0 || map->west_txt < 0 || map->east_txt < 0)
        {
            close(map->north_txt);
            close(map->south_txt);
            close(map->west_txt);
            close(map->east_txt);
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
int handle_map(t_list *head, t_data *data)
{
    int i;
    int j;
    char **map;

    data->map_info.height_map = ft_lstsize(head);
    data->map_info.width_map = len_map(head);
    map = (char **)malloc(sizeof(char *) * (data->map_info.height_map + 1));
    if (!map)
        return (0);
    i = 0;
    while (head)
    {
        map[i] = ft_monstrdup(head->content, data->map_info.width_map);
        j = 0;    
        while(head->content[j])
        {
            if (head->content[j] != '0' && head->content[j] != '1' && head->content[j] != 'N' && head->content[j] != 'S' && head->content[j] != 'W' && head->content[j] != 'E' && head->content[j] != ' ' && head->content[j] != '\t')
                error_and_exit("Error\nWrong Map\n", -9);
            if (head->content[j] == 'N' || head->content[j] == 'S' || head->content[j] == 'W' || head->content[j] == 'E')
            {
                data->player.x = j;
                data->player.y = i;
                data->player.rotation_angle = (head->content[j] == 'N') ? 270 * (M_PI / 180) : (head->content[j] == 'S') ? 90 * (M_PI / 180) : (head->content[j] == 'W') ? 180 * (M_PI / 180) : 0;
            }
                
            map[i][j] = head->content[j];
            j++;
        }
        head = head->next;
        i++;
    }
    map[i] = NULL;
    data->map_info.map = map;
    return (1);
}

void parse_map(t_list *head, t_data *data)
{
    char *diraction[4];
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
            data->map_info.floor_clr = parce_color(head->content + 2);
        else if (!ft_strncmp(head->content,"C", 1) && ft_strlen(head->content) > 2)
            data->map_info.ceiling_clr = parce_color(head->content + 2);
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
void print_texture(t_map_info *map)
{
    int i;
    i = 0;

    
    printf("NO: %d\n", map->north_txt);
    printf("SO: %d\n", map->south_txt);
    printf("WE: %d\n", map->west_txt);
    printf("EA: %d\n", map->east_txt);
    printf("F: %d\n", map->floor_clr);
    printf("C: %d\n", map->ceiling_clr);
    while (map->map[i])
    {
        printf("%s\n", map->map[i]);
        i++;
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
    print_texture(&data->map_info);
    ft_lstclear(&head);
}
