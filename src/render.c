/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/08 11:52:18 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define MLX_SUCCESS 0
#define MLX_ERROR -1
#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

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


// v1
// void render_ray(t_img *img, t_ray ray)
// {
//     int y = ray.draw_start;
//     while (y < ray.draw_end)
//     {
//         img_pix_put(img, ray.x, y, ray.color);
//         y++;
//     }
// }

void render_ray(t_img *img, t_ray ray, unsigned char *texture_data, int img_width, int img_height)
{
    int bpp = img->bpp;
    int size_line = img->line_len;

    for (int screenY = ray.draw_start; screenY < ray.draw_end; screenY++) {
        double texPos = (screenY - ray.draw_start) * img_height / (double)(ray.draw_end - ray.draw_start);
        int texY = (int)texPos % img_height;
        int texX = (int)((ray.x * img_width / 800.0)) % img_width;

        // Calculate the position in the texture data array
        int tex_pixel_pos = (texX * (bpp / 8)) + (texY * size_line);
        int color = *(int *)(texture_data + tex_pixel_pos);

        // Calculate the position in the image buffer
        int img_pixel_pos = (ray.x * (bpp / 8)) + (screenY * size_line);
        
        // Update the image buffer directly
        *(int *)(img->addr + img_pixel_pos) = color;
    }
}


// Function to render the sky (upper half)
void render_sky(t_img *img, int sky_color) {
    int i, j;
    for (i = 0; i < DEFAULT_S_HEIGHT / 2; ++i) {
        for (j = 0; j < DEFAULT_S_WIDTH; ++j) {
            img_pix_put(img, j, i, sky_color);
        }
    }
}

// Function to render the floor (lower half)
void render_floor(t_img *img, int floor_color) {
    int i, j;
    for (i = DEFAULT_S_HEIGHT / 2; i < DEFAULT_S_HEIGHT; ++i) {
        for (j = 0; j < DEFAULT_S_WIDTH; ++j) {
            img_pix_put(img, j, i, floor_color);
        }
    }
}

// v1
// void render_ray_list(t_game *game)
// {
//     // Initialize the list and calculate rays
//     t_ray_node* ray_list = NULL;
//     ray_list = calculate_rays(game, ray_list);

//     // Traverse through the linked list and render each ray
//     t_ray_node* current = ray_list;
//     while (current != NULL)
//     {
//         render_ray(&game->img, current->ray);
//         current = current->next;
//     }

//     // Assuming proper freeing is done inside calculate_rays or elsewhere
// }

void render_ray_list(t_game *game, unsigned char *texture_data, int tex_width, int tex_height)
{
    // Initialize the list and calculate rays
    t_ray_node* ray_list = NULL;
    ray_list = calculate_rays(game, ray_list);

    // Traverse through the linked list and render each ray
    t_ray_node* current = ray_list;
    while (current != NULL)
    {
        render_ray(&game->img, current->ray, texture_data, tex_width, tex_height);
        current = current->next;
    }

    // Assuming proper freeing is done inside calculate_rays or elsewhere
}



int	render(t_game *game)
{
	if (game->win_ptr == NULL)
		return (1);




	// Rendering elements onto the game image
	// render_background(&game->img, WHITE_PIXEL); // Uncomment if background needs to be rendered
	render_sky(&game->img, 0x87CEEB);
	render_floor(&game->img, 0x8B4513);
	// render_rect(&game->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL}); // Uncomment for rectangle
	// render_rect(&game->img, (t_rect){0, 0, 100, 100, RED_PIXEL}); // Uncomment for another rectangle

    // // Example ray (adjust properties according to your actual game needs)
    // t_ray example_ray;
    // example_ray.x = 300; // The x-position on the screen where the ray will be drawn
    // example_ray.draw_start = 50; // The starting y-position of the ray's line
    // example_ray.draw_end = 250; // The ending y-position of the ray's line
    // example_ray.color = GREEN_PIXEL; // The color of the ray

    // // Draw the ray onto the image buffer
    // render_ray(&game->img, example_ray);
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

	/* Setup hooks */
	game->img.mlx_img = mlx_new_image(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp,
			&game->img.line_len, &game->img.endian);

	mlx_loop_hook(game->mlx_ptr, &render, game);
	// mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_keypress, game);

	mlx_loop(game->mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);

	return (0);
}