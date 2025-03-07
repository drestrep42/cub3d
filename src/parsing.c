/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:47:22 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/07 17:40:17 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	transition_table(int i, int j)
{
	const int	status[][10] = {
//  \s, N, O, S, W, E, A, F, C, ^
	{0, 1, 1, 1, 1, 1, 1, 3, 3, 5}, // 0 Empty fd
	{5, 5, 4, 5, 5, 5, 5, 5, 5, 5},	// 1 Cardinal point
	{},	// 2 Path
	{}, // 3 Floor or color
	{}, // 4 Space between words
	{}, // 5 Invalid fd
	};
	return (status[i][j]);
}

void	skip_spaces(char *line)
{
	while (line && *line == ' ')
		line++;
}

void	validate_var(t_texture *texture, \
t_floor *floor, t_ceiling *ceiling, char *var)
{
	if (texture[NO].empty && ft_strncmp(var, "NO", 3) == 0)
		texture[NO].empty = false;
	else if (texture[SO].empty && ft_strncmp(var, "SO", 3) == 0)
		texture[SO].empty = false;
	else if (texture[EA].empty && ft_strncmp(var, "EA", 3) == 0)
		texture[EA].empty = false;
	else if (texture[WE].empty && ft_strncmp(var, "WE", 3) == 0)
		texture[WE].empty = false;
	else if (floor->empty && ft_strncmp(var, "F", 2) == 0)
		floor->empty = false;
	else if (ceiling->empty && ft_strncmp(var, "C", 2) == 0)
		ceiling->empty = false;
	else
	{
		free(var);
		ft_exit(INVALID_MAP);
	}
}

char	*get_word(char *line)
{
	int	i;

	i = 0;
	while (line && line[i] != ' ')
		i++;
	return (ft_substr(line, 0, i));
}

void	file_init(t_file *file)
{
	file->textures[NO] = malloc(sizeof(file->textures));
	file->textures[SO] = malloc(sizeof(file->textures));
	file->textures[EA] = malloc(sizeof(file->textures));
	file->textures[WE] = malloc(sizeof(file->textures));
	file->textures[NO]->empty = true;
	file->textures[SO]->empty = true;
	file->textures[EA]->empty = true;
	file->textures[WE]->empty = true;
	file->ceiling.empty = true;
	file->floor.empty = true;
}

void	parsing(t_file *file, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		ft_exit(EMPTY_MAP);
	file_init(file);
	while (line && (file->textures[NO]->empty || file->textures[SO]->empty ||\
			file->textures[EA]->empty || file->textures[WE]->empty || \
			file->floor.empty || file->ceiling.empty))
	{
		skip_spaces(line);
		validate_var(*file->textures, &file->floor, \
		&file->ceiling, get_word(line));
		free(line);
		line = get_next_line(fd);
	}
}
