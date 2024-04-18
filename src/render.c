/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/18 12:05:34 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// Initialize MiniLibX, window, and image buffer
// void setup_mlx(t_game* game);

// // Main rendering loop
// void render_loop(t_game* game);

// // Draw a single frame
// void render_frame(t_game* game);

// // Cleanup resources
// void cleanup(t_game* game);

void draw_vertical_slice_from_ray(void *mlx_ptr, void *win_ptr, char *img_data, int img_width, int img_height, int bpp, int size_line, t_ray ray)
{
	// printf("draw_vertical_slice_from_ray: START\n");
    // if (!ray.hit) return; // Only draw if there was a wall hit

    for (int screenY = ray.draw_start; screenY < ray.draw_end; screenY++) {
        double texPos = (screenY - ray.draw_start) * img_height / (double)(ray.draw_end - ray.draw_start);
        int texY = (int)texPos % img_height;
        int texX = (int)((ray.x * img_width / 800.0)) % img_width;

        // Calculate the position in the image data array
        int pixel_pos = (texX * (bpp / 8)) + (texY * size_line);

        // Extract the color of each pixel
        int color = *(int *)(img_data + pixel_pos);

        // Put the pixel on the window at the scaled position
        mlx_pixel_put(mlx_ptr, win_ptr, ray.x, screenY, color);
    }
	// printf("draw_vertical_slice_from_ray: END\n");

}

// void	*calc_texture(t_ray ray, void *mlx_ptr, int *img_width, int *img_height)
// {
//     void *img_ptr;

// 	img_ptr = NULL;
// 	if (ray.wall_face == 1) {
// 		img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/eagle.xpm", &img_width, &img_height);
// 	} else if (ray.wall_face == 2) {
// 		img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/bluestone.xpm", &img_width, &img_height);
// 	} else if (ray.wall_face == 3) {
// 		img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/greystone.xpm", &img_width, &img_height);
// 	} else if (ray.wall_face == 4) {
// 		img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/wood.xpm", &img_width, &img_height);
// 	} else {
// 		img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/eagle.xpm", &img_width, &img_height);
// 	}
// 	return (img_ptr);
// }

void render_ray_list(t_ray_node* head, void *mlx_ptr, void *win_ptr)
{
    void *img_ptr;
    int img_width, img_height;
    char *img_data;
    int bpp, size_line, endian;
	int	current_image;

	current_image = -1;
    // Load an XPM file as an image


    // Example linked list of rays (normally you would populate this list)
    // t_ray_node *head = NULL; // Populate this list with real data in practice

    // Loop through linked list of rays and render each
    for (t_ray_node *current = head; current != NULL; current = current->next)
	{
		if (current_image != current->ray.wall_face)
		{
			current_image = current->ray.wall_face;
			// img_ptr = calc_texture(current->ray, mlx_ptr, &img_width, &img_height);
			if (current->ray.wall_face == 1) {
				img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/eagle.xpm", &img_width, &img_height);
			} else if (current->ray.wall_face == 2) {
				img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/bluestone.xpm", &img_width, &img_height);
			} else if (current->ray.wall_face == 3) {
				img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/greystone.xpm", &img_width, &img_height);
			} else if (current->ray.wall_face == 4) {
				img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/wood.xpm", &img_width, &img_height);
			} else {
				img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/eagle.xpm", &img_width, &img_height);
			}
			// img_ptr = mlx_xpm_file_to_image(mlx_ptr, "textures/eagle.xpm", &img_width, &img_height);
			if (!img_ptr) {
				printf("Error loading XPM file\n");
				return ;
			}
			// printf("render_ray_list: image loaded\n");
			// Get the image data from the image pointer
			img_data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
		}

        draw_vertical_slice_from_ray(mlx_ptr, win_ptr, img_data, img_width, img_height, bpp, size_line, current->ray);
    }

}