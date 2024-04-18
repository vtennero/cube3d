

# include "cube3d.h"


#define mapWidth 24
#define mapHeight 24


// typedef struct {
//     unsigned char r;
//     unsigned char g;
//     unsigned char b;
// } ColorRGB;

// // Define colors
// ColorRGB RGB_Red = {255, 0, 0};
// ColorRGB RGB_Green = {0, 255, 0};
// ColorRGB RGB_Blue = {0, 0, 255};
// ColorRGB RGB_White = {255, 255, 255};
// ColorRGB RGB_Yellow = {255, 255, 0};

void	lodev()
{
	// int mapWidth;
	// int mapHeight;
	int	w;

	// mapWidth = 24;
	// mapHeight = 24;
    t_ray_node* list = NULL; // Start with an empty list


int worldMap[mapWidth][mapHeight]=
{
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

    void *mlx_ptr;
    void *win_ptr;

    mlx_ptr = mlx_init();
    // win_ptr = mlx_new_window(mlx_ptr, screenWidth, screenHeight, "MLX Window");

// posX and posY represent the position vector of the player. dirX and dirY represent the direction of the player, and planeX and planeY the camera plane of the player.

	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

//   double time = 0; //time of current frame
//   double oldTime = 0; //time of previous frame

w = screenWidth;
	for(int x = 0; x < w; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			if (x % 10 == 0)
				printf("ray %d x: %f, %f\n", x, rayDirX, rayDirY);
	
			//which box of the map we're in
			int mapX = (int)(posX);
			int mapY = (int)(posY);

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			 //length of ray from one x or y-side to next x or y-side
			double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			
			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}

			
			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0)
					hit = 1;
			}
			
			//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
			if(side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			
			//Calculate height of line to draw on screen
			int lineHeight = (int)(screenHeight / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int draw_start = -lineHeight / 2 + screenHeight / 2;
			if(draw_start < 0)draw_start = 0;
			int draw_end = lineHeight / 2 + screenHeight / 2;
			if(draw_end >= screenHeight)draw_end = screenHeight - 1;
			printf("draw_start %d draw_end %d\n", draw_start, draw_end);

			int color;

				int tileValue = worldMap[mapX][mapY];
			int RGB_Red = 0xFF0000;  // Hexadecimal for {255, 0, 0}
			int RGB_Green = 0x00FF00;  // Hexadecimal for {0, 255, 0}
			int RGB_Blue = 0x0000FF;  // Hexadecimal for {0, 0, 255}
			int RGB_White = 0xFFFFFF;  // Hexadecimal for {255, 255, 255}
			int RGB_Yellow = 0xFFFF00;  // Hexadecimal for {255, 255, 0}
			if (tileValue == 1) {
				color = RGB_Red;
			} else if (tileValue == 2) {
				color = RGB_Green;
			} else if (tileValue == 3) {
				color = RGB_Blue;
			} else if (tileValue == 4) {
				color = RGB_White;
			} else {
				color = RGB_Yellow;
			}

			// printf("Color chosen - Red: %d, Green: %d, Blue: %d\n", color.r, color.g, color.b);
			// addRay(&list, x, draw_start, draw_end, color);
			// for (int y = draw_start; y < draw_end; y++)
			// {
			// 	// mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x00FF00); // 0x00FF00 is the color code for green
			// 	mlx_pixel_put(mlx_ptr, win_ptr,x, y, color); // 0x00FF00 is the color code for green
			// }



	}
	// render_ray_list(list, mlx_ptr, win_ptr);
	// printRayList(list);
	(void)win_ptr;
    mlx_loop(mlx_ptr);

}