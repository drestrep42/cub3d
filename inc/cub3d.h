/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:45:23 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/01 12:19:04 by drestrep         ###   ########.fr       */
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
#include <assert.h>
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
#define PLAYER_RADIUS  10

typedef struct s_points
{
	int			filled;
	int			x_nbrs;
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
	int			color[3];	double radius;

	bool		empty;
}				t_ceiling;

typedef struct s_player
{
    double pos_x;
    double pos_y;
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

typedef struct s_touch {
	double	nearest_x;
	double	nearest_y;
	double	dx;
	double	dy;
	double	px;
	double	py;
	int		min_x;
	int		max_x;
	int		min_y;
	int		max_y;
	int		y;
	int		x;
}				t_touch;

typedef struct s_ray {
    /* Camera & ray direction */
    double	pos_x;
	double	pos_y;
    double	raydir_x;
	double	raydir_y;

    /* DDA state */
    int mapX, mapY;
    int stepX, stepY;
    double sideDistX, sideDistY;
    double deltaDistX, deltaDistY;
    int side, hit;

    /* Projection & drawing */
    double perpDist;
    int drawStart, drawEnd;
    double wallX;
    int texID;
} t_ray;

typedef struct s_mlx
{
	t_file		file;
	void		*mlx_ptr;
	mlx_image_t	*img;
	int			width;
	int			height;
	double		cos_angle;
	double		sin_angle;
	int			speed;
	t_player    player;
	t_ray		ray;
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
void parse_elements(t_file *file, int fd);

// void	parse_elements(t_file *file, int fd);
void	parse_floor_and_ceiling(t_floor *floor, t_ceiling *ceiling, \
								char **line, char element);
/**
 * Parses and stores a texture path for a given cardinal direction.
 * ydir_x < 0)
	{
		mlx->ray.stepX = -1;
		mlx->ray.sideDistX = (mlx->ray.pos_x - mlx->ray.mapX) \
		* mlx->ray.deltaDistX;
	}
	else
	{
		mlx->ray.stepX = +1;
		mlx->ray.sideDistX = (mlx->ray.mapX + 1.0 - mlx->ray.pos_x) \
		* mlx->ray.deltaDistX;
	}
	if (mlx->ray.raydir_y < 0)
	{
		mlx->ray.stepY = -1;
		mlx->ray.sideDistY = (mlx->ray.pos_y - mlx->ray.mapY) \
		* mlx->ray.deltaDistY;
	}
	else
	{
		mlx->ray.stepY = +1;
		mlx->ray.sideDistY = (mlx->ray.mapY + 1.0 - mlx->ray.pos_y) \
		* mlx->ray.deltaDistY;
	}
}*/
void parse_textures(t_texture *texture, int cardinal, char **line, char *word);

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
 * ydir_x < 0)
	{
		mlx->ray.stepX = -1;
		mlx->ray.sideDistX = (mlx->ray.pos_x - mlx->ray.mapX) \
		* mlx->ray.deltaDistX;
	}
	else
	{
		mlx->ray.stepX = +1;
		mlx->ray.sideDistX = (mlx->ray.mapX + 1.0 - mlx->ray.pos_x) \
		* mlx->ray.deltaDistX;
	}
	if (mlx->ray.raydir_y < 0)
	{
		mlx->ray.stepY = -1;
		mlx->ray.sideDistY = (mlx->ray.pos_y - mlx->ray.mapY) \
		* mlx->ray.deltaDistY;
	}
	else
	{
		mlx->ray.stepY = +1;
		mlx->ray.sideDistY = (mlx->ray.mapY + 1.0 - mlx->ray.pos_y) \
		* mlx->ray.deltaDistY;
	}
}
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

// bool touch(double px, double py, t_map *map);
bool   touch(double px, double py, t_map *map, double radius);
void put_pixel(int x, int y, uint32_t color, mlx_image_t *img);
void clear_image(t_mlx *mlx);
int	get_color(t_mlx *mlx, int mode);
void print_sky_and_floor(t_mlx *mlx);
void move_player(mlx_key_data_t key_data, t_mlx *mlx);
void init_player(t_player *player, t_map *map);
void cast_single_ray(t_mlx *mlx, double rayAngle, int screenX);

void	perform_dda(t_mlx *mlx);
void	draw_stripe(t_mlx *mlx, int x);

// UTILS

char	**ft_split_cub3d(char const *s, char c);
int		check_spaces(char **ptr);
char	*skip_spaces(char *line);

#endif