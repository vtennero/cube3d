/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:16:06 by root              #+#    #+#             */
/*   Updated: 2024/07/10 13:04:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void update_normal_gun_frame(t_game *game)
{
    static int frame_counter = 0;
    const int frames_per_switch = 4;

    if (frame_counter >= frames_per_switch)
    {
        game->current_gun_frame = (game->current_gun_frame + 1) % game->num_gun_frames;
        frame_counter = 0;
    }
    frame_counter++;
}

void update_shooting_gun_frame(t_game *game)
{
    static int frame_counter = 0;
    const int frames_per_switch = 4;
    const int num_shooting_frames = 4;

    if (frame_counter >= frames_per_switch)
    {
        game->current_shooting_frame = (game->current_shooting_frame + 1) % num_shooting_frames;
        frame_counter = 0;
    }
    frame_counter++;

}

t_texture *select_gun_texture(t_game *game)
{
    if (game->is_shooting)
    {
        return &game->shooting_texture[game->current_shooting_frame];
    }
    else
    {
        return &game->gun_textures[game->current_gun_frame];
    }
}

void calculate_gun_position(t_game *game, t_texture *gun_texture, int *start_x, int *start_y)
{
    int offset = gun_texture->width / 4;
    *start_x = game->screen_width - gun_texture->width + offset;
    *start_y = game->screen_height - gun_texture->height;
}

void draw_gun_pixel(t_game *game, t_texture *gun_texture, int start_x, int start_y, int x, int y)
{
    int tex_x = x;
    int tex_y = y;
    int color = *(int *)(gun_texture->data + (tex_y * gun_texture->tex_line_len + tex_x * (gun_texture->tex_bpp / 8)));

    if ((unsigned int)color != 0xFF000000)
        img_pix_put(&game->img, start_x + x, start_y + y, color);
}

void update_gun_state(t_game *game)
{
    if (game->is_shooting)
    {
        update_shooting_gun_frame(game);
    }
    else
    {
        if(game->is_moving_fwd)
            update_normal_gun_frame(game);
    }
}

void render_gun(t_game *game)
{
    t_texture *gun_texture = select_gun_texture(game);
    int start_x, start_y;
    calculate_gun_position(game, gun_texture, &start_x, &start_y);

    for (int y = 0; y < gun_texture->height; y++)
    {
        for (int x = 0; x < gun_texture->width; x++)
        {
            if (start_x + x < game->screen_width)
            {
                draw_gun_pixel(game, gun_texture, start_x, start_y, x, y);
            }
        }
    }
}

