
// void put_pixel(t_mlx *mlx, int x, int y, int color)
// {
//     if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
//         return;
//     int *img_data = (int *)mlx_get_data_addr(mlx->img.img_ptr, NULL, NULL, NULL);
//     img_data[y * mlx->width + x] = color;
// }

int worldMap[mapWidth][mapHeight] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


// Función que implementa el renderizado con raycasting.
// void render_scene(t_mlx *mlx, t_player *player)
// {
//     int x, y;
	
//     for (x = 0; x < WIDTH; x++)
//     {
//         // Calcula la posición en el plano de cámara para este rayo.
//         double cameraX = 2 * x / (double)WIDTH - 1;
//         double rayDirX = player->dirX + player->planeX * cameraX;
//         double rayDirY = player->dirY + player->planeY * cameraX;
        
//         // Posición actual en la cuadrícula.
//         int mapX = (int)(player->posX);
//         int mapY = (int)(player->posY);
        
//         // Distancias que debe recorrer el rayo para cruzar una celda.
//         double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
//         double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
//         double sideDistX, sideDistY;
//         int stepX, stepY;
//         int hit = 0;
//         int side;

//         // Cálculo del paso y la distancia inicial en X.
//         if (rayDirX < 0)
//         {
//             stepX = -1;
//             sideDistX = (player->posX - mapX) * deltaDistX;
//         }
//         else
//         {
//             stepX = 1;
//             sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
//         }
//         // Cálculo del paso y la distancia inicial en Y.
//         if (rayDirY < 0)
//         {
//             stepY = -1;
//             sideDistY = (player->posY - mapY) * deltaDistY;
//         }
//         else
//         {
//             stepY = 1;
//             sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
//         }

//         // Algoritmo DDA: se avanza celda a celda hasta encontrar una pared.
//         while (hit == 0)
// 		{
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			// Verifica que no se salga del rango del mapa
// 			if (mapX < 0 || mapX >= mapWidth || mapY < 0 || mapY >= mapHeight)
// 			{
// 				hit = 1;
// 				break;
// 			}
// 			if (worldMap[mapX][mapY] > 0)
// 				hit = 1;
// 		}

//         // Calcula la distancia perpendicular a la pared (para evitar efecto "fish-eye").
//         double perpWallDist;
//         if (side == 0)
//             perpWallDist = (mapX - player->posX + (1 - stepX) / 2.0) / rayDirX;
//         else
//             perpWallDist = (mapY - player->posY + (1 - stepY) / 2.0) / rayDirY;
        
//         // Calcula la altura de la pared en pantalla.
//         int lineHeight = (int)(HEIGHT / perpWallDist);
//         int drawStart = -lineHeight / 2 + HEIGHT / 2;
//         if (drawStart < 0)
//             drawStart = 0;
//         int drawEnd = lineHeight / 2 + HEIGHT / 2;
//         if (drawEnd >= HEIGHT)
//             drawEnd = HEIGHT - 1;

//         // Selecciona el color según el tipo de pared.
//         int color;
//         switch (worldMap[mapX][mapY])
//         {
//             case 1:  color = 0xFF0000; break;  // Rojo
//             case 2:  color = 0x00FF00; break;  // Verde
//             case 3:  color = 0x0000FF; break;  // Azul
//             case 4:  color = 0xFFFFFF; break;  // Blanco
//             case 5:  color = 0xAAAAAA; break;  // Blanco
//             default: color = 0xFFFF00; break;  // Amarillo
//         }
//         // Oscurece el color si se impacta una pared lateral.
//         if (side == 1)
//             color = color / 2;
        
//         // Dibuja la columna vertical correspondiente a la pared.
//         for (y = drawStart; y < drawEnd; y++)
//             put_pixel(mlx, x, y, color);
//     }
// }


static void key_callback(mlx_key_data_t key_data, void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    (void)mlx;
    if (key_data.key == MLX_KEY_ESCAPE)
        exit(1);
    
    // if (key_data.key == MLX_KEY_UP)
    // {
    //     if (worldMap[(int)(mlx->player.posX + mlx->player.dirX * MOVE_SPEED)]
    //                 [(int)(mlx->player.posY)] == 0)
    //         mlx->player.posX += mlx->player.dirX * MOVE_SPEED;
    //     if (worldMap[(int)(mlx->player.posX)]
    //                 [(int)(mlx->player.posY + mlx->player.dirY * MOVE_SPEED)] == 0)
    //         mlx->player.posY += mlx->player.dirY * MOVE_SPEED;
    // }
    // if (key_data.key == MLX_KEY_DOWN)
    // {
    //     if (worldMap[(int)(mlx->player.posX - mlx->player.dirX * MOVE_SPEED)]
    //                 [(int)(mlx->player.posY)] == 0)
    //         mlx->player.posX -= mlx->player.dirX * MOVE_SPEED;
    //     if (worldMap[(int)(mlx->player.posX)]
    //                 [(int)(mlx->player.posY - mlx->player.dirY * MOVE_SPEED)] == 0)
    //         mlx->player.posY -= mlx->player.dirY * MOVE_SPEED;
    // }
    // if (key_data.key == MLX_KEY_RIGHT)
    // {
    //     double oldDirX = mlx->player.dirX;
    //     mlx->player.dirX = mlx->player.dirX * cos(-ROT_SPEED) - mlx->player.dirY * sin(-ROT_SPEED);
    //     mlx->player.dirY = oldDirX * sin(-ROT_SPEED) + mlx->player.dirY * cos(-ROT_SPEED);
    //     double oldPlaneX = mlx->player.planeX;
    //     mlx->player.planeX = mlx->player.planeX * cos(-ROT_SPEED) - mlx->player.planeY * sin(-ROT_SPEED);
    //     mlx->player.planeY = oldPlaneX * sin(-ROT_SPEED) + mlx->player.planeY * cos(-ROT_SPEED);
    // }
    // if (key_data.key == MLX_KEY_LEFT)
    // {
    //     double oldDirX = mlx->player.dirX;
    //     mlx->player.dirX = mlx->player.dirX * cos(ROT_SPEED) - mlx->player.dirY * sin(ROT_SPEED);
    //     mlx->player.dirY = oldDirX * sin(ROT_SPEED) + mlx->player.dirY * cos(ROT_SPEED);
    //     double oldPlaneX = mlx->player.planeX;
    //     mlx->player.planeX = mlx->player.planeX * cos(ROT_SPEED) - mlx->player.planeY * sin(ROT_SPEED);
    //     mlx->player.planeY = oldPlaneX * sin(ROT_SPEED) + mlx->player.planeY * cos(ROT_SPEED);
    // }
    
    // Redibujar la escena tras actualizar la posición y dirección
    // render_scene(mlx, &mlx->player);
    // mlx_image_to_window(mlx->mlx_ptr, mlx->img.img_ptr, 0, 0);
}


void cube_init(t_mlx *mlx)
{
    // Se configuran las dimensiones de la ventana.
    mlx->width = WIDTH;
    mlx->height = HEIGHT;
    
    // Inicializa la MLX (en este caso, la versión de Codam).
    mlx->mlx_ptr = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
    if (!mlx->mlx_ptr)
        ft_exit("Error al inicializar MLX");
    
    // Crea una imagen donde se dibujará la escena.
    mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
    if (!mlx->img.img_ptr)
        ft_exit("Error al crear la imagen");

    // Configuración inicial del jugador.
    // t_player player;
    // player.posX = 12.0;
    // player.posY = 12.0;
    // player.dirX = -1.0;
    // player.dirY = 0.0;
    // player.planeX = 0.0;
    // player.planeY = 0.66;

    // Renderiza la escena usando raycasting.
    // render_scene(mlx, &player);
    
    // Muestra la imagen en la ventana.
    draw_square(WIDTH/2, HEIGHT/2, 10, 0X00FF00, mlx);
    mlx_image_to_window(mlx->mlx_ptr, mlx->img.img_ptr, 0, 0);
    // Registra el callback de teclado.
    mlx_key_hook(mlx->mlx_ptr, key_callback, mlx);
    
    // Inicia el loop de eventos.
    mlx_loop(mlx->mlx_ptr);
}


// --------------------- drawsquare --------------------

void put_pixel(int x, int y, int color, mlx_image_t *img)
{
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
        return;
    // int index;
    // img->pixels[index] = color & 0xFF;
    // img->pixels[index +1] = (color >> 8) & 0xFF;
    // img->pixels[index +2] = (color >> 16) & 0xFF;
    img->pixels[y * img->width + x] = color;
    mlx_put_pixel(img, x, y, color);
}

void draw_square(int x, int y, int size, int color, mlx_image_t *img)
{
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, img);  
    for (int i = 0; i < size; i++)
        put_pixel(x, y+i, color, img);
    for (int i = 0; i < size; i++)
        put_pixel(x+size, y+i, color, img);
    for (int i = 0; i < size; i++)
        put_pixel(x+i, y+size, color, img);

}
static void key_callback(mlx_key_data_t key_data, void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    (void)mlx;
    if (key_data.key == MLX_KEY_ESCAPE)
        exit(1);
}

void cube_init(t_mlx *mlx)
{
    mlx->width = WIDTH;
    mlx->height = HEIGHT;
    mlx->mlx_ptr = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
    if (!mlx->mlx_ptr)
        ft_exit("Error al inicializar MLX");
    mlx->img = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
    if (!mlx->img)
        ft_exit("Error al crear la imagen");
    draw_square(WIDTH/2, HEIGHT/2, 10, 0XAAAAAA, mlx->img);
    mlx_image_to_window(mlx->mlx_ptr, mlx->img, 0, 0);
    mlx_key_hook(mlx->mlx_ptr, key_callback, mlx);
    mlx_loop(mlx->mlx_ptr);
}
