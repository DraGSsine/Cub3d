/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:10:47 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/26 16:32:44 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp( char *s1, char *s2, size_t n )
{
	size_t	k;

	k = 0;
	if ((!s1 && !s2) || n == 0)
		return (0);
	while (s1[k] && s2[k] && s1[k] == s2[k] && k < n - 1)
		k++;
	return ((unsigned char) s1[k] - (unsigned char) s2[k]);
}

char	*ft_monstrdup( char *s1, size_t size)
{
	char		*dup;
	size_t		i;

	if (!s1 || size == 0)
		return (NULL);
	i = 0;
	dup = (char *) malloc(size + 1 * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < size && s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
