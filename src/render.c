/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/09 22:43:37 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define MLX_SUCCESS 0
#define MLX_ERROR -1
#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF


int get_texture_color(t_texture *texture, int x, int y) {
    // printf("Getting texture color at (X: %d, Y: %d)\n", x, y);
    int pixel_pos = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
    int color = *(int *)(texture->data + pixel_pos);
    return color;
}



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



// void render_ray(t_img *img, t_ray ray, t_texture *texture) {

// 	// printf("Screen bpp: %d, Texture bpp: %d\n", img->bpp, texture->tex_bpp);
// 	// printf("Screen endian: %d, Texture endian: %d\n", img->endian, texture->tex_endian);

//     if (img->bpp != texture->tex_bpp || img->endian != texture->tex_endian) {
//         fprintf(stderr, "Error: Texture and screen format mismatch\n");
//         exit(EXIT_FAILURE);
//     }



//     // printf("Rendering ray at screen position X: %d\n", ray.x);

//     int y = ray.draw_start;
//     while (y < ray.draw_end) {
//         // printf("Rendering pixel at Y: %d\n", y);
//         int texY = ((y - ray.draw_start) * texture->height) / ray.lineHeight;
//         int color = get_texture_color(texture, ray.texX, texY);
//         img_pix_put(img, ray.x, y, color);
//         y++;
//     }
// }

void render_ray(t_img *img, t_ray ray, t_texture *texture, int rayIndex, int totalRays) {
    if (img->bpp != texture->tex_bpp || img->endian != texture->tex_endian) {
        fprintf(stderr, "Error: Texture and screen format mismatch\n");
        exit(EXIT_FAILURE);
    }

    // Calculate texture X coordinate for the ray
    // Assuming texture should wrap around completely for all rays across the screen
    int texX = (rayIndex * texture->width) / totalRays;
    texX %= texture->width;  // Wrap around by using modulo operation

    int y = ray.draw_start;
    while (y < ray.draw_end) {
        int texY = ((y - ray.draw_start) * texture->height) / ray.lineHeight;
        texY %= texture->height;  // Optionally ensure texY also wraps around if needed
        int color = get_texture_color(texture, texX, texY);
        img_pix_put(img, ray.x, y, color);
        y++;
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



// void render_ray_list(t_game *game)
// {
// 	int	i = 0;
//     // Initialize the list and calculate rays
// 	printf("render ray list STARTS\n");
//     t_ray_node* ray_list = NULL;
//     ray_list = calculate_rays(game, ray_list);

// 	debug_print_rays(ray_list);

//     t_ray_node* current = ray_list;
//     // printf("Starting to render ray list.\n");
//     while (current != NULL)
// 	{
// 		// printf("i = %d\n", i);
//         t_texture *used_texture = &game->walltextures[current->ray.wall_face];


//         render_ray(&game->img, current->ray, used_texture);
//         current = current->next;
// 		i++;
// }
// 	printf("render ray list ENDS\n");
// }


void render_ray_list(t_game *game) {
    int i = 0;
	// printf("render ray list STARTS\n");
    t_ray_node* ray_list = NULL;
    ray_list = calculate_rays(game, ray_list);
    t_ray_node* current = ray_list;
    int totalRays = 800;  // Or however many rays you are calculating

    while (current != NULL) {
        t_texture *used_texture = &game->walltextures[current->ray.wall_face];
        render_ray(&game->img, current->ray, used_texture, i, totalRays);
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
	// printf("RENDERING STARTS\n");
	render_sky(&game->img, 0x87CEEB);
	render_floor(&game->img, 0x8B4513);
	render_ray_list(game);

	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);

	// printf("RENDERING ENDS\n");
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
