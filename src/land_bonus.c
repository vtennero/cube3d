/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   land_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:32:25 by toto              #+#    #+#             */
/*   Updated: 2024/08/12 18:46:34 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void render_land(t_game *game)
{
    int frame_to_render = get_current_frame(&game->opening_start_time);
    printf("render land frame to render %d\n", frame_to_render);
    t_texture *land_texture = &game->land_texture[frame_to_render];

    if (land_texture->img == NULL)
    {
        printf("Error: land texture not loaded\n");
        return;
    }

    // Render the frame
    for (int y = 0; y < game->screen_height; y++)
    {
        // printf("rendering frame\n");
        for (int x = 0; x < game->screen_width; x++)
        {
            int tex_x = x * land_texture->width / game->screen_width;
            int tex_y = y * land_texture->height / game->screen_height;
            int color = get_texture_color(land_texture, tex_x, tex_y);
            img_pix_put(&game->img, x, y, color);
        }
    }

    // Update game state
    game->current_frame = frame_to_render;

    // Check if we've reached the last frame
    if (frame_to_render == MAX_LAND_TEXTURES - 1)
    {
            game->game_sequence = 3;
            game->current_frame = 0;
			playAudioFileWithDelay("audio/land.mp3", 0);

    }
}