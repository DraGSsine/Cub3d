/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:10:47 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/22 20:32:44 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_strlen(char *s)
{
    int i;
    i = 0;
    while (s && s[i])
        i++;
    return (i);
}
void	error_and_exit(char *s, int exite)
{
	if (exite == -9)
	{
		write(2, s, ft_strlen(s));
		exit (1);
	}
	perror(s);
	if (exite != 0)
		exit(exite);
}
int ft_strcmp(char *s1, char *s2)
{
    int i;
    i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}