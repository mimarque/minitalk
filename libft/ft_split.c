/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimarque <mimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:43:20 by mimarque          #+#    #+#             */
/*   Updated: 2021/11/24 17:26:48 by mimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**delete(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static int	getnextc(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		end;
	int		j;

	if (!s)
		return (NULL);
	arr = ft_calloc((count(s, c) + 1), sizeof(arr));
	if (!arr)
		return (NULL);
	j = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			end = getnextc(s, c);
			arr[j] = ft_substr(s, 0, end);
			if (!arr[j++])
				return (delete(arr));
			s += end;
		}
	}
	return (arr);
}
