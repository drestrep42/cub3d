/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 19:56:22 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/04 19:13:48 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_readed(int fd, char *readed)
{
	char	*stash;
	int		buf;

	if (!readed)
		readed = ft_calloc(sizeof(char), 1);
	stash = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	buf = 1;
	while (!ft_strchr_gnl(stash, '\n') && buf != 0)
	{
		buf = read(fd, stash, BUFFER_SIZE);
		if (buf == -1)
		{
			free (readed);
			free (stash);
			return (NULL);
		}
		stash[buf] = '\0';
		readed = ft_strjoin_gnl(readed, stash);
	}
	free (stash);
	return (readed);
}

char	*ft_get_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*readed;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	readed = ft_readed(fd, readed);
	if (!readed)
		return (0);
	line = ft_get_line(readed);
	readed = ft_next_line_gnl(readed);
	return (line);
}
