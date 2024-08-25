
#include "cube3d.h"

float STRIKE_WIDTH_FACTOR = 0.1; // Adjust this value to change the overall width scaling

// void draw_strike_stripe(t_game *game, int stripe, int drawStartY, int drawEndY)
// {
//     int strike_width = 3;
//     int half_width = strike_width / 2;

//     int full_height = game->screen_height;

//     printf("Drawing strike: stripe=%d, drawStartY=%d, drawEndY=%d, full_height=%d\n", 
//            stripe, drawStartY, drawEndY, full_height);

//     for (int y = 0; y < full_height; y++)
//     {
//         for (int i = -half_width; i <= half_width; i++)
//         {
//             int x = stripe + i;
//             if (x >= 0 && x < game->screen_width)
//             {
//                 int color;
//                 char* color_name;
//                 if (y < drawEndY)
//                 {
//                     if (i == 0)
//                     {
//                         color = 0xFFFFFF; // White in the middle
//                         color_name = "White";
//                     }
//                     else
//                     {
//                         color = 0xFF0000; // Red on the sides
//                         color_name = "Red";
//                     }
//                 }
//                 else
//                 {
//                     color = 0x00FF00; // Green for the bottom part
//                     color_name = "Green";
//                 }
//                 img_pix_put(&game->img, x, y, color);
                
//                 // Print debug info for every 50th pixel to avoid overwhelming output
//                 if (y % 50 == 0 && i == 0)
//                 {
//                     printf("Drawing pixel: x=%d, y=%d, color=%s\n", x, y, color_name);
//                 }
//             }
//         }
//     }
// }


// void render_strike(t_game *game, t_vector2d position)
// {
//     float spriteX, spriteY;
//     calculate_sprite_position(game, position.x, position.y, &spriteX, &spriteY);

//     float transformX, transformY;
//     transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

//     int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

//     int spriteHeight, drawStartY, drawEndY;
//     calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

//     // We only need to render a single stripe for the strike
//     int stripe = spriteScreenX;
//     if (is_sprite_in_front(transformY, stripe, game->screen_width))
//     {
//         draw_strike_stripe(game, stripe, drawStartY, drawEndY);
//     }
// }

void draw_strike_stripe(t_game *game, int stripe, int drawStartY, int drawEndY, float distance)
{
    // Calculate the total width based on distance
    int total_width = (int)(STRIKE_WIDTH_FACTOR * game->screen_width / distance);
    // Ensure the total width is at least 3 pixels
    total_width = (total_width < 3) ? 3 : total_width;
    
    // Make the white part wider
    int white_width = total_width / 2;
    // int red_width = (total_width - white_width) / 2;

    printf("Drawing strike: stripe=%d, drawStartY=%d, drawEndY=%d, total_width=%d\n", 
           stripe, drawStartY, drawEndY, total_width);

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
    strike->frame_count++;
    
    // Only change frame every AIRSTRIKE_ANIMATION_INTERVAL
    if (strike->frame_count % AIRSTRIKE_ANIMATION_INTERVAL != 0)
        return strike->current_frame;

    // Move to the next frame in the sequence
    strike->current_frame = (strike->current_frame + 1) % NUM_AIRSTRIKE_FRAMES;

    // If we've completed a full cycle, set is_active to 0
    if (strike->current_frame == 0)
    {
        strike->is_active = 0;
        strike->is_launching = 0;
    }

    return strike->current_frame;
}

void render_ongoing_strike(t_game *game)
{
    if (!game->strike->is_active)
        return;

    int current_frame = get_next_airstrike_frame(game->strike);
    t_texture *strike_texture = &game->airstrike_textures[current_frame];

    printf("Rendering strike frame %d, texture address: %p\n", current_frame, (void*)strike_texture);

    // Define offsets for adjacent tiles
    int offsets[4][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}}; // Current tile and 3 adjacent

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

        printf("Strike sprite dimensions for tile %d: X=%d-%d, Y=%d-%d\n", i, drawStartX, drawEndX, drawStartY, drawEndY);

        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            if (is_sprite_in_front(transformY, stripe, game->screen_width))
            {
                draw_sprite_stripe(game, strike_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
            }
        }
    }
}

// void render_ongoing_strike(t_game *game)
// {
//     if (!game->strike->is_active)
//         return;

//     int current_frame = get_next_airstrike_frame(game->strike);
//     t_texture *strike_texture = &game->airstrike_textures[current_frame];

//     printf("Rendering strike frame %d, texture address: %p\n", current_frame, (void*)strike_texture);

//     float spriteX, spriteY;
//     calculate_sprite_position(game, game->strike->position.x, game->strike->position.y, &spriteX, &spriteY);

//     float transformX, transformY;
//     transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

//     int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

//     int spriteHeight, drawStartY, drawEndY;
//     calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

//     int spriteWidth, drawStartX, drawEndX;
//     calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

//     printf("Strike sprite dimensions: X=%d-%d, Y=%d-%d\n", drawStartX, drawEndX, drawStartY, drawEndY);

//     for (int stripe = drawStartX; stripe < drawEndX; stripe++)
//     {
//         if (is_sprite_in_front(transformY, stripe, game->screen_width))
//         {
//             draw_sprite_stripe(game, strike_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
//         }
//     }
// }

// void render_ongoing_strike(t_game *game)
// {
//     if (!game->strike->is_active)
//         return;

//     int current_frame = get_next_airstrike_frame(game->strike);
//     t_texture *strike_texture = &game->airstrike_textures[current_frame];

//     float spriteX, spriteY;
//     calculate_sprite_position(game, game->strike->position.x, game->strike->position.y, &spriteX, &spriteY);

//     float transformX, transformY;
//     transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

//     int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

//     int spriteHeight, drawStartY, drawEndY;
//     calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

//     int spriteWidth, drawStartX, drawEndX;
//     calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

//     for (int stripe = drawStartX; stripe < drawEndX; stripe++)
//     {
//         if (is_sprite_in_front(transformY, stripe, game->screen_width))
//         {
//             draw_sprite_stripe(game, strike_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
//         }
//     }
// }

void    render_strike(t_game *game)
{
    if (game->strike->is_launching)
        render_call_strike(game, game->strike->position);
    else if (game->strike->is_active)
        render_ongoing_strike(game);
}