/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strike_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:43:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/29 14:05:49 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define STRIKE_WIDTH_FACTOR 0.1 // Adjust this value to change the overall width scaling

#define SHAKE_DURATION 30 // Number of frames the shake effect lasts
#define SHAKE_INTENSITY 0.3f // Maximum shake offset
#define BASE_PLAYER_HEIGHT 0.2f // Base player height

float calculate_screen_shake(t_game *game, int current_frame)
{
    if (current_frame >= SHAKE_DURATION)
        return 0.0f;

    // Use the random number generator for unpredictable shake
    float random_offset = (float)random_int(game, 1000) / 1000.0f;

    // Calculate a decreasing intensity over time
    float intensity = SHAKE_INTENSITY * (1.0f - (float)current_frame / SHAKE_DURATION);

    // Use a sine wave for a bouncing effect
    float shake = sinf(current_frame * 0.5f) * intensity;

    // Combine the sine wave with the random offset for more chaotic movement
    return shake * random_offset;
}


void draw_strike_stripe(t_game *game, int stripe, int drawStartY, int drawEndY, float distance)
{
    (void)drawStartY;
    // Calculate the total width based on distance
    int total_width = (int)(STRIKE_WIDTH_FACTOR * game->screen_width / distance);
    // Ensure the total width is at least 3 pixels
    total_width = (total_width < 3) ? 3 : total_width;
    
    // Make the white part wider
    int white_width = total_width / 2;
    // int red_width = (total_width - white_width) / 2;

    // printf("Drawing strike: stripe=%d, drawStartY=%d, drawEndY=%d, total_width=%d\n", 
    //        stripe, drawStartY, drawEndY, total_width);

    for (int y = 0; y < drawEndY; y++)
    {
        for (int i = -total_width/2; i < total_width/2; i++)
        {
            int x = stripe + i;
            if (x >= 0 && x < game->screen_width)
            {
                int color;
                // char* color_name;
                if (i >= -white_width/2 && i < white_width/2)
                {
                    color = 0xFFFFFF; // White in the middle
                    // color_name = "White";
                }
                else
                {
                    // Calculate gradient for red
                    float gradient = 1.0f - (float)abs(i) / (total_width/2);
                    int red_value = 128 + (int)(127 * gradient); // Range from 128 to 255
                    color = (red_value << 16) | 0x000000; // Only red channel
                    // color_name = "Red (Gradient)";
                }
                img_pix_put(&game->img, x, y, color);
                
                // Print debug info for every 50th pixel to avoid overwhelming output
                // if (y % 50 == 0 && i == 0)
                // {
                //     printf("Drawing pixel: x=%d, y=%d, color=%s, total_width=%d\n", x, y, color_name, total_width);
                // }
            }
        }
    }
}




void render_call_strike(t_game *game, t_vector2d position)
{
    float spriteX, spriteY;
    calculate_sprite_position(game, position.x, position.y, &spriteX, &spriteY);

    float transformX, transformY;
    transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

    int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

    int spriteHeight, drawStartY, drawEndY;
    calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

    // Calculate distance to player
    float dx = position.x - game->player->position.x;
    float dy = position.y - game->player->position.y;
    float distance = sqrt(dx * dx + dy * dy);

    // We only need to render a single stripe for the strike
    int stripe = spriteScreenX;
    if (is_sprite_in_front(transformY, stripe, game->screen_width))
    {
        draw_strike_stripe(game, stripe, drawStartY, drawEndY, distance);
    }
}

void update_airstrike_frames(t_strike *strike)
{
    int all_explosions_complete = 1;

    for (int i = 0; i < NUM_EXPLOSIONS; i++)
    {
        strike->frame_count[i]++;
        
        // Only change frame every AIRSTRIKE_ANIMATION_INTERVAL
        if (strike->frame_count[i] % AIRSTRIKE_ANIMATION_INTERVAL == 0)
        {
            // Move to the next frame in the sequence, wrapping around to 0 when we reach NUM_AIRSTRIKE_FRAMES
            strike->current_frame[i] = (strike->current_frame[i] + 1) % NUM_AIRSTRIKE_FRAMES;
        }

        // If this explosion hasn't completed its animation, mark that not all explosions are complete
        if (strike->frame_count[i] < NUM_AIRSTRIKE_FRAMES * AIRSTRIKE_ANIMATION_INTERVAL)
            all_explosions_complete = 0;
    }

    // If we've completed all explosions, set is_active to 0
    if (all_explosions_complete)
    {
        strike->is_active = 0;
        strike->is_launching = 0;
    }
}

void render_ongoing_strike(t_game *game)
{
    if (!game->strike->is_active)
        return;

    update_airstrike_frames(game->strike);

    // Define offsets for adjacent tiles
    int offsets[4][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}}; // Current tile and 3 adjacent

    for (int explosion = 0; explosion < NUM_EXPLOSIONS; explosion++)
    {
        int current_frame = game->strike->current_frame[explosion];
        t_texture *strike_texture = &game->airstrike_textures[current_frame];

        for (int i = 0; i < 4; i++)
        {
            float spriteX, spriteY;
            calculate_sprite_position(game, 
                                      game->strike->position.x + offsets[i][0],
                                      game->strike->position.y + offsets[i][1],
                                      &spriteX, &spriteY);

            float transformX, transformY;
            transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

            int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

            int spriteHeight, drawStartY, drawEndY;
            calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

            int spriteWidth, drawStartX, drawEndX;
            calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

            for (int stripe = drawStartX; stripe < drawEndX; stripe++)
            {
                if (is_sprite_in_front(transformY, stripe, game->screen_width))
                {
                    draw_sprite_stripe(game, strike_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
                }
            }
        }
    }
}

void    render_strike(t_game *game)
{
    if (game->strike->is_launching)
        render_call_strike(game, game->strike->position);
    else if (game->strike->is_active)
        render_ongoing_strike(game);
}