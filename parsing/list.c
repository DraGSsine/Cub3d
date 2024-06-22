/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:42:01 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/22 20:43:18 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_list	*ft_lstnew(char *content)
{
    t_list	*new;

    new = (t_list *)malloc(sizeof(t_list));
    if (!new)
        return (NULL);
    new->content = content;
    new->next = NULL;
    return (new);
}
void    ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list	*last;

    if (!*lst)
    {
        *lst = new;
        return ;
    }
    last = *lst;
    while (last->next)
        last = last->next;
    last->next = new;
}
void    ft_lstclear(t_list **lst)
{
    t_list	*tmp;

    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->content);
        free(*lst);
        *lst = tmp;
    }
}
