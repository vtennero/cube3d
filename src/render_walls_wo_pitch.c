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

void render_ray(t_img *img, t_ray ray, t_texture *texture)
{
    if (img->bpp != texture->tex_bpp || img->endian != texture->tex_endian)
    {
        fprintf(stderr, "Error: Texture and screen format mismatch\n");
        exit(EXIT_FAILURE);
    }

    // Use doubles for increased precision
    double wallX = ray.wallX;
    int texX = (int)(wallX * (double)(texture->width));
    if (ray.side == 0 && ray.rayDirX > 0)
        texX = texture->width - texX - 1;
    if (ray.side == 1 && ray.rayDirY < 0)
        texX = texture->width - texX - 1;

    // Calculate the height of the wall slice to be drawn
    int lineHeight = (int)(DEFAULT_S_HEIGHT / ray.perpWallDist);

    // Calculate the lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + DEFAULT_S_HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;
    int drawEnd = lineHeight / 2 + DEFAULT_S_HEIGHT / 2;
    if (drawEnd >= DEFAULT_S_HEIGHT)
        drawEnd = DEFAULT_S_HEIGHT - 1;

    // Texture step and initial texture position
    double step = 1.0 * texture->height / lineHeight;
    double texPos = (drawStart - DEFAULT_S_HEIGHT / 2 + lineHeight / 2) * step;

    for (int y = drawStart; y < drawEnd; y++)
    {
        int texY = (int)texPos & (texture->height - 1);
        texPos += step;
        int color = get_texture_color(texture, texX, texY);
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
        render_ray(&game->img, current->ray, used_texture);
        current = current->next;
        i++;
    }
}