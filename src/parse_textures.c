/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:43:48 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/25 16:06:15 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

// void	parse_textures(t_texture *texture, int cardinal, 
// 						char **line, char *word, t_mlx *mlx)
// {
// 	char	*path;
// 	int		fd;
// 	xpm_t *xpm;
// 	mlx_image_t    *img;

// 	*line += ft_strlen(word);
// 	while (**line && (**line == ' ' || **line == '\t'))
// 		(*line)++;
// 	path = get_word(*line);
// 	*line += ft_strlen(path);
// 	while (**line && (**line == ' ' || **line == '\t'))
// 		(*line)++;
// 	if (**line != '\n')
// 		ft_exit(INVALID_TEXTURES);
// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 		ft_exit(strerror(errno));
// 	texture[cardinal].path = path;
// 	xpm = mlx_load_xpm42(path);
//     if (!xpm)
//     {
//         fprintf(stderr, "Error load xpm: No se pudo cargar la textura desde '%s'\n", path);
//         ft_exit("Error load xpm");
//     }
// 	img = mlx_texture_to_image(mlx, tex);
// 	// xpm = mlx_load_xpm42(texture[cardinal].path);
// 	if (!img)
// 	{
// 		printf("%d.-> '%s'\n",cardinal, texture[cardinal].path);
// 		ft_exit("Error load xpm");

// 	}
// 	texture[cardinal].img = img;
// 	// texture[cardinal].img = &xpm->texture;
// 	printf("asd asdasdasdasdasd'%s'\n", texture[cardinal].path);
// 	texture[cardinal].empty = false;
// }


void parse_textures(t_texture *texture, int cardinal, char **line, char *word)
// void parse_textures(t_texture *texture, int cardinal, char **line, char *word, void *mlx_ptr)
{
    char           *path;
    int             fd;
    // xpm_t          *xpm;
    // mlx_texture_t  *tex;
    // mlx_image_t    *img;

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
    {
        perror("Error al abrir el archivo de textura");
        ft_exit(strerror(errno));
    }
    close(fd);
    texture[cardinal].path = path;
    xpm_t *xpm = mlx_load_xpm42(path);
	if (!xpm)
		perror("xpm");
    // if (!&xpm->texture)
	// 	perror("&xpm->texture");   
    texture[cardinal].img = &xpm->texture;
	// mlx_image_t* img = mlx_texture_to_image(mlx_ptr, &xpm->texture);
//	printf("cardinal '%d'\n", cardinal);
	if (!texture[cardinal].img)
        perror("img"); 
//	printf("aaaaaaaaaaaa\n");
	// texture[cardinal].img = img;

    // xpm = mlx_load_xpm42(path);
    // if (!xpm)
    // {
    //     // fprintf(stderr, "Error load xpm: No se pudo cargar la textura desde '%s'\n", path);
    //     ft_exit("Error load xpm");
    // }
    // tex = &xpm->texture;
    // img = mlx_texture_to_image(mlx_ptr, tex);
    // if (!img)
    // {
    //     // fprintf(stderr, "Error: No se pudo convertir la textura a imagen para '%s'\n", path);
    //     ft_exit("Error al convertir la textura");
    // }
    // texture[cardinal].img = img;
    texture[cardinal].empty = false;
}
