/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:42:52 by root              #+#    #+#             */
/*   Updated: 2024/07/09 18:51:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int get_texture_color(t_texture *texture, int x, int y)
{
    // printf("Getting texture color at (X: %d, Y: %d)\n", x, y);
    int pixel_pos = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
    int color = *(int *)(texture->data + pixel_pos);
    return color;
}

void render_ray(t_img *img, t_ray ray, t_texture *texture, t_game *game)
{
    int pitch_offset = (int)(game->player->pitch * game->screen_height);
    double step = 1.0 * texture->height / ray.lineHeight;
    
    // Adjust starting texture position based on pitch
    double texPos = (ray.draw_start - pitch_offset - game->screen_height / 2 + ray.lineHeight / 2) * step;

    for (int y = ray.draw_start; y < ray.draw_end; y++)
    {
        int texY = (int)texPos & (texture->height - 1);
        texPos += step;
        int color = get_texture_color(texture, ray.texX, texY);
        img_pix_put(img, ray.x, y, color);
    }
}

void render_ray_list(t_game *game)
{
    int i = 0;
    t_ray_node *ray_list = NULL;
    ray_list = calculate_rays(game, ray_list);
    t_ray_node *current = ray_list;

    while (current != NULL)
    {
        t_texture *used_texture = &game->walltextures[current->ray.wall_face];
        render_ray(&game->img, current->ray, used_texture, game);  // Updated function call
        current = current->next;
        i++;
    }
}