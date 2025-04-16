/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:47:22 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/16 14:05:17 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	map_validator(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->coord[y])
	{
		x = 0;
		while (map->coord[y][x].nbr)
		{
			printf("%c", map->coord[y][x].nbr);
			x++;
		}
		y++;
	}
	printf("\n");
	/* while (map->points[y])
	{
		x = 0;
		while (map->coord[y][x].nbr)
		{
			if (map->coord[y][x].nbr == 0)
				
			x++;
		}
		y++;
	} */
}

void set_map_dimensions(t_map *map)
{
    int y = 0, max_x = 0, x;
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

void	parsing(t_file *file, char *argv)
{
	int		fd;
	int		size;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		ft_exit(USAGE_ERROR);
	parse_elements(file, fd);
	size = get_map_size(fd);
	close(fd);
	fd = open(argv, O_RDONLY);
	parse_map(&file->map, fd, size);
	set_map_dimensions(&file->map);
    printf("aaaaaaaaaaaaa map->y_nbrs: %d, map->x_nbrs: %d\n", file->map.y_nbrs, file->map.x_nbrs);
	map_validator(&file->map);
}
