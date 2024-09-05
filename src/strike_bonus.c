/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strike_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:43:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/05 12:46:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define STRIKE_WIDTH_FACTOR 0.1 // Adjust this value to change the overall width scaling

#define SHAKE_DURATION 30 // Number of frames the shake effect lasts
#define SHAKE_INTENSITY 0.3f // Maximum shake offset
#define BASE_PLAYER_HEIGHT 0.2f // Base player height
#define NUM_OFFSETS 13
#define NUM_NAPALM_OFFSETS 37



float calculate_screen_shake(t_game *game, int current_frame)
{
    if (current_frame >= SHAKE_DURATION || game->player->is_dead == 1)
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


// int get_next_napalm_frame(t_strike *strike)
// {
//     strike[1].frame_count++;
    
//     if (strike[1].frame_count % AIRSTRIKE_ANIMATION_INTERVAL != 0)
//         return strike[1].current_frame;

//     strike[1].current_frame = (strike[1].current_frame + 1) % NUM_NAPALM_FRAMES;

//     // Remove the deactivation logic to keep the napalm effect active indefinitely
//     // The is_active and is_launching flags will remain unchanged

//     return strike[1].current_frame;
// }

// void render_ongoing_napalm(t_game *game)
// {
//     if (!game->strike[1].is_active)
//         return;

//     int current_frame = get_next_napalm_frame(game->strike);
//     t_texture *napalm_texture = &game->napalm_textures[current_frame];

//     float shake_offset = calculate_screen_shake(game, current_frame);

//     if (game->player->is_dead == 0)
//         game->player->height = BASE_PLAYER_HEIGHT + shake_offset;

//     int offsets[NUM_NAPALM_OFFSETS][2] = {
//         {0, 0},
//         {1, 0}, {-1, 0}, {0, 1}, {0, -1},
//         {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
//         {2, 0}, {-2, 0}, {0, 2}, {0, -2},
//         {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
//         {3, 0}, {-3, 0}, {0, 3}, {0, -3},
//         {3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {1, 3}, {1, -3}, {-1, 3}, {-1, -3},
//         {4, 0}, {-4, 0}, {0, 4}, {0, -4}
//     };

//     for (int i = 0; i < NUM_NAPALM_OFFSETS; i++)
//     {
//         float spriteX, spriteY;
//         calculate_sprite_position(game, 
//                                   game->strike[1].position.x + offsets[i][0], 
//                                   game->strike[1].position.y + offsets[i][1], 
//                                   &spriteX, &spriteY);

//         float transformX, transformY;
//         transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

//         int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

//         int spriteHeight, drawStartY, drawEndY;
//         calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

//         int spriteWidth, drawStartX, drawEndX;
//         calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

//         for (int stripe = drawStartX; stripe < drawEndX; stripe++)
//         {
//             if (is_sprite_in_front(transformY, stripe, game->screen_width))
//             {
//                 draw_sprite_stripe(game, napalm_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
//             }
//         }
//     }
// }

// void render_napalm(t_game *game)
// {
//     if (game->strike[1].is_launching)
//         render_call_strike(game, game->strike[1].position);
//     else if (game->strike[1].is_active)
//         render_ongoing_napalm(game);
// }

int get_next_napalm_frame(t_strike *strike)
{
    strike[1].frame_count++;
    
    if (strike[1].frame_count % AIRSTRIKE_ANIMATION_INTERVAL != 0)
        return strike[1].current_frame;

    strike[1].current_frame = (strike[1].current_frame + 1) % NUM_NAPALM_FRAMES;

    // Set is_animating to false after the first full animation cycle
    if (strike[1].current_frame == 0)
        strike[1].is_animating = 0;

    return strike[1].current_frame;
}

void render_ongoing_napalm(t_game *game)
{
    if (!game->strike[1].is_active)
        return;

    int current_frame = get_next_napalm_frame(game->strike);
    t_texture *napalm_texture = &game->napalm_textures[current_frame];

    // Only calculate and apply screen shake if is_animating is true
    if (game->strike[1].is_animating)
    {
        float shake_offset = calculate_screen_shake(game, current_frame);

        if (game->player->is_dead == 0)
            game->player->height = BASE_PLAYER_HEIGHT + shake_offset;
    }
    else
    {
        // Reset player height to base height when not shaking
        if (game->player->is_dead == 0)
            game->player->height = BASE_PLAYER_HEIGHT;
    }

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
    {
        render_call_strike(game, game->strike[1].position);
        game->strike[1].is_animating = 1; // Start animating when launching
    }
    else if (game->strike[1].is_active)
    {
        render_ongoing_napalm(game);
    }
}


void randomize_barrage_location(t_game *game)
{
    // Assuming the game map is a grid with dimensions defined somewhere
    int map_width = game->map->width;
    int map_height = game->map->height;

    // Define the proximity radius (adjust this value as needed)
    float proximity_radius = 10.0f; // For example, 5 units radius

    // Generate random angle and distance within the proximity radius
    float angle = random_float(game) * 2 * M_PI; // Random angle between 0 and 2π
    float distance = random_float(game) * proximity_radius; // Random distance within the radius

    // Calculate new position relative to base position
    float delta_x = cosf(angle) * distance;
    float delta_y = sinf(angle) * distance;

    // Calculate new absolute position
    int new_x = (int)(game->strike[2].base_position.x + delta_x);
    int new_y = (int)(game->strike[2].base_position.y + delta_y);

    // Ensure the new position is within map bounds
    new_x = fmax(0, fmin(new_x, map_width - 1));
    new_y = fmax(0, fmin(new_y, map_height - 1));

    // Update the strike position (not the base position)
    game->strike[2].position.x = new_x;
    game->strike[2].position.y = new_y;

    // Ensure the new position is valid
    int attempts = 0;
    while (!is_valid_location(game, new_x, new_y) && attempts < 10)
    {
        // If not valid, try a new random position
        angle = random_float(game) * 2 * M_PI;
        distance = random_float(game) * proximity_radius;
        delta_x = cosf(angle) * distance;
        delta_y = sinf(angle) * distance;
        new_x = (int)(game->strike[2].base_position.x + delta_x);
        new_y = (int)(game->strike[2].base_position.y + delta_y);
        new_x = fmax(0, fmin(new_x, map_width - 1));
        new_y = fmax(0, fmin(new_y, map_height - 1));
        game->strike[2].position.x = new_x;
        game->strike[2].position.y = new_y;
        attempts++;
    }

    // Reset relevant strike parameters
    game->strike[2].frame_count = 0;
    game->strike[2].current_frame = 0;
    game->strike[2].is_active = 1;
    game->strike[2].is_launching = 1;
    game->strike[2].is_animating = 0;
    game->strike[2].delay_frames = 0;
    game->strike[2].delay_duration = 60 * 2; // 3 seconds at 60 FPS, adjust as needed

    // Debug output
    printf("New barrage location: (%d, %d), Base position: (%f, %f)\n", 
           new_x, new_y, 
           game->strike[2].base_position.x, 
           game->strike[2].base_position.y);
}

void render_call_barrage(t_game *game, t_vector2d position)
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



int get_next_barrage_frame(t_strike *strike)
{
    strike->frame_count++;
    
    // Only change frame every AIRSTRIKE_ANIMATION_INTERVAL
    if (strike->frame_count % AIRSTRIKE_ANIMATION_INTERVAL == 0)
    {
        strike->current_frame = (strike->current_frame + 1) % NUM_AIRSTRIKE_FRAMES;
    }

    return strike->current_frame;
}

void render_ongoing_barrage(t_game *game)
{
    // printf("render_ongoing_barrage: Start\n");
    if (!game->strike[2].is_active)
    {
        // printf("render_ongoing_barrage: Strike not active, returning\n");
        return;
    }

    int current_frame = get_next_barrage_frame(&game->strike[2]);
    // printf("render_ongoing_barrage: Current frame: %d\n", current_frame);

    t_texture *strike_texture = &game->airstrike_textures[current_frame];
    // printf("render_ongoing_barrage: Strike texture address: %p\n", (void*)strike_texture);
    printf("render_ongoing_barrage: current_frame: %d\n", current_frame);

    // Calculate screen shake offset
    float shake_offset = calculate_screen_shake(game, current_frame);
    // printf("render_ongoing_barrage: Shake offset: %f\n", shake_offset);

    // Apply screen shake to player height
    if (game->player->is_dead == 0)
    {
        game->player->height = BASE_PLAYER_HEIGHT + shake_offset;
        // printf("render_ongoing_barrage: Player height: %f\n", game->player->height);
    }

    int offsets[1][2] = {{0, 0}}; // Only one tile rendered

    for (int i = 0; i < 1; i++)
    {
        float spriteX, spriteY;
        calculate_sprite_position(game, 
                                  game->strike[2].position.x + offsets[i][0], 
                                  game->strike[2].position.y + offsets[i][1], 
                                  &spriteX, &spriteY);
        // printf("render_ongoing_barrage: Sprite position: (%f, %f)\n", spriteX, spriteY);

        float transformX, transformY;
        transform_sprite(game, spriteX, spriteY, &transformX, &transformY);
        // printf("render_ongoing_barrage: Transformed position: (%f, %f)\n", transformX, transformY);

        int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);
        // printf("render_ongoing_barrage: Sprite Screen X: %d\n", spriteScreenX);

        int spriteHeight, drawStartY, drawEndY;
        calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);
        // printf("render_ongoing_barrage: Sprite Height: %d, Draw Y range: %d - %d\n", spriteHeight, drawStartY, drawEndY);

        int spriteWidth, drawStartX, drawEndX;
        calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);
        // printf("render_ongoing_barrage: Sprite Width: %d, Draw X range: %d - %d\n", spriteWidth, drawStartX, drawEndX);

        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            if (is_sprite_in_front(transformY, stripe, game->screen_width))
            {
                // printf("render_ongoing_barrage: Drawing stripe %d\n", stripe);
                draw_sprite_stripe(game, strike_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
            }
        }
            // Check if we've completed a full animation cycle
    if (current_frame == 18)
        add_script(game, play_barrage_shell,0);
    if (current_frame == NUM_AIRSTRIKE_FRAMES - 1)
    {
        // add_script(game, play_barrage_shell,2);
        game->strike[2].is_animating = 0;
        game->strike[2].delay_frames = 0;
        printf("render_ongoing_barrage: Completed full animation cycle, randomizing location\n");
        printf("Barrage Hit\n");
        randomize_barrage_location(game);
    }
    }

    // printf("render_ongoing_barrage: End\n");
}

void render_barrage(t_game *game)
{
    if (game->strike[2].is_launching)
    {
        render_call_barrage(game, game->strike[2].base_position);
    }
    if (game->strike[2].is_active)
    {
        if (!game->strike[2].is_animating)
        {
            if (game->strike[2].delay_frames >= game->strike[2].delay_duration)
            {
                game->strike[2].is_animating = 1;
                game->strike[2].current_frame = 0;
                game->strike[2].frame_count = 0;
            }
            else
            {
                game->strike[2].delay_frames++;
            }
        }
        
        if (game->strike[2].is_animating)
        {
            render_ongoing_barrage(game);
        }
    }
}