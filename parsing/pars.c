/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:40:46 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/23 23:11:11 by ymomen           ###   ########.fr       */
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
int open_texture(t_texture *texture, char **diraction)
{
    int i;

    i = 0;
    texture->north = open(diraction[0], O_RDONLY);
    texture->south = open(diraction[1], O_RDONLY);
    texture->west = open(diraction[2], O_RDONLY);
    texture->east = open(diraction[3], O_RDONLY);  
    if (texture->north < 0 || texture->south < 0 || texture->west < 0 || texture->east < 0)
        {
            close(texture->north);
            close(texture->south);
            close(texture->west);
            close(texture->east);
            while (i < 4)
                free(diraction[i++]);
            error_and_exit("Error\nCan't open textures\n", -9);
        }
    return (1);
} 
int handle_map(t_list *head, t_texture *texture)
{
    int i;
    int len;
    char **map;

    texture->height = ft_lstsize(head);
    texture->width = 0;
    map = (char **)malloc(sizeof(char *) * (texture->height + 1));
    if (!map)
        return (0);
    i = 0;
    while (head)
    {
        len = ft_strlen(head->content);
        if (len > 0)
        {
            map[i] = ft_monstrdup(head->content, len);
            if (!map[i])
                return (0);
            i++;
        }
        if (texture->width < len)
            texture->width = len;
        head = head->next;
    }
    map[i] = NULL;
    texture->map = map;
    return (1);
}

void parse_map(t_list *head, t_texture *texture)
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
            texture->floor = parce_color(head->content + 2);
        else if (!ft_strncmp(head->content,"C", 1) && ft_strlen(head->content) > 2)
            texture->ceiling = parce_color(head->content + 2);
        else
            break;
        head = head->next;
    }
    open_texture(texture, diraction);
    if (!handle_map(head, texture))
    {
        ft_lstclear(&head);
        error_and_exit("Error\nCan't handle map\n", -9);
    }
}
void print_texture(t_texture *texture)
{
    int i;
    i = 0;
    printf("NO: %d\n", texture->north);
    printf("SO: %d\n", texture->south);
    printf("WE: %d\n", texture->west);
    printf("EA: %d\n", texture->east);
    printf("F: %d\n", texture->floor);
    printf("C: %d\n", texture->ceiling);
    while (texture->map[i])
    {
        printf("%s\n", texture->map[i]);
        i++;
    }
}

t_texture read_map (int ac, char **av)
{
    int len;
    t_list *head;
    t_texture texture;

    if (ac != 2)
        error_and_exit("Error\nWorng Number of arguments", -9);
    len = ft_strlen(av[1]);
    if (len < 4 || ft_strcmp(&av[1][len - 4], ".cub"))
        error_and_exit("Error\nWorng Map\n", -9);
    
    head = NULL;
    read_file(av[1], &head);
    trim_map(&head);
    parse_map(head, &texture);
    print_texture(&texture);
    ft_lstclear(&head); 
    return (texture);
}
