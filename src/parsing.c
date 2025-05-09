/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:47:22 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/09 22:08:45 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	set_map_dimensions(t_map *map)
{
	int	x;
	int	y;
	int	max_x;

	y = 0;
	max_x = 0;
	while (map->coord[y])
	{
		x = 0;
		while (map->coord[y][x].nbr)
			x++;
		if (x > max_x)
			max_x = x;
		y++;
	}
	map->y_nbrs = y;
	map->x_nbrs = max_x;
}

void	flood_fill(t_mlx *mlx, t_map *map, int x, int y)
{
	if (y < 0 || y >= map->y_nbrs || x < 0 || x >= map->coord[y]->x_nbrs || \
		(map->coord[y][x].nbr != '0' && map->coord[y][x].nbr != '1' && \
		map->coord[y][x].nbr != 'N' && map->coord[y][x].nbr != 'S' && \
		map->coord[y][x].nbr != 'E' && map->coord[y][x].nbr != 'W'))
	{
		free_textures(mlx, 1);
		free_map(map);
		ft_exit(INVALID_MAP);
	}
	if (map->coord[y][x].filled == true || map->coord[y][x].nbr == '1')
		return ;
	map->coord[y][x].filled = true;
	flood_fill(mlx, map, x + 1, y);
	flood_fill(mlx, map, x - 1, y);
	flood_fill(mlx, map, x, y + 1);
	flood_fill(mlx, map, x, y - 1);
}

void	start_flood_fill(t_mlx *mlx, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->y_nbrs)
	{
		x = 0;
		while (map->coord[y][x].nbr)
		{
			if (map->coord[y][x].nbr == 'N' || map->coord[y][x].nbr == 'S' \
			|| map->coord[y][x].nbr == 'E' || map->coord[y][x].nbr == 'W' \
			|| map->coord[y][x].nbr == '0')
				flood_fill(mlx, map, x, y);
			x++;
		}
		y++;
	}
}

void	parsing(t_mlx	*mlx, char *argv)
{
	t_allocated	tobfreed;
	int			fd;
	int			size;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		ft_exit(USAGE_ERROR);
	mlx->error_msg = NULL;
	tobfreed.mlx = mlx;
	tobfreed.fd = fd;
	parse_elements(mlx, &mlx->file, fd);
	size = get_map_size(&tobfreed, fd) + 1;
	free_gnl(fd);
	close(fd);
	fd = open(argv, O_RDONLY);
	parse_map(mlx, &mlx->file.map, fd, size);
	set_map_dimensions(&mlx->file.map);
	start_flood_fill(mlx, &mlx->file.map);
}
