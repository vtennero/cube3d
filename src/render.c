/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/18 23:35:22 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define MLX_SUCCESS 0
#define MLX_ERROR -1
#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF


int get_texture_color(t_texture *texture, int x, int y)
{
    // printf("Getting texture color at (X: %d, Y: %d)\n", x, y);
    int pixel_pos = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
    int color = *(int *)(texture->data + pixel_pos);
    return color;
}



void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

    if (x < 0 || x >= DEFAULT_S_WIDTH || y < 0 || y >= DEFAULT_S_HEIGHT) {
        fprintf(stderr, "Attempted to write pixel out of bounds: x=%d, y=%d\n", x, y);
        return; // Skip drawing for invalid coordinates
    }

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void render_ray(t_img *img, t_ray ray, t_texture *texture) {
    if (img->bpp != texture->tex_bpp || img->endian != texture->tex_endian) {
        fprintf(stderr, "Error: Texture and screen format mismatch\n");
        exit(EXIT_FAILURE);
    }

    // Use the pre-calculated texX for the ray
    int texX = ray.texX;  // This value is already calculated and should be valid for the texture width

    int y = ray.draw_start;
    while (y < ray.draw_end) {
        // Calculate texY based on the proportion of the wall's visible height
        // printf("renderray: texture dimensions width %d x height %d", texture->width, texture->height);
        int texY = ((y - ray.draw_start) * texture->height) / ray.lineHeight;
        texY %= texture->height;  // Wrap around if necessary
        int color = get_texture_color(texture, texX, texY);
        img_pix_put(img, ray.x, y, color);
        y++;
    }
}

void render_sky(t_img *img, void *mlx_ptr, char *sky_texture_path) {
    int sky_width, sky_height;
    void *sky_texture;
    char *sky_data;
    int bpp, line_len, endian;

    // Load the sky texture
    sky_texture = mlx_xpm_file_to_image(mlx_ptr, sky_texture_path, &sky_width, &sky_height);
    sky_data = mlx_get_data_addr(sky_texture, &bpp, &line_len, &endian);

    for (int i = 0; i < DEFAULT_S_HEIGHT / 2; i++) {
        for (int j = 0; j < DEFAULT_S_WIDTH; j++) {
            // Calculate pixel position in the texture
            int tx = (j * sky_width) / DEFAULT_S_WIDTH; // repeat texture if needed
            int ty = (i * sky_height) / (DEFAULT_S_HEIGHT / 2); // repeat texture vertically

            // Get the color from the texture
            int color = *((int *)(sky_data + ty * line_len + tx * (bpp / 8)));

            // Put the color into the main image
        // printf("render_sky: calling img_pix_put\n");
            img_pix_put(img, j, i, color);
        }
    }

    // Clean up the texture
    mlx_destroy_image(mlx_ptr, sky_texture);
}

void render_ray_list(t_game *game) {
    int i = 0;
    t_ray_node* ray_list = NULL;
    ray_list = calculate_rays(game, ray_list);
    t_ray_node* current = ray_list;

    while (current != NULL) {

        t_texture *used_texture = &game->walltextures[current->ray.wall_face];
        if (i == 400 || i == 399 || i == 401)
            printf(" Ray #%d - texX: %d,  lineHeight: %d, perpWallDist: %f\n", i, current->ray.texX, current->ray.lineHeight, current->ray.perpWallDist);
        render_ray(&game->img, current->ray, used_texture);
        current = current->next;
        i++;
    }
}

void my_mlx_pixel_put(char *data_addr, int x, int y, int color, int size_line, int bits_per_pixel) {
    
	// int pixel;
	char *pixel;
    // Ensure x and y are within the bounds of the image dimensions
    if (x < 0 || y < 0 || x >= size_line / (bits_per_pixel / 8) || y >= size_line / (bits_per_pixel / 8)) {
        return;
    }

    pixel = data_addr + (y * size_line + x * (bits_per_pixel / 8));
    *(unsigned int*)pixel = color;
	    // pixel =  (y * size_line + x * (bits_per_pixel / 8));

	//    data_addr[pixel + 0] = (color >> 24);
    // 	data_addr[pixel + 1] = (color >> 16) & 0xFF;
    //     data_addr[pixel + 2] = (color >> 8) & 0xFF;
    //     data_addr[pixel + 3] = (color) & 0xFF;

	    // data_addr[pixel + 0] = (color) & 0xFF;
        // data_addr[pixel + 1] = (color >> 8) & 0xFF;
        // data_addr[pixel + 2] = (color >> 16) & 0xFF;
        // data_addr[pixel + 3] = (color >> 24);
}



// void my_mlx_pixel_put(char *data_addr, int x, int y, int color, int size_line, int bits_per_pixel) {
//     char *pixel;
//     unsigned char alpha;

//     // Extract the alpha value (most significant byte of color) and convert to integer
//     alpha = (color >> (bits_per_pixel - 8)) & 0xFF;

//     // Ensure x and y are within the bounds of the image dimensions
//     if (x < 0 || y < 0 || x >= size_line / (bits_per_pixel / 8) || y >= size_line / (bits_per_pixel / 8)) {
//         return;
//     }

//     pixel = data_addr + (y * size_line + x * (bits_per_pixel / 8));

//     // Apply alpha blending
//     unsigned int original_color = *(unsigned int*)pixel;
//     unsigned char original_alpha = (original_color >> (bits_per_pixel - 8)) & 0xFF;
//     unsigned char final_alpha = alpha + (original_alpha * (255 - alpha)) / 255;
//     unsigned int final_color = ((color & 0x00FFFFFF) * alpha + (original_color & 0x00FFFFFF) * original_alpha * (255 - alpha)) / (255 * 255) & 0x00FFFFFF;
//     final_color |= (final_alpha << (bits_per_pixel - 8));

//     // Write the final color to the pixel
//     *(unsigned int*)pixel = final_color;
// }


// void my_mlx_pixel_put(char *data_addr, int x, int y, int color, int size_line, int bits_per_pixel) {
//     char *pixel;
//     unsigned char alpha;

//     // Extract the alpha value (first two characters of color) and convert to integer
//     alpha = (color >> 24) & 0xFF;

//     // Ensure x and y are within the bounds of the image dimensions
//     if (x < 0 || y < 0 || x >= size_line / (bits_per_pixel / 8) || y >= size_line / (bits_per_pixel / 8)) {
//         return;
//     }

//     pixel = data_addr + (y * size_line + x * (bits_per_pixel / 8));

//     // Apply alpha blending
//     unsigned int original_color = *(unsigned int*)pixel;
//     unsigned char original_alpha = (original_color >> 24) & 0xFF;
//     unsigned char final_alpha = alpha + (original_alpha * (255 - alpha)) / 255;
//     unsigned int final_color = ((color & 0x00FFFFFF) * alpha + (original_color & 0x00FFFFFF) * original_alpha * (255 - alpha)) / (255 * 255) & 0x00FFFFFF;
//     final_color |= (final_alpha << 24);

//     // Write the final color to the pixel
//     *(unsigned int*)pixel = final_color;
// }

// void put_pixel_to_image(char *image_data, int width, int x, int y, int color) {
//     int pixel_offset = (y * width + x) * 4; // Each pixel is represented by 4 bytes (RGBA)
//     *((int*)(image_data + pixel_offset)) = color; // Set the pixel color
// }


// void put_pixel_to_window(void *mlx_ptr, void *win_ptr, int x, int y, int color) {
//     // Create a small image (1x1 pixel) with the desired color
//     void *pixel_img = mlx_new_image(mlx_ptr, 1, 1);
//     int *img_data = (int *)mlx_get_data_addr(pixel_img, NULL, NULL, NULL);
//     *img_data = color;

//     // Put the image (pixel) at the specified position in the window
//     mlx_put_image_to_window(mlx_ptr, win_ptr, pixel_img, x, y);

//     // Destroy the pixel image to avoid memory leaks
//     mlx_destroy_image(mlx_ptr, pixel_img);
// }

void draw_player_pos(t_game *game,int CELL_SIZE)
{
	int start_x=game->player->position.x*CELL_SIZE;
	int end_x = start_x + CELL_SIZE;
	int start_y=game->player->position.y*CELL_SIZE;
	int end_y = start_y + CELL_SIZE;
	// while (start_x < end_x && start_y < end_y)
	// {
    // 	mlx_pixel_put(game->mlx_ptr, game->minimap_win_ptr, start_y, start_x, 0xFF0000);
    // 	mlx_pixel_put(game->mlx_ptr, game->minimap_win_ptr, start_y+15, start_x-15, 0xFF0000);
	// 	start_x++;
	// 	start_y++;
	// }
	for (int x = start_x; x < end_x; x++) {
		// Iterate over each y-coordinate within the range
		for (int y = start_y; y < end_y; y++) {
			// Draw a pixel at the current position
			mlx_pixel_put(game->mlx_ptr, game->win_ptr, y, 350+x, 0xFF0000);
		}
	}
}
				



void draw_minimap(t_game *game,void *minimap_img, int **map, int rows, int cols) {
    char *data_addr;
    int bits_per_pixel;
    int size_line;
    int endian;
	(void)game;
    data_addr = mlx_get_data_addr(minimap_img, &bits_per_pixel, &size_line, &endian);
    int CELL_SIZE = 10;
    int x, y;

    for (y = 0; y < rows; y++) {
        for (x = 0; x < cols; x++) {
            int color = (map[y][x] == 1) ? 0x00FFFFFF :  0xFFDCDCDC; // White for 1, Black for 0
            int start_x = x * CELL_SIZE-1;
            int start_y = y * CELL_SIZE-1;
            int end_x = start_x + CELL_SIZE-1;
            int end_y = start_y + CELL_SIZE-1;

            for (int i = start_x; i < end_x; i++) {
                for (int j = start_y; j < end_y; j++) {
					
				// if (round(game->player->position.x) == j/CELL_SIZE  &&  round(game->player->position.y) == i/CELL_SIZE) 
				// 					color = 0xFF0000; 
				
                   	my_mlx_pixel_put(data_addr, i, j, color, size_line, bits_per_pixel);

                }
            }
        }
    }
    printf("draw end!\n");
}

int	render(t_game *game)
{
	if (game->win_ptr == NULL)
		return (1);
	// if (game->minimap_win_ptr == NULL)
	// 	return (1);
	
	handle_movement_left(game);
	handle_movement_right(game);
	handle_movement_forward(game);
	handle_movement_backward(game);
	handle_movement_strafe_left(game);
	handle_movement_strafe_right(game);
	handle_movement_dash(game);
	render_sky(&game->img, game->mlx_ptr, "textures/sky02.xpm");
    render_floor(game);
	render_ray_list(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);


//    mlx_clear_window(game->mlx_ptr, game->minimap_win_ptr);

    mlx_put_image_to_window(game->mlx_ptr,  game->win_ptr, game->minimap_img_ptr, 0, 350);
	draw_player_pos(game,10);
    // mlx_clear_window(game->mlx_ptr, game->minimap_win_ptr);

    // mlx_put_image_to_window(game->mlx_ptr, game->minimap_win_ptr, game->minimap_img_ptr, 0, 0);
	// draw_player_pos(game,15);
	return (0);
}




int	setup_game_mlx(t_game *game)
{



	if (game == NULL)
		return (MLX_ERROR);

	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		return (MLX_ERROR);
	game->win_ptr = mlx_new_window(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "my window");
	if (game->win_ptr == NULL)
	{
		free(game->win_ptr);
		return (MLX_ERROR);
	}
    preload_textures(game);


	game->img.mlx_img = mlx_new_image(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);



	// Minimap sectopn
	// Declare new window

	
    // void* win_minimap = mlx_new_window(game->mlx_ptr,500, 500, "2D Minimap");
	// game->minimap_win_ptr = mlx_new_window(game->mlx_ptr,300, 300, "2D Minimap");

	// Declare new image
	// void    *mini_map_img_ptr;
	int     img_width = 250;
	int     img_height = 250;

	game->minimap_img_ptr = mlx_new_image(game->mlx_ptr, img_width, img_height);
    draw_minimap(game,game->minimap_img_ptr ,game->map->data, game->map->height, game->map->width);

    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->minimap_img_ptr, 0,350);
    // mlx_put_image_to_window(game->mlx_ptr, game->minimap_win_ptr, game->minimap_img_ptr, 0, 0);

	// mlx_hook(recup->data.mlx_win, 33, 1L << 17, ft_exit, recup);
	mlx_hook(game->win_ptr, 2, 1L << 0, ft_key_press, game);

	mlx_loop_hook(game->mlx_ptr, &render, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, ft_key_release, game);

	mlx_loop(game->mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	// mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
	// mlx_destroy_display(game->mlx_ptr);
	// free(game->mlx_ptr);

	return (0);
}
