/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:45:23 by drestrep          #+#    #+#             */
/*   Updated: 2025/05/10 20:53:38 by drestrep         ###   ########.fr       */
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
# include <math.h>
# include <assert.h>
# include "../libft/inc/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define USAGE_ERROR "Correct use: ./cub3d map_name.cub"
# define EMPTY_MAP "Map is empty"
# define DOUBLE_MAP "Only one map allowed"
# define INVALID_MAP "Invalid map"
# define INVALID_TEXTURES "Invalid textures"
# define NO_PLAYER "No player on the map"
# define OUT_OF_BOUNDS "Player out of bounds"
# define DUPLICATED_TEXTURE "Texture duplicate"
# define INVALID_COLOR "Invalid color format"

# define NO 0
# define SO 1
# define EA 2
# define WE 3

# define R 0
# define G 1
# define B 2

# define WIDTH 800
# define HEIGHT 800
# define BLOCK  64
# define PI  3.14159265359
#define MAX_DDA_STEPS 1000

typedef struct s_points
{
	int				filled;
	int				x_nbrs;
	char			nbr;
}				t_points;

typedef struct s_map
{
	t_points		**coord;
	int				x_nbrs;
	int				y_nbrs;
	char			**raw_lines;
}				t_map;

typedef struct s_texture
{
	mlx_texture_t	*img;
	xpm_t			*xpm;
	char			*path;
	int				width;
	int				height;
	bool			empty;
}				t_texture;

typedef struct s_floor
{
	int			color[3];
	bool		empty;
}				t_floor;

typedef struct s_ceiling
{
	int			color[3];
	double		radius;
	bool		empty;
}				t_ceiling;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		angle;
}				t_player;

typedef struct s_file
{
	t_map		map;
	t_floor		floor;
	t_ceiling	ceiling;
	t_texture	textures[4];

}				t_file;

typedef struct s_ray
{
/* Camera & ray direction */
	double	pos_x;
	double	pos_y;
	double	raydir_x;
	double	raydir_y;

	/* DDA state */
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;

	/* Projection & drawing */
	int		tex_id;
	int		draw_end;
	int		draw_start;
	int		line_height;
	double	perp_dist;
}				t_ray;

typedef struct s_mlx
{
	t_ray		ray;
	t_file		file;
	t_player	player;
	mlx_image_t	*img;
	int			flag_error;
	int			speed;
	int			width;
	int			height;
	void		*mlx_ptr;
	double		cos_angle;
	double		sin_angle;
	char		*error_msg;
}				t_mlx;

typedef struct s_dh
{
	int			x;
	int			y;
	int			dh;
	double		wall_x;
	uint32_t	*pixels;
	uint32_t	color;
	t_texture	*t;
}				t_dh;

typedef struct s_flags
{
	bool	gnl_flag;
	bool	rgb_flag;
	bool	textures_flag;
}				t_flag;

typedef struct s_allocated
{
	int		fd;
	char	*var1;
	char	*var2;
	char	**var3;
	t_flag	flags;
	t_mlx	*mlx;
}				t_allocated;

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
 * @param[in, out] file Pointer to the t_file structure where parsed
 * data will be stored.
 * @param[in] argv Path to the file to be parsed.
 */
void	parsing(t_mlx	*mlx, char *argv);

/**
 * Parses the textures and color elements from the given file descriptor.
 * 
 * @param[in, out] file Pointer to the t_file structure where parsed
 * elements will be stored.
 * @param[in] fd File descriptor of the map file being read.
 */
void	parse_elements(t_mlx *mlx, t_file *file, int fd);

/**
 * Parses and stores RGB values for the floor or ceiling.
 * 
 * @param[in, out] tobfreed Pointer to a structure containing allocations
 * that may be used for cleanup.
 * @param[in, out] file Pointer to the t_file structure where the parsed
 * RGB values will be stored.
 * @param[in, out] line Pointer to the current parsing position in the
 * input line; this pointer is advanced during parsing.
 * @param[in] element Character representing the target: 'F' for floor,
 * 'C' for ceiling.
 */
void	parse_floor_and_ceiling(t_allocated *tobfreed, t_file *file, \
								char **line, char element);
/**
 * Parses and validates a texture path, storing it in the corresponding
 * texture slot.
 * 
 * @param[in, out] tobfreed Pointer to an allocation management structure
 * used for cleanup on error.
 * @param[out] texture Pointer to the texture array where the parsed path
 * will be stored.
 * @param[in] cardinal Index representing the direction
 * (e.g., NO, SO, EA, WE) to store the texture.
 */
void	parse_textures(t_allocated *tobfreed, t_texture *texture, \
						int cardinal);

/**
 * Parses the map lines from the file and stores them in the map structure.
 * 
 * @param[in, out] map Pointer to the t_map structure where the parsed lines
 * will be stored.
 * @param[in] fd File descriptor of the map file being read.
 * @param[in] size The number of lines in the map section.
 */
void	parse_map(t_mlx *mlx, t_map *map, int fd, int size);

/**
 * Finds the first map line in a file.
 * 
 * Reads lines from the file descriptor `fd`, trims spaces, and returns
 * the first line with a digit. 
 * Exits the program if no valid map line is found.
 * 
 * @param[in] fd The file descriptor to read from.
 * 
 * @return The first line with a digit, or exits the program on failure.
 */
char	*get_to_map(t_allocated *tobfreed, int fd);

/**
 * Determines the number of lines in the map section of the file.
 * 
 * @param[in] fd File descriptor of the map file being read.
 * 
 * @return The number of lines in the map section.
 */
int		get_map_size(t_allocated *tobfreed, int fd);

/**
 * Frees all map and texture-related resources in the t_mlx structure.
 * 
 * @param[in, out] mlx Pointer to the t_mlx structure to be cleaned up.
 * @param[in] path_flag Passed to free_textures to determine if paths
 * should also be freed.
 */
void	free_all(t_mlx *mlx, int path_flag);

/**
 * Frees texture resources from the t_mlx structure.
 * 
 * @param[in, out] mlx Pointer to the structure containing the textures.
 * @param[in] path_flag If set to 1, also frees the texture path strings.
 */
void	free_textures(t_mlx *mlx, int path_flag);

/**
 * Frees the memory used by the map coordinates and raw lines.
 * 
 * @param[in, out] map Pointer to the map structure whose memory is to be freed.
 */
void	free_map(t_map *map);

/**
 * Frees allocated resources and exits the program with an error message.
 * 
 * @param[in, out] tobfreed Pointer to the structure containing memory to free.
 * @param[in] rgb_flag If true, frees RGB-related allocations.
 * @param[in] textures_flag If true, calls free_textures to free texture data.
 * @param[in] error_msg Error message to print before exiting.
 * 
 * @note Always calls ft_exit. This function does not return.
 */
void	free_alloc_and_exit(t_allocated *tobfreed, t_flag flags, \
			char *error_msg);

void	free_gnl(int fd);

void	free_rgb(t_allocated *tobfreed);

// EXIT
/**
 * Prints the argument before exiting the program.
 * 
 * @param[in] message Message to be printed.
 */
void	*ft_exit(char *error_msg);

// EXECUTION
/**
 * @brief Checks if the given (px, py) coordinates collide with a wall or
 * are out of bounds.
 * 
 * @param[in] px X-coordinate in the game world.
 * @param[in] py Y-coordinate in the game world.
 * @param[in] map Pointer to the map structure used for collision detection.
 * 
 * @return true if the point is out of bounds or touches a wall
 * ('1'); false otherwise.
 */
bool	touch(double px, double py, t_map *map);

/**
 * Swaps the byte order of the color to match the expected format
 * before drawing.
 * Ignores drawing if the pixel is out of image bounds.
 * 
 * @param[in] x X-coordinate on the image.
 * @param[in] y Y-coordinate on the image.
 * @param[in] color The color to draw the pixel in (in 0xRRGGBB format).
 * @param[in, out] img Pointer to the image where the pixel will be drawn.
 */
void	put_pixel(int x, int y, uint32_t color, mlx_image_t *img);

/**
 * Iterates over all pixels in the image and sets them to color 0 (black).
 * 
 * @param[in, out] mlx Pointer to the main graphics context containing
 * the image to clear.
 */
void	clear_image(t_mlx *mlx);

/**
 * Retrieves the color for either the floor or the ceiling based on the mode.
 * 
 * Constructs a 32-bit color value using RGB components from the floor
 * or ceiling structure.
 * The color is returned in 0xRRGGBBAA format, with
 * an alpha value of 255 (opaque).
 * 
 * @param[in] mlx Pointer to the graphics context containing the floor and
 * ceiling color data.
 * @param[in] mode Determines which color to retrieve: 1 for ceiling, 
 * other values for floor.
 * 
 * @return The color value as a 32-bit integer.
 */
int		get_color(t_mlx *mlx, int mode);

/**
 * Draws the sky and floor on the image.
 * 
 * Divides the screen into two halves and uses `get_color` and `put_pixel` 
 * to draw the sky and floor.
 * 
 * @param[in, out] mlx Pointer to the graphics context with image 
 * and color data.
 */
void	print_sky_and_floor(t_mlx *mlx);

/**
 * Updates player movement and rotation based on keyboard input.
 * 
 * Rotates the player (left and right arrows keys) and moves the 
 * player (WASD), ensuring the angle stays within valid bounds.
 * 
 * @param[in] key_data The key input data.
 * @param[in, out] mlx Pointer to the graphics context containing 
 * the player's position and angle.
 */

void	move_player(mlx_key_data_t key_data, t_mlx *mlx);

/**
 * Initializes the player's position based on the map.
 * 
 * Scans the map to find and set the player's starting position using 
 * `set_player_position`.
 * 
 * @param[in, out] player Pointer to the player structure.
 * @param[in] map Pointer to the map structure with the map data.
 */
void	init_player(t_player *player, t_map *map);

/**
 * Casts a ray to calculate the intersection and draws the corresponding stripe.
 * 
 * Initializes ray parameters, performs raycasting, selects texture,
 *  and draws the stripe at screenX.
 * 
 * @param[in, out] mlx Pointer to the graphics context containing 
 * ray and player data.
 * @param[in] rayAngle The angle at which the ray is cast.
 * @param[in] screenX The screen column where the ray's stripe is drawn.
 */

void	cast_single_ray(t_mlx *mlx, double rayAngle, int screenX);

/**
 * Performs the DDA algorithm to trace the ray through the map.
 * 
 * Steps through the map grid, updating the ray's position and
 *  detecting wall hits or boundary crossing.
 * 
 * @param[in, out] mlx Pointer to the graphics context with ray information.
 */
void	perform_dda(t_mlx *mlx);

/**
 * Draws a vertical wall stripe at the specified x-coordinate.
 * 
 * Uses the appropriate texture or a default gray color to draw a
 *  stripe based on raycasting results. 
 * The stripe is drawn between the calculated start and end heights.
 * 
 * @param[in, out] mlx Pointer to the graphics context containing 
 * ray and texture data.
 * @param[in] x The x-coordinate for the stripe on the screen.
 */
void	draw_stripe(t_mlx *mlx, int x);

// UTILS

char	**ft_split_cub3d(t_allocated *tobfreed, char const *s, char c);
int		check_spaces(char **ptr);
char	*skip_spaces(char *line);

void	flags_init(t_allocated *tobfreed, bool rgb_flag, \
					bool textures_flag, bool gnl_flag);

#endif