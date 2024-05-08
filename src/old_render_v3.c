/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_render_v3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/08 10:37:38 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// v3
// uses image buffer
// uses colors instead of textures
void draw_vertical_slice_from_ray(void *mlx_ptr, void *win_ptr, char *img_data, int img_width, int img_height, int bpp, int size_line, t_ray ray)
{
    (void)mlx_ptr;
    (void)win_ptr;
    printf("Ray.x: %d, Draw Start: %d, Draw End: %d\n", ray.x, ray.draw_start, ray.draw_end);

    if (ray.draw_start == ray.draw_end) {
        printf("No vertical slice to draw, draw_start == draw_end\n");
        return;
    }

    for (int screenY = ray.draw_start; screenY < ray.draw_end; screenY++) {
        double texPos = (screenY - ray.draw_start) * img_height / (double)(ray.draw_end - ray.draw_start);
        int texY = (int)texPos % img_height;
        int texX = (int)((ray.x * img_width / 800.0)) % img_width;

        int pixel_pos = (texX * (bpp / 8)) + (texY * size_line);
        int color = *(int *)(img_data + pixel_pos);

        int img_pixel_pos = (ray.x * (bpp / 8)) + (screenY * size_line);
        *(int *)(img_data + img_pixel_pos) = color;  // Original color write

        // Test with a fixed color to ensure loop is working
        *(int *)(img_data + img_pixel_pos) = 0x00FF0000;  // Writing red to verify pixel writes
    }
}






void render_ray_list(t_ray_node* head, t_game *game)
{
    int bpp, size_line, endian;
    // Create a new image buffer for the entire screen
    void *img = mlx_new_image(game->mlx_ptr, game->screen_width, game->screen_height);
    char *img_data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

    t_ray_node *current = head;
    while (current != NULL) {
        if (current->ray.x >= 0 && current->ray.x < game->screen_width) {
            draw_vertical_slice_from_ray(game->mlx_ptr, game->win_ptr, img_data, game->screen_width, game->screen_height, bpp, size_line, current->ray);
        }
        current = current->next;
    }

    // Put the composed image onto the window
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, 0, 0);
    mlx_destroy_image(game->mlx_ptr, img);
}


