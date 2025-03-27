/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:47:22 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/27 14:04:47 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
}
