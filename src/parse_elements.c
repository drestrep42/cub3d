/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:04:56 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/30 17:48:18 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	parse_each_element(t_texture *texture, t_floor *floor, \
					t_ceiling *ceiling, char **line)
{
	char	*word;
	int		i;

	i = 0;
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\t')
		i++;
	word = ft_substr(*line, 0, i);
	if (texture[NO].empty && ft_strncmp(word, "NO", 2) == 0)
		parse_textures(texture, NO, line, word);
	else if (texture[SO].empty && ft_strncmp(word, "SO", 2) == 0)
		parse_textures(texture, SO, line, word);
	else if (texture[EA].empty && ft_strncmp(word, "EA", 2) == 0)
		parse_textures(texture, EA, line, word);
	else if (texture[WE].empty && ft_strncmp(word, "WE", 2) == 0)
		parse_textures(texture, WE, line, word);
	else if (floor->empty && ft_strncmp(word, "F", 2) == 0)
		parse_floor_and_ceiling(floor, ceiling, line, 'F');
	else if (ceiling->empty && ft_strncmp(word, "C", 2) == 0)
		parse_floor_and_ceiling(floor, ceiling, line, 'C');
	else if (ft_strncmp(word, "\n", 1) != 0)
	{
		free(word);
		ft_exit(INVALID_TEXTURES);
	}
	free(word);
}

void	parse_space(char *line, char *trimmed, int fd)
{
	while (line)
	{
		trimmed = line;
		while (*trimmed == ' ')
			trimmed++;
		if (*trimmed != '\n' && !ft_isdigit(*trimmed))
		{
			free(line);
			ft_exit(INVALID_TEXTURES);
		}
		if (ft_isdigit(*trimmed))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	parse_elements(t_file *file, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	if (!line)
		ft_exit(EMPTY_MAP);
	while (line && (file->textures[NO].empty || file->textures[SO].empty \
			|| file->textures[EA].empty || file->textures[WE].empty \
			|| file->floor.empty || file->ceiling.empty))
	{
		trimmed = skip_spaces(line);
		free(line);
		line = trimmed;
		parse_each_element(file->textures, &file->floor, \
		&file->ceiling, &trimmed);
		free(line);
		line = get_next_line(fd);
	}
	parse_space(line, trimmed, fd);
}
