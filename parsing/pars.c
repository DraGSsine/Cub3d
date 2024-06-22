/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:40:46 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/22 20:54:17 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void read_file(char *file, t_list **head)
{
    int fd;
    char *line;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        error_and_exit("Error\nCan't open file", -9);
    while ((line = get_next_line(fd)))
    {
        ft_lstadd_back(head, ft_lstnew(line));
    }
    close(fd);
}
void parse_map(t_list *head)
{
    t_list *tmp;
    int i;

    i = 0;
    tmp = head;
    while (tmp)
    {
        printf("%s\n", tmp->content);
        tmp = tmp->next;
    }
}

void read_map (int ac, char **av)
{
    int len;
    t_list *head;

    if (ac != 2)
        error_and_exit("Error\nWorng Number of arguments", -9);
    len = ft_strlen(av[1]);
    if (len < 4 || ft_strcmp(&av[1][len - 4], ".cub"))
        error_and_exit("Error\nWorng Map", -9);

    head = NULL;
    read_file(av[1], &head);
    parse_map(head);
    ft_lstclear(&head);  
}