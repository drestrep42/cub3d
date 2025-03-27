/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:01:11 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/27 14:26:47 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*get_to_map(int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = skip_spaces(line);
		if (ft_isdigit(*trimmed))
		{
			free(trimmed);
			return (line);
		}
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	return (ft_exit(INVALID_MAP));
}

int	get_map_size(int fd)
{
	char	*line;
	int		size;

	size = 0;
	line = get_to_map(fd);
	while (line && ft_strncmp(line, "\n", 1) != 0)
	{
		size++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (size);
}

void	parse_line(char *line, int *player)
{
	while (line)
	{
		while (*line == ' ')
		{
			line++;
			if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
				ft_exit(OUT_OF_BOUNDS);
		}
		if (*line == '\n')
			break ;
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			(*player)++;
		if (*line != '0' && *line != '1' && \
			*line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			ft_exit(INVALID_MAP);
		line++;
	}
	if (*player > 1)
		ft_exit(INVALID_PLAYER);
}

void	parse_map(t_map *map, int fd, int size)
{
	static int	player;
	char		**aux;
	char		*line;

	line = get_to_map(fd);
	map->points = malloc((size + 1) * sizeof(char *));
	if (!map->points)
		exit(1);
	aux = map->points;
	while (line && ft_strncmp(line, "\n", 1) != 0)
	{
		parse_line(line, &player);
		printf("%s", line);
		*aux = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		aux++;
	}
	*aux = NULL;
	free(line);
}
