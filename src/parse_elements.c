/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:04:56 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/21 21:32:47 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	parse_each_element(t_texture *texture, t_floor *floor, \/
// 					t_ceiling *ceiling, char **line)
// {
// 	char	*word;
// 	int		i;

// 	i = 0;
// 	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\t')
// 		i++;
// 	word = ft_substr(*line, 0, i);
// 	printf("word: '%s', empty: %d\n", word, texture[NO].empty);

// 	if (texture[NO].empty && ft_strncmp(word, "NO", 2) == 0)
// 		parse_textures(texture, NO, line, word);
// 	else if (texture[SO].empty && ft_strncmp(word, "SO", 2) == 0)
// 		parse_textures(texture, SO, line, word);
// 	else if (texture[EA].empty && ft_strncmp(word, "EA", 2) == 0)
// 		parse_textures(texture, EA, line, word);
// 	else if (texture[WE].empty && ft_strncmp(word, "WE", 2) == 0)
// 		parse_textures(texture, WE, line, word);
// 	else if (floor->empty && ft_strncmp(word, "F", 2) == 0)
// 		parse_floor_and_ceiling(floor, ceiling, line, 'F');
// 	else if (ceiling->empty && ft_strncmp(word, "C", 2) == 0)
// 		parse_floor_and_ceiling(floor, ceiling, line, 'C');
// 	else if (ft_strncmp(word, "\n", 1) != 0)
// 	{
// 		free(word);
// 		printf("bbbbb\n");
// 		ft_exit(INVALID_TEXTURES);
// 	}
// 	free(word);
// }

// void	parse_each_element(t_texture *texture, t_floor *floor, \/
// 	t_ceiling *ceiling, char **line)
// {
// 	char	*word;
// 	int		i;

// 	i = 0;
// 	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\t')
// 		i++;
// 	word = ft_substr(*line, 0, i);
// 	printf("word: '%s'\n", word);

// 	if (ft_strcmp(word, "NO") == 0)
// 		{
// 		if (!texture[NO].empty)
// 			ft_exit(DUPLICATED_TEXTURE);
// 		parse_textures(texture, NO, line, word);
// 	}
// 	else if (ft_strcmp(word, "SO") == 0)
// 	{
// 		if (!texture[SO].empty)
// 			ft_exit(DUPLICATED_TEXTURE);
// 		parse_textures(texture, SO, line, word);
// 	}
// 	else if (ft_strcmp(word, "EA") == 0)
// 	{
// 		if (!texture[EA].empty)
// 			ft_exit(DUPLICATED_TEXTURE);
// 		parse_textures(texture, EA, line, word);
// 	}
// 	else if (ft_strcmp(word, "WE") == 0)
// 	{
// 		if (!texture[WE].empty)
// 			ft_exit(DUPLICATED_TEXTURE);
// 		parse_textures(texture, WE, line, word);
// 	}
// 	else if (ft_strcmp(word, "F") == 0)
// 	{
// 		if (!floor->empty)
// 			ft_exit(DUPLICATED_TEXTURE);
// 		parse_floor_and_ceiling(floor, ceiling, line, 'F');
// 	}
// 	else if (ft_strcmp(word, "C") == 0)
// 	{
// 		if (!ceiling->empty)
// 			ft_exit(DUPLICATED_TEXTURE);
// 		parse_floor_and_ceiling(floor, ceiling, line, 'C');
// 	}
// 	else if (ft_strcmp(word, "\n") != 0 && word[0] != '\0')
// 	{
// 		free(word);
// 		ft_exit(INVALID_TEXTURES);
// 	}
// 	free(word);
// }

void parse_each_element(t_texture *texture, t_floor *floor, t_ceiling *ceiling, char **line, void *mlx_ptr)
{
	char *word;
	int   i = 0;

	// Extraemos la palabra clave (NO, SO, EA, WE, F, C, etc.)
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '\t')
		i++;
	word = ft_substr(*line, 0, i);

	if (ft_strcmp(word, "NO") == 0)
	{
		if (!texture[NO].empty) ft_exit(DUPLICATED_TEXTURE);
			parse_textures(texture, NO, line, word, mlx_ptr);
	}
	else if (ft_strcmp(word, "SO") == 0)
	{
		if (!texture[SO].empty) ft_exit(DUPLICATED_TEXTURE);
			parse_textures(texture, SO, line, word, mlx_ptr);
	}
	else if (ft_strcmp(word, "EA") == 0)
	{
		if (!texture[EA].empty) ft_exit(DUPLICATED_TEXTURE);
			parse_textures(texture, EA, line, word, mlx_ptr);
	}
	else if (ft_strcmp(word, "WE") == 0)
	{
		if (!texture[WE].empty) ft_exit(DUPLICATED_TEXTURE);
			parse_textures(texture, WE, line, word, mlx_ptr);
	}
	else if (ft_strcmp(word, "F") == 0)
	{
		if (!floor->empty) ft_exit(DUPLICATED_TEXTURE);
			parse_floor_and_ceiling(floor, ceiling, line, 'F');
	}
	else if (ft_strcmp(word, "C") == 0)
	{
		if (!ceiling->empty) ft_exit(DUPLICATED_TEXTURE);
			parse_floor_and_ceiling(floor, ceiling, line, 'C');
	}
	else if (ft_strcmp(word, "\n") != 0 && word[0] != '\0')
	{
		free(word);
		ft_exit(INVALID_TEXTURES);
	}

	free(word);
}

// void	parse_elements(t_file *file, int fd)
// {
// 	char	*line;
// 	char	*trimmed;

// 	line = get_next_line(fd);
// 	if (!line)
// 		ft_exit(EMPTY_MAP);
// 	while (line && (file->textures[NO].empty || file->textures[SO].empty || \/
// 			file->textures[EA].empty || file->textures[WE].empty || \/
// 			file->floor.empty || file->ceiling.empty))
// 	{
// 		trimmed = skip_spaces(line);
// 		free(line);
// 		line = trimmed;
// 		parse_each_element(file->textures, &file->floor, \/
// 		&file->ceiling, &trimmed);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// }

void parse_elements(t_file *file, int fd, void *mlx_ptr)
{
    char *line    = get_next_line(fd);
    char *trimmed;

    if (!line)
        ft_exit(EMPTY_MAP);

    // Mientras queden elementos por leer...
    while (line &&
           (file->textures[NO].empty   ||
            file->textures[SO].empty   ||
            file->textures[EA].empty   ||
            file->textures[WE].empty   ||
            file->floor.empty          ||
            file->ceiling.empty))
    {
        // Eliminamos espacios iniciales
        trimmed = skip_spaces(line);
        free(line);
        line = trimmed;

        // Parseamos cada elemento, dándole el mlx_ptr
        parse_each_element(file->textures,
                           &file->floor,
                           &file->ceiling,
                           &trimmed,
                           mlx_ptr);

        free(line);
        line = get_next_line(fd);
    }
    free(line);
}