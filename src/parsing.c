/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:47:22 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/25 15:56:44 by drestrep         ###   ########.fr       */
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

char *skip_spaces(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return (ft_strdup(line));
}

char	*get_word(char *line)
{
	char	*word;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n' \
	&& line[i] != ' ' && line[i] != '\t')
		i++;
	word = ft_substr(line, 0, i);
	return (word);
}

	/* if (!*line || (**line != ' ' && **line != '\t'))
	{
		printf("NOOOOOO\n");
		ft_exit(INVALID_TEXTURES);
	}
	if (!*line)
	{
		printf("ENTRAAA\n");
		ft_exit(INVALID_TEXTURES);
	} */

void	parse_rgb(char **rgb)
{
	int		nbr_of_elements;
	char	**aux;

	aux = rgb;
	nbr_of_elements = 0;
	while (*rgb)
	{
		while (**rgb)
		{	
			if (!ft_isdigit(**rgb) && **rgb != '\n')
				ft_exit(INVALID_TEXTURES);
			(*rgb)++;
		}
		nbr_of_elements++;
		printf("%s\n", *rgb++);
	}
	if (nbr_of_elements != 3)
		ft_exit(INVALID_TEXTURES);
	rgb = aux;
}

void	get_rgb(char **line, void *floor_or_ceiling, char element)
{
	t_floor		*floor;
	t_ceiling	*ceiling;
	char		**rgb;

	rgb = ft_split(*line, ',');
	//parse_rgb(rgb);
	if (element == 'F')
	{
		floor = (t_floor *)floor_or_ceiling;
		floor->color[R] = ft_atoi(rgb[R]);
		floor->color[G] = ft_atoi(rgb[G]);
		floor->color[B] = ft_atoi(rgb[B]);
	}
	else if (element == 'C')
	{
		ceiling = (t_ceiling *)floor_or_ceiling;
		ceiling->color[R] = ft_atoi(rgb[R]);
		ceiling->color[G] = ft_atoi(rgb[G]);
		ceiling->color[B] = ft_atoi(rgb[B]);
	}
	free(rgb[R]);
	free(rgb[G]);
	free(rgb[B]);
	free(rgb);
}

void	parse_floor_and_ceiling(t_floor *floor, t_ceiling *ceiling, \
								char **line, char element)
{
	(*line)++;
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
	if (element == 'F')
	{
		get_rgb(line, floor, 'F');
		(*floor).empty = false;
	}
	else if (element == 'C')
	{
		get_rgb(line, ceiling, 'C');
		(*ceiling).empty = false;
	}
}

void	parse_textures(t_texture *texture, int cardinal, \
						char **line, char *word)
{
	char	*path;
	int		fd;

	*line += ft_strlen(word);
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
	path = get_word(*line);
	*line += ft_strlen(path);
	while (**line && (**line == ' ' || **line == '\t'))
		(*line)++;
	if (**line != '\n')
		ft_exit(INVALID_TEXTURES);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(strerror(errno));
	texture[cardinal].path = path;
	texture[cardinal].empty = false;
}

void parse_elements(t_texture *texture, t_floor *floor, \
					t_ceiling *ceiling, char **line)
{
	char *word;
	int i;

	i = 0;
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\t')
		i++;
	word = ft_substr(*line, 0, i);
	if (texture[NO].empty && ft_strncmp(word, "NO", 3) == 0)
		parse_textures(texture, NO, line, word);
	else if (texture[SO].empty && ft_strncmp(word, "SO", 3) == 0)
		parse_textures(texture, SO, line, word);
	else if (texture[EA].empty && ft_strncmp(word, "EA", 3) == 0)
		parse_textures(texture, EA, line, word);
	else if (texture[WE].empty && ft_strncmp(word, "WE", 3) == 0)
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


void	file_init(t_file *file)
{
	file->textures[NO].empty = true;
	file->textures[SO].empty = true;
	file->textures[EA].empty = true;
	file->textures[WE].empty = true;
	file->ceiling.empty = true;
	file->floor.empty = true;
}

void	parsing(t_file *file, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	if (!line)
		ft_exit(EMPTY_MAP);
	file_init(file);
	while (line && (file->textures[NO].empty || file->textures[SO].empty ||\
			file->textures[EA].empty || file->textures[WE].empty || \
			file->floor.empty || file->ceiling.empty))
	{
		trimmed = skip_spaces(line);
		free(line);
		line = trimmed;
		parse_elements(file->textures, &file->floor, \
		&file->ceiling, &trimmed);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}
