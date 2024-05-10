/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/10 16:27:11 by toto             ###   ########.fr       */
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



// void render_ray(t_img *img, t_ray ray, t_texture *texture, int rayIndex, int totalRays) {
//     if (img->bpp != texture->tex_bpp || img->endian != texture->tex_endian) {
//         fprintf(stderr, "Error: Texture and screen format mismatch\n");
//         exit(EXIT_FAILURE);
//     }

//     // Calculate texture X coordinate for the ray
//     // Assuming texture should wrap around completely for all rays across the screen
//     int texX = (rayIndex * texture->width) / totalRays;
//     texX %= texture->width;  // Wrap around by using modulo operation

//     int y = ray.draw_start;
//     while (y < ray.draw_end) {
//         int texY = ((y - ray.draw_start) * texture->height) / ray.lineHeight;
//         texY %= texture->height;  // Optionally ensure texY also wraps around if needed
//         int color = get_texture_color(texture, texX, texY);
//         img_pix_put(img, ray.x, y, color);
//         y++;
//     }
// }

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
        int texY = ((y - ray.draw_start) * texture->height) / ray.lineHeight;
        texY %= texture->height;  // Wrap around if necessary (usually not needed unless texture is shorter than the wall segment)

        int color = get_texture_color(texture, texX, texY);
        // printf("render_ray: calling img_pix_put\n");
        img_pix_put(img, ray.x, y, color);
        y++;
    }
}




// Function to render the sky (upper half)
// void render_sky(t_img *img, int sky_color) {
//     int i, j;
//     for (i = 0; i < DEFAULT_S_HEIGHT / 2; ++i) {
//         for (j = 0; j < DEFAULT_S_WIDTH; ++j) {
//             img_pix_put(img, j, i, sky_color);
//         }
//     }
// }

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

// void render_sky(t_game *game) {
//     t_texture *sky = game->skytexture;

//     for (int i = 0; i < game->screen_height / 2; i++) {
//         for (int j = 0; j < game->screen_width; j++) {
//             int tx = (j * sky->width) / game->screen_width;  // Repeat texture if needed
//             int ty = (i * sky->height) / (game->screen_height / 2);  // Repeat texture vertically

//             // Get the color from the texture
//             int color = *((int *)(sky->data + ty * sky->tex_line_len + tx * (sky->tex_bpp / 8)));

//             // Put the color into the main image
//             img_pix_put(&game->img, j, i, color);
//         }
//     }
// }










void render_ray_list(t_game *game) {
    int i = 0;
    t_ray_node* ray_list = NULL;
    ray_list = calculate_rays(game, ray_list);
    t_ray_node* current = ray_list;

    while (current != NULL) {
        t_texture *used_texture = &game->walltextures[current->ray.wall_face];
        render_ray(&game->img, current->ray, used_texture);
        current = current->next;
        i++;
    }
}


int	render(t_game *game)
{
	if (game->win_ptr == NULL)
		return (1);
	
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
