/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cub3d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:52:50 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/25 17:38:36 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_countstr(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] == c)
			ft_exit(INVALID_TEXTURES);
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			j++;
		i++;
	}
	if (j != 2)
		ft_exit(INVALID_TEXTURES);
	if (s[0] != c)
		j++;
	return (j);
}

char	*ft_string(const char *s, char c, size_t counter)
{
	char	*str;
	size_t	i;

	i = counter;
	while (s[i] != c && s[i] != '\0')
		i++;
	str = malloc(sizeof(char) * i + 1 - counter);
	if (!str || !s)
		return (NULL);
	i = 0;
	while (s[counter] != c && s[counter] != '\0')
	{
		str[i] = s[counter];
		i++;
		counter++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_cub3d(char const *s, char c)
{
	char	**new;
	size_t	sn;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	sn = ft_countstr(s, c);
	new = malloc((sn + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (j < sn)
	{
		while (s[i] == c && s[i])
			i++;
		new[j] = ft_string(s, c, i);
		while (s[i] != c && s[i])
			i++;
		j++;
	}
	new[j] = NULL;
	return (new);
}
