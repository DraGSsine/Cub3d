/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:51:47 by ymomen            #+#    #+#             */
/*   Updated: 2024/06/25 19:52:09 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*check(void)
{
	char	*newstr;

	newstr = (char *)malloc(1 * sizeof(char));
	if (!newstr)
		return (NULL);
	newstr[0] = '\0';
	return (newstr);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	lenstr;
	char	*newstr;

	if (!s1)
		return (NULL);
	if (ft_strlen(s1) == 0)
	{
		return (check());
	}
	if (ft_strlen(set) == 0 || !set)
		return (ft_strdup(s1));
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
	return (newstr);
}
