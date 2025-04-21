/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:45:23 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/21 21:28:46 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>
#include <math.h>
# include "../libft/inc/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define USAGE_ERROR "Correct use: ./cub3d map_name.cub"
# define EMPTY_MAP "Map is empty"
# define INVALID_MAP "Invalid map"
# define INVALID_TEXTURES "Invalid textures"
# define INVALID_PLAYER "Only one player allowed"
# define OUT_OF_BOUNDS "Player out of bounds"
# define DUPLICATED_TEXTURE "Texture duplicate"

# define NO 0
# define SO 1
# define EA 2
# define WE 3

# define R 0
# define G 1
# define B 2

# define WIDTH 800
# define HEIGHT 800
#define mapHeight 8
#define mapWidth 13
#define screenWidth 640
#define screenHeight 480
#define MOVE_SPEED 0.1
#define ROT_SPEED  0.05
#define BLOCK  64
#define PI  3.14159265359


typedef struct s_points
{
	int			filled;
	char		nbr;
}				t_points;

typedef struct s_map
{
	t_points	**coord;
	int			x_nbrs;
	int			y_nbrs;
	char      **raw_lines;
}				t_map;

typedef struct s_texture
{
	char		*path;
	mlx_texture_t *img;
	xpm_t       *xpm;
	int            width;
	int            height;
	bool		empty;
}				t_texture;

typedef struct s_floor
{
	int			color[3];
	bool		empty;
}				t_floor;

typedef struct s_ceiling
{
	int			color[3];
	bool		empty;
}				t_ceiling;

typedef struct s_player
{
    double posX;
    double posY;
    // double dirX;
    // double dirY;
	double angle;
    double planeX;
    double planeY;

	bool left_rotate;
	bool right_rotate;
}               t_player;

typedef struct s_file
{
	t_map		map;
	t_floor		floor;
	t_ceiling	ceiling;
	t_texture	textures[4];

}				t_file;

typedef struct s_mlx
{
	t_file		file;
	void		*mlx_ptr;
	mlx_image_t	*img;
	int			width;
	int			height;
	t_player    player;
}				t_mlx;

// Init
/**
 * Initializes the t_mlx struct with a new window and image.
 * 
 * @param[out] mlx Pointer to the MLX instance to be initialized.
 */
void	cube_init(t_mlx *mlx);

/**
 * Initializes all values of the t_file struct passed as argument.
 * 
 * @param[out] file The t_file struct to initialize.
 */
void	file_init(t_file *file);

// Parsing
/**
 * Parses the given file and extracts necessary elements and map data.
 * 
 * @param[in, out] file Pointer to the t_file structure where parsed \
 * data will be stored.
 * @param[in] argv Path to the file to be parsed.
 */
// void	parsing(t_file *file, char *argv);
void	parsing(t_mlx	*mlx, char *argv);

/**
 * Parses the textures and color elements from the given file descriptor.
 * 
 * @param[in, out] file Pointer to the t_file structure where parsed \
 * elements will be stored.
 * @param[in] fd File descriptor of the map file being read.
 * 
 * @note If the map is empty, the function exits with an error.
 */
void parse_elements(t_file *file, int fd, void *mlx_ptr);

// void	parse_elements(t_file *file, int fd);
void	parse_floor_and_ceiling(t_floor *floor, t_ceiling *ceiling, \
								char **line, char element);
/**
 * Parses and stores a texture path for a given cardinal direction.
 * 
 * @param[in, out] texture Pointer to the texture array where the parsed path \
 * will be stored.
 * @param[in] cardinal Index representing the texture's cardinal direction.
 * @param[in, out] line Pointer to the current position in the input line; \
 * it is modified as parsing progresses.
 * @param[in] word Expected keyword identifying the texture.
 * 
 * @note If the texture file cannot be opened, the function exits with an error.
 */
void parse_textures(t_texture *texture, int cardinal, char **line, char *word, void *mlx_ptr);

// void	parse_textures(t_texture *texture, int cardinal, \/
						// char **line, char *word);

/**
 * Parses the map lines from the file and stores them in the map structure.
 * 
 * @param[in, out] map Pointer to the t_map structure where the parsed lines \
 * will be stored.
 * @param[in] fd File descriptor of the map file being read.
 * @param[in] size The number of lines in the map section.
 * 
 * @note If the function encounters a failure, it will exit with the \
 * corresponding message. 
 */
void	parse_map(t_map *map, int fd, int size);

/**
 * Determines the number of lines in the map section of the file.
 * 
 * @param[in] fd File descriptor of the map file being read.
 * 
 * @return The number of lines in the map section.
 */
int		get_map_size(int fd);

// Free
/**
 * Frees all allocated memory in the mlx struct.
 * 
 * @param[in, out] mlx Pointer to the MLX instance to be freed.
 * @note After calling this function, the freed pointers should not be accessed.
 */
void	free_all(t_mlx *mlx);

// Exit
/**
 * Prints the argument before exiting the program.
 * 
 * @param[in] message Message to be printed.
 */
void	*ft_exit(char *message);

// UTILS

char	**ft_split_cub3d(char const *s, char c);
int		check_spaces(char **ptr);
char	*skip_spaces(char *line);

#endif