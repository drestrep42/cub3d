/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 10:26:28 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:12:12 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (count == SIZE_MAX || size == SIZE_MAX)
		return (0);
	ptr = malloc(count * size);
	if (ptr == 0)
	{
		free (ptr);
		return (NULL);
	}
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

char	*ft_strjoin_gnl(char *readed, char *stash)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	j = 0;
	if (!readed || !stash)
		return (NULL);
	line = malloc(sizeof(char) * \
	((ft_strlen_gnl(readed) + ft_strlen_gnl(stash)) + 1));
	if (!line)
		return (NULL);
	while (readed[i])
	{
		line[i] = readed[i];
		i++;
	}
	while (stash[j])
		line[i++] = stash[j++];
	line[ft_strlen_gnl(readed) + ft_strlen_gnl(stash)] = '\0';
	free(readed);
	return (line);
}

int	ft_strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	while (*str != '\0')
	{
		str++;
		i++;
	}
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen_gnl(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_next_line_gnl(char *readed)
{
	char	*nl;
	int		i;
	int		j;

	i = 0;
	while (readed[i] != '\n' && readed[i])
		i++;
	if (!readed[i])
	{
		free(readed);
		return (NULL);
	}
	nl = malloc(sizeof(char) * (ft_strlen_gnl(readed) - i + 1));
	if (!nl)
		return (NULL);
	i++;
	j = 0;
	while (readed[i])
		nl[j++] = readed[i++];
	nl [j] = '\0';
	free(readed);
	return (nl);
}
