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

// void update_gun_frame(t_game *game)
// {
//     static int frame_counter = 0;
//     const int frames_per_switch = 4; // Adjust this value to control the animation speed

//     if (frame_counter >= frames_per_switch)
//     {
//         game->current_gun_frame = (game->current_gun_frame + 1) % game->num_gun_frames;
//         frame_counter = 0;
//     }

//     frame_counter++;
// }

void scale_gun_textures(t_game *game)
{
    double scale_height = game->screen_height * 0.55;
    double scale_width = game->screen_width * 0.6;

    for (int i = 0; i < game->num_gun_frames; i++)
    {
        t_texture *gun_texture = &game->gun_textures[i];

        gun_texture->height = (int)scale_height;
        gun_texture->width = (int)(gun_texture->width * (scale_height / gun_texture->height));

        if (gun_texture->width > scale_width)
        {
            gun_texture->width = (int)scale_width;
            gun_texture->height = (int)(gun_texture->height * (scale_width / gun_texture->width));
        }
    }
}

void scale_shooting_textures(t_game *game)
{
    double scale_height = game->screen_height * 0.55;
    double scale_width = game->screen_width * 0.6;

    for (int i = 0; i < game->num_gun_frames; i++)
    {
        t_texture *gun_texture = &game->shooting_texture[i];

        gun_texture->height = (int)scale_height;
        gun_texture->width = (int)(gun_texture->width * (scale_height / gun_texture->height));

        if (gun_texture->width > scale_width)
        {
            gun_texture->width = (int)scale_width;
            gun_texture->height = (int)(gun_texture->height * (scale_width / gun_texture->width));
        }
    }
}

// void render_gun(t_game *game)
// {
//     t_texture *gun_texture;

//     if (game->is_shooting)
//     {
//         gun_texture = &game->shooting_texture[0];  // Assuming the shooting texture is at index 0
//     }
//     else
//     {
//         gun_texture = &game->gun_textures[game->current_gun_frame];
//     }

//     // Move the gun more to the right by adding an offset
//     int offset = gun_texture->width / 4; // Adjust this value to move the gun more or less
//     int start_x = game->screen_width - gun_texture->width + offset;
//     int start_y = game->screen_height - gun_texture->height;

//     for (int y = 0; y < gun_texture->height; y++)
//     {
//         for (int x = 0; x < gun_texture->width; x++)
//         {
//             // Only render if the pixel is within the screen bounds
//             if (start_x + x < game->screen_width)
//             {
//                 int tex_x = (x * gun_texture->width) / gun_texture->width;
//                 int tex_y = (y * gun_texture->height) / gun_texture->height;

//                 int color = *(int *)(gun_texture->data + (tex_y * gun_texture->tex_line_len + tex_x * (gun_texture->tex_bpp / 8)));

//                 if ((unsigned int)color != 0xFF000000) // Skip transparent pixels (assuming black is transparent)
//                     img_pix_put(&game->img, start_x + x, start_y + y, color);
//             }
//         }
//     }
// }


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
    const int num_shooting_frames = 4;  // Adjust this based on your actual number of shooting frames

    if (frame_counter >= frames_per_switch)
    {
        game->current_shooting_frame = (game->current_shooting_frame + 1) % num_shooting_frames;
        frame_counter = 0;
    }
    frame_counter++;
    // playAudioFileWithDelay("audio/gun01.wav", 0);

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

    if ((unsigned int)color != 0xFF000000) // Skip transparent pixels
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

