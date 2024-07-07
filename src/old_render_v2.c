/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_render_v2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/08 10:37:35 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


// v2 works
// uses pixel put
// uses textures
void draw_vertical_slice_from_ray(void *mlx_ptr, void *win_ptr, char *img_data, int img_width, int img_height, int bpp, int size_line, t_ray ray)
{
	// printf("draw_vertical_slice_from_ray: START\n");
    // if (!ray.hit) return; // Only draw if there was a wall hit
	printf("draw_vertical_slice_from_ray: img_width = %d, img_height = %d bpp = %d size_line = %d img_data= |%s|\n", img_width, img_height, bpp, size_line, img_data);
	// printf("First byte of img_data: %02x\n", (unsigned char)img_data[0]);

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



void render_ray_list(t_ray_node* head, t_game *game)
{
    int img_width, img_height, bpp, size_line, endian;
    char *img_data;
    int current_image = -1;

    // Loop through linked list of rays and render each
    for (t_ray_node *current = head; current != NULL; current = current->next)
    {
        if (current_image != current->ray.wall_face)
        {
            current_image = current->ray.wall_face;
            t_texture texture = game->walltextures[current_image];

            // Ensure the texture image is valid
            if (!texture.img) {
                printf("Error: Texture not loaded for face %d\n", current_image);
                continue;
            }
            img_width = texture.width;
            img_height = texture.height;
            img_data = mlx_get_data_addr(texture.img, &bpp, &size_line, &endian);
        }

        draw_vertical_slice_from_ray(game->mlx_ptr, game->win_ptr, img_data, img_width, img_height, bpp, size_line, current->ray);
    }
}


