/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:04:05 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/23 22:58:09 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strchr( char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *) s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	count;
	size_t	lens;

	count = 0;
	lens = 0;
	while (src[lens])
		lens++;
	if (dstsize == 0)
		return (lens);
	while (src[count] != '\0' && count + 1 < dstsize)
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (lens);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	size_t	lenstr;
	char	*newstr;

	if (!s1 || *s1 == '\0' || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	lenstr = end - start + 1;
	newstr = (char *)malloc((lenstr + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, &s1[start], lenstr + 1);
	free(s1);
	return (newstr);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
