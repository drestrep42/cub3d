/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:01:11 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/08 16:55:17 by drestrep         ###   ########.fr       */
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
	size++;
	free(line);
	return (size);
}

void	parse_line(t_mlx *mlx, char *line, int *player)
{
	while (line && *line != '\0')
	{
		while (*line == ' ')
		{
			line++;
			if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
				mlx->error_msg = OUT_OF_BOUNDS;
		}
		if (*line == '\n')
			break ;
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			(*player)++;
		if (*line != '0' && *line != '1' && \
			*line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			{
				free_textures(mlx, 1);
				mlx->error_msg = INVALID_MAP;
			}
		line++;
	}
	if (*player > 1)
		mlx->error_msg = INVALID_MAP;
}

void	parse_all_lines(t_mlx *mlx, t_map *map, char *line, int *player, int fd)
{
	int			x;
	int			y;

	y = 0;
	while (line && ft_strncmp(line, "\n", 1) != 0)
	{
		parse_line(mlx, line, player);
		map->raw_lines[y] = ft_strdup(line);
		x = 0;
		map->coord[y] = ft_malloc((ft_strlen(line) + 1) * sizeof(t_points));
		while (line[x])
		{
			map->coord[y][x].nbr = line[x];
			map->coord[y][x].filled = false;
			map->coord[y]->x_nbrs = x;
			x++;
		}
		map->coord[y][x].nbr = '\0';
		free(line);
		line = get_next_line(fd);
		y++;
	}
	free(line);
	map->coord[y] = NULL;
	map->raw_lines[y] = NULL;
	if (*player < 1)
		mlx->error_msg = NO_PLAYER;
	if (mlx->error_msg)
	{
		free_all(mlx, 0);
		ft_exit(mlx->error_msg);
	}
}

void	parse_map(t_mlx *mlx, t_map *map, int fd, int size)
{
	static int	player;
	char		*line;

	map->raw_lines = ft_malloc((size + 1) * sizeof(char *));
	map->coord = ft_malloc((size + 1) * sizeof(t_points *));
	line = get_to_map(fd);
	parse_all_lines(mlx, map, line, &player, fd);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			free_all(mlx, 0);
			ft_exit(INVALID_MAP);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}
