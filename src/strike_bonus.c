/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strike_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:43:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/02 17:50:00 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define STRIKE_WIDTH_FACTOR 0.1 // Adjust this value to change the overall width scaling

#define SHAKE_DURATION 30 // Number of frames the shake effect lasts
#define SHAKE_INTENSITY 0.3f // Maximum shake offset
#define BASE_PLAYER_HEIGHT 0.2f // Base player height
#define NUM_OFFSETS 13
#define NUM_NAPALM_OFFSETS 37

void randomize_barrage_location(t_game *game)
{
    // Assuming the game map is a grid with dimensions defined somewhere
    // If not, you'll need to add these to your game structure
    int map_width = game->map->width;  // Add this to your t_game struct if not present
    int map_height = game->map->height;  // Add this to your t_game struct if not present

    // Generate random x and y coordinates within the map bounds
    int new_x = random_int(game, map_width);
    int new_y = random_int(game, map_height);

    // Update the strike position
    game->strike[0].position.x = new_x;
    game->strike[0].position.y = new_y;

    // Optionally, you might want to ensure the new position is valid
    // (e.g., not inside a wall or outside the playable area)
    while (!is_valid_position(game, new_x, new_y))  // You'll need to implement is_valid_position
    {
        new_x = random_int(game, map_width);
        new_y = random_int(game, map_height);
        game->strike[0].position.x = new_x;
        game->strike[0].position.y = new_y;
    }

    // Optionally, reset any relevant strike parameters
    game->strike[0].frame_count = 0;
    game->strike[0].current_frame = 0;
    game->strike[0].is_active = 1;
    game->strike[0].is_launching = 1;

    // Debug output
    printf("New barrage location: (%d, %d)\n", new_x, new_y);
}

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



int get_next_airstrike_frame(t_strike *strike)
{
    strike[0].frame_count++;
    
    // Only change frame every AIRSTRIKE_ANIMATION_INTERVAL
    if (strike[0].frame_count % AIRSTRIKE_ANIMATION_INTERVAL != 0)
        return strike[0].current_frame;

    // Move to the next frame in the sequence
    strike[0].current_frame = (strike[0].current_frame + 1) % NUM_AIRSTRIKE_FRAMES;

    // If we've completed a full cycle, set is_active to 0
    if (strike[0].current_frame == 0)
    {
        strike[0].is_active = 0;
        strike[0].is_launching = 0;
    }
    // printf("Airstrike frame: %d, frame_count: %d\n", strike[0].current_frame, strike[0].frame_count);

    return strike[0].current_frame;
}


void render_ongoing_strike(t_game *game)
{
    if (!game->strike[0].is_active)
        return;

    int current_frame = get_next_airstrike_frame(game->strike);
    t_texture *strike_texture = &game->airstrike_textures[current_frame];

    // printf("render_ongoing_strike: Rendering strike frame %d, texture address: %p\n", current_frame, (void*)strike_texture);

    // Calculate screen shake offset
    float shake_offset = calculate_screen_shake(game, current_frame);
    // printf("render_ongoing_strike: shake_offset %f\n", shake_offset);

    // Apply screen shake to player height
    if (game->player->is_dead == 0)
        game->player->height = BASE_PLAYER_HEIGHT + shake_offset;

    // Define offsets for adjacent tiles
    // int offsets[NUM_OFFSETS][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}}; // Current tile and 3 adjacent


    int offsets[NUM_OFFSETS][2] =
    {
        {0, 0},  // Center tile
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},  // Adjacent tiles (up, down, left, right)
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1},  // Diagonal adjacent tiles
        {2, 0}, {-2, 0}, {0, 2}, {0, -2}  // Tiles 2 units away on x or y axis
    };
    for (int i = 0; i < NUM_OFFSETS; i++)
    {
        // printf("render_ongoing_strike: calcualting sprites positions for explosion %d\n", i);
        float spriteX, spriteY;
        calculate_sprite_position(game, 
                                  game->strike[0].position.x + offsets[i][0], 
                                  game->strike[0].position.y + offsets[i][1], 
                                  &spriteX, &spriteY);

        // printf("render_ongoing_strike: calcualting transform_sprite for explosion %d\n", i);
        float transformX, transformY;
        transform_sprite(game, spriteX, spriteY, &transformX, &transformY);
        // printf("render_ongoing_strike:  calculate_sprite_screen_x for explosion %d\n", i);

        int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

        int spriteHeight, drawStartY, drawEndY;
        // printf("render_ongoing_strike:  calculate_sprite_height for explosion %d\n", i);
        calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

        int spriteWidth, drawStartX, drawEndX;
        // printf("render_ongoing_strike:  calculate_sprite_width for explosion %d\n", i);
        calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

        // printf("Strike sprite dimensions for tile %d: X=%d-%d, Y=%d-%d\n", i, drawStartX, drawEndX, drawStartY, drawEndY);

        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            if (is_sprite_in_front(transformY, stripe, game->screen_width))
            {
        // printf("render_ongoing_strike:  draw_sprite_stripe for explosion %d\n", i);
                draw_sprite_stripe(game, strike_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
            }
        }
    }
}



void    render_strike(t_game *game)
{
    if (game->strike[0].is_launching)
        render_call_strike(game, game->strike[0].position);
    else if (game->strike[0].is_active)
        render_ongoing_strike(game);
}


int get_next_napalm_frame(t_strike *strike)
{
    strike[1].frame_count++;
    
    if (strike[1].frame_count % AIRSTRIKE_ANIMATION_INTERVAL != 0)
        return strike[1].current_frame;

    strike[1].current_frame = (strike[1].current_frame + 1) % NUM_NAPALM_FRAMES;

    // Remove the deactivation logic to keep the napalm effect active indefinitely
    // The is_active and is_launching flags will remain unchanged

    return strike[1].current_frame;
}

void render_ongoing_napalm(t_game *game)
{
    if (!game->strike[1].is_active)
        return;

    int current_frame = get_next_napalm_frame(game->strike);
    t_texture *napalm_texture = &game->napalm_textures[current_frame];

    float shake_offset = calculate_screen_shake(game, current_frame);

    if (game->player->is_dead == 0)
        game->player->height = BASE_PLAYER_HEIGHT + shake_offset;

    int offsets[NUM_NAPALM_OFFSETS][2] = {
        {0, 0},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
        {2, 0}, {-2, 0}, {0, 2}, {0, -2},
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
        {3, 0}, {-3, 0}, {0, 3}, {0, -3},
        {3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {1, 3}, {1, -3}, {-1, 3}, {-1, -3},
        {4, 0}, {-4, 0}, {0, 4}, {0, -4}
    };

    for (int i = 0; i < NUM_NAPALM_OFFSETS; i++)
    {
        float spriteX, spriteY;
        calculate_sprite_position(game, 
                                  game->strike[1].position.x + offsets[i][0], 
                                  game->strike[1].position.y + offsets[i][1], 
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
                draw_sprite_stripe(game, napalm_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
            }
        }
    }
}

void render_napalm(t_game *game)
{
    if (game->strike[1].is_launching)
        render_call_strike(game, game->strike[1].position);
    else if (game->strike[1].is_active)
        render_ongoing_napalm(game);
}


