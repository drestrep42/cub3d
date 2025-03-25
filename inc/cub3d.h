/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:45:23 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/25 14:44:33 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_h
# define CUB3D_h

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include "../libft/inc/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

#define USAGE_ERROR "Correct use: ./cub3d map_name.cub"
#define EMPTY_MAP "Map is empty"
#define INVALID_MAP "Invalid map"
#define INVALID_TEXTURES "Invalid textures"

#define NO 0
#define SO 1
#define EA 2
#define WE 3

#define R 0
#define G 1
#define B 2

#define WIDTH 2000
#define HEIGHT 2000

typedef struct s_points
{
	int			x;
	int			y;
	int			z;
	int			height;
}				t_points;

typedef struct s_map
{
	t_points	**coord;
}				t_map;

typedef struct s_texture
{
	char		*path;
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
	void		*win_ptr;
	void		*img_ptr;
	int			width;
	int			height;
}				t_mlx;

void	cube_init(t_mlx *mlx);

void	parsing(t_file *file, int fd);

void	free_all(t_mlx *mlx);
void	ft_exit(char *message);

#endif