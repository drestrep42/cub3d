/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:31:26 by drestrep          #+#    #+#             */
/*   Updated: 2025/03/27 19:44:58 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void key_callback(mlx_key_data_t key_data, void *param)
{
    t_mlx *mlx = (t_mlx *)param;
	(void)mlx;
	// printf("path: '%s'\n", mlx->file.textures[NO].path);
    if (key_data.key == MLX_KEY_ESCAPE)
        exit(1);
	// mlx_destroy_image(window->mlx, window->img.img_ptr);
	// window->img.img_ptr = mlx_new_image(window->mlx, WIDTH_WIN, HEIGHT_WIN);
	// window->img.img_pixel_ptr = mlx_get_data_addr(window->img.img_ptr,
	// 		&window->img.bits_per_pixel, &window->img.line_length,
	// 		&window->img.endian);
}



void	cube_init(t_mlx *mlx)
{

	mlx->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
// 	double posX = 22, posY = 12;  //x and y start position
// 	double dirX = -1, dirY = 0; //initial direction vector
// 	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

// 	double time = 0; //time of current frame
// 	double oldTime = 0; //time of previous frame
// 	int worldMap[mapWidth][mapHeight]=
// 	{
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
// 		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// 	};
// 	while(1)
//   	{
// 		for(int x = 0; x < WIDTH; x++)
// 		{
// 			//calculate ray position and direction
// 			double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
// 			double rayDirX = dirX + planeX * cameraX;
// 			double rayDirY = dirY + planeY * cameraX;
// 			int mapX = int(posX);
//       int mapY = int(posY);
// 	    double sideDistX;
//       double sideDistY;
// double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
//       double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

//       double perpWallDist;
// int stepX;
//       int stepY;

//       int hit = 0; //was there a wall hit?
//       int side; //was a NS or a EW wall hit?
//       //calculate step and initial sideDist
//       if(rayDirX < 0)
//       {
//         stepX = -1;
//         sideDistX = (posX - mapX) * deltaDistX;
//       }
//       else
//       {
//         stepX = 1;
//         sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//       }
//       if(rayDirY < 0)
//       {
//         stepY = -1;
//         sideDistY = (posY - mapY) * deltaDistY;
//       }
//       else
//       {
//         stepY = 1;
//         sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//       }
//       //perform DDA
//       while(hit == 0)
//       {
//         //jump to next map square, either in x-direction, or in y-direction
//         if(sideDistX < sideDistY)
//         {
//           sideDistX += deltaDistX;
//           mapX += stepX;
//           side = 0;
//         }
//         else
//         {
//           sideDistY += deltaDistY;
//           mapY += stepY;
//           side = 1;
//         }
//         //Check if ray has hit a wall
//         if(worldMap[mapX][mapY] > 0) hit = 1;
//       }



// 		}
// 	}
// 	mlx_image_to_window(mlx->mlx_ptr, mlx->img_ptr, 0, 0);
	mlx_key_hook(mlx->mlx_ptr, key_callback, mlx);
	mlx_loop(mlx->mlx_ptr);
}
