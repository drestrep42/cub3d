/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:54:35 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/09 15:38:34 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*get_to_map(t_allocated *tobfreed, int fd)
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
	free_textures(tobfreed->mlx, 1);
	free_gnl(fd);
	ft_exit(INVALID_MAP);
	return (NULL);
}

int	get_map_size(t_allocated *tobfreed, int fd)
{
	char	*line;
	int		size;

	size = 0;
	line = get_to_map(tobfreed, fd);
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
