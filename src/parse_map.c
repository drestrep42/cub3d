/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:01:11 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/25 16:42:22 by drestrep         ###   ########.fr       */
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
	while (line && *line != '\0')
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
	char		*line;
	int			x;
	int			y;

	y = 0;
	line = get_to_map(fd);
	map->coord = ft_malloc((size + 1) * sizeof(t_points *));
	while (line && ft_strncmp(line, "\n", 1) != 0)
	{
		x = -1;
		parse_line(line, &player);
		map->coord[y] = ft_malloc((ft_strlen(line) + 1) * sizeof(t_points));
		while (line[++x])
		{
			map->coord[y][x].nbr = line[x];
			map->coord[y]->x_nbrs = x;
		}
		map->coord[y][x].nbr = '\0';
		free(line);
		line = get_next_line(fd);
		y++;
	}
	while (line)
	{
		if (line[0] != '\n')
			ft_exit(INVALID_MAP);
		free(line);
		line = get_next_line(fd);
	}
	map->coord[y] = NULL;
	free(line);
}
