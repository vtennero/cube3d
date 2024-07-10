/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_render_gun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:16:06 by root              #+#    #+#             */
/*   Updated: 2024/07/10 13:00:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void load_gun_texture(t_game *game, char *path)
{
    t_texture *gun_texture = &game->gun_texture;

    gun_texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &gun_texture->width, &gun_texture->height);
    if (gun_texture->img == NULL)
    {
        fprintf(stderr, "Error: Could not load gun texture: %s\n", path);
        exit(1);
    }
    gun_texture->data = mlx_get_data_addr(gun_texture->img, &gun_texture->tex_bpp, &gun_texture->tex_line_len, &gun_texture->tex_endian);
}

void scale_gun_texture(t_game *game)
{
    t_texture *gun_texture = &game->gun_texture;

    double scale_height = game->screen_height * 0.65;
    double scale_width = game->screen_width * 0.7;

    gun_texture->height = (int)scale_height;
    gun_texture->width = (int)(gun_texture->width * (scale_height / gun_texture->height));

    if (gun_texture->width > scale_width)
    {
        gun_texture->width = (int)scale_width;
        gun_texture->height = (int)(gun_texture->height * (scale_width / gun_texture->width));
    }
}

void render_gun(t_game *game)
{
    t_texture *gun_texture = &game->gun_texture;

    int start_x = game->screen_width - gun_texture->width;
    int start_y = game->screen_height - gun_texture->height;

    for (int y = 0; y < gun_texture->height; y++)
    {
        for (int x = 0; x < gun_texture->width; x++)
        {
            int tex_x = (x * gun_texture->width) / gun_texture->width;
            int tex_y = (y * gun_texture->height) / gun_texture->height;

            int color = *(int *)(gun_texture->data + (tex_y * gun_texture->tex_line_len + tex_x * (gun_texture->tex_bpp / 8)));

            if ((unsigned int)color != 0xFF000000) // Skip transparent pixels (assuming black is transparent)
            {
                img_pix_put(&game->img, start_x + x, start_y + y, color);
            }
        }
    }
}
