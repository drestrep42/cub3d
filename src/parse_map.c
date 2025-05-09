/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:01:11 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/09 22:07:05 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	check_for_errors(t_allocated *tobfreed, t_map *map, int *player, int y)
{
	free(tobfreed->var1);
	map->coord[y] = NULL;
	map->raw_lines[y] = NULL;
	if (*player < 1)
		tobfreed->mlx->error_msg = NO_PLAYER;
	if (tobfreed->mlx->error_msg)
	{
		free_gnl(tobfreed->fd);
		free_all(tobfreed->mlx, 1);
		ft_exit(tobfreed->mlx->error_msg);
	}
}

void	parse_all_lines(t_allocated	*tobfreed, t_map *map, int *player, int fd)
{
	int			x;
	int			y;

	y = 0;
	while (tobfreed->var1 && ft_strncmp(tobfreed->var1, "\n", 1) != 0)
	{
		parse_line(tobfreed->mlx, tobfreed->var1, player);
		map->raw_lines[y] = ft_strdup(tobfreed->var1);
		x = 0;
		map->coord[y] = ft_malloc((ft_strlen(tobfreed->var1) + 1) * \
		sizeof(t_points));
		while (tobfreed->var1[x])
		{
			map->coord[y][x].nbr = tobfreed->var1[x];
			map->coord[y][x].filled = false;
			map->coord[y]->x_nbrs = x;
			x++;
		}
		map->coord[y][x].nbr = '\0';
		free(tobfreed->var1);
		tobfreed->var1 = get_next_line(fd);
		y++;
	}
	check_for_errors(tobfreed, map, player, y);
}

void	parse_map(t_mlx *mlx, t_map *map, int fd, int size)
{
	t_allocated	tobfreed;
	static int	player;
	char		*line;

	map->raw_lines = ft_malloc((size + 1) * sizeof(char *));
	map->coord = ft_malloc((size + 1) * sizeof(t_points *));
	line = get_to_map(&tobfreed, fd);
	tobfreed.fd = fd;
	tobfreed.mlx = mlx;
	tobfreed.var1 = line;
	parse_all_lines(&tobfreed, map, &player, fd);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			free_gnl(fd);
			free_all(mlx, 0);
			ft_exit(DOUBLE_MAP);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}
