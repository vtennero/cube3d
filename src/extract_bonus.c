/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:49:50 by toto              #+#    #+#             */
/*   Updated: 2024/08/23 11:44:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void render_extract_multi_tile(t_game *game, float base_x, float base_y)
{
    const int num_tiles = 3;
    const float tile_offset = 0.98f; // Slightly reduced offset for minimal overlap

    float view_angle = atan2(game->player->direction.y, game->player->direction.x);
    float perp_x = -sin(view_angle);
    float perp_y = cos(view_angle);

    for (int i = 0; i < num_tiles; i++)
    {
        t_texture *extract_texture = &game->extract_texture[i + 1]; // Use extract[1], extract[2], extract[3]

        float tile_x = base_x + perp_x * (i - (num_tiles - 1) / 2.0f) * tile_offset;
        float tile_y = base_y + perp_y * (i - (num_tiles - 1) / 2.0f) * tile_offset;

        float spriteX, spriteY;
        calculate_sprite_position(game, tile_x, tile_y, &spriteX, &spriteY);

        float transformX, transformY;
        transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

        int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

        int spriteHeight, drawStartY, drawEndY;
        calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

        int spriteWidth, drawStartX, drawEndX;
        calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

        // Slightly increase sprite width to cover potential gaps
        spriteWidth = (int)(spriteWidth * 1.02f);
        drawStartX = -spriteWidth / 2 + spriteScreenX;
        drawEndX = spriteWidth / 2 + spriteScreenX;

        // Ensure we don't draw outside the screen bounds
        drawStartX = (drawStartX < 0) ? 0 : drawStartX;
        drawEndX = (drawEndX >= game->screen_width) ? game->screen_width - 1 : drawEndX;

        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            if (is_sprite_in_front(transformY, stripe, game->screen_width))
            {
                draw_sprite_stripe(game, extract_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
            }
        }
    }
}


// stable
// void render_extract(t_game *game)
// {
//     if (game->extract[0].is_available == 1 || game->extract[0].is_activated == 1)
//     {
//         t_texture *extract_texture = &game->extract_texture[0];
        
//         float spriteX, spriteY;
//         calculate_sprite_position(game, game->extract[0].position.x, game->extract[0].position.y, &spriteX, &spriteY);

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
//                 draw_sprite_stripe(game, extract_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
//             }
//         }
//     }
//     else if (game->extract[0].is_landing == 1)
//     {
//         render_extract_multi_tile(game, game->extract[0].position.x, game->extract[0].position.y);
//     }
// }

// v2

// void draw_extract_stripe(t_game *game, int stripe, int drawStartY, int drawEndY, float distance)
// {
//     (void)drawEndY;
//     // Calculate the total width based on distance, using a smaller factor for narrower stripe
//     int total_width = (int)(0.05 * game->screen_width / distance);  // Reduced from 0.1 to 0.05
//     // Ensure the total width is at least 3 pixels
//     total_width = (total_width < 3) ? 3 : total_width;
    
//     // Make the white part wider
//     int white_width = total_width / 2;
//     // int white_width = (total_width < 3) ? 1 : total_width /2;

//     for (int y = 0; y < drawStartY; y++)  // Draw only above the texture
//     {
//         for (int i = -total_width/2; i < total_width/2; i++)
//         {
//             int x = stripe + i;
//             if (x >= 0 && x < game->screen_width)
//             {
//                 int color;
//                 if (i >= -white_width/2 && i < white_width/2)
//                 {
//                     color = 0xFFFFFF; // White in the middle
//                 }
//                 else
//                 {
//                     // Calculate gradient for blue
//                     float gradient = 1.0f - (float)abs(i) / (total_width/2);
//                     int blue_value = 128 + (int)(127 * gradient); // Range from 128 to 255
//                     color = blue_value; // Only blue channel
//                 }
//                 img_pix_put(&game->img, x, y, color);
//             }
//         }
//     }
// }

void draw_extract_stripe(t_game *game, int stripe, int drawStartY, int drawEndY, float distance)
{
    (void)drawEndY;
    // Calculate the total width based on distance, using a smaller factor for narrower stripe
    int total_width = (int)(0.05 * game->screen_width / distance);
    // Ensure the total width is at least 3 pixels
    total_width = (total_width < 3) ? 3 : total_width;
    
    // Ensure there's always at least one white pixel in the middle
    int white_width = (total_width < 3) ? 1 : total_width / 2;

    for (int y = 0; y < drawStartY; y++)
    {
        for (int i = -total_width/2; i < total_width/2; i++)
        {
            int x = stripe + i;
            if (x >= 0 && x < game->screen_width)
            {
                int color;
                if (i == 0 || (i >= -white_width/2 && i < white_width/2))  // Changed this line
                {
                    color = 0xFFFFFF; // White in the middle
                }
                else
                {
                    // Calculate gradient for blue
                    float gradient = 1.0f - (float)abs(i) / (total_width/2);
                    int blue_value = 128 + (int)(127 * gradient); // Range from 128 to 255
                    color = blue_value; // Only blue channel
                }
                img_pix_put(&game->img, x, y, color);
            }
        }
    }
}



void render_extract(t_game *game)
{
    if (game->extract[0].is_available == 1 || game->extract[0].is_activated == 1)
    {
        t_texture *extract_texture = &game->extract_texture[0];
        
        float spriteX, spriteY;
        calculate_sprite_position(game, game->extract[0].position.x, game->extract[0].position.y, &spriteX, &spriteY);

        float transformX, transformY;
        transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

        int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

        int spriteHeight, drawStartY, drawEndY;
        calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

        int spriteWidth, drawStartX, drawEndX;
        calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

        // Calculate distance to player for the red ray
        float dx = game->extract[0].position.x - game->player->position.x;
        float dy = game->extract[0].position.y - game->player->position.y;
        float distance = sqrt(dx * dx + dy * dy);

        // Render the ray first, only if the extract is available
        if (game->extract[0].is_available == 1)
        {
            int rayStripe = spriteScreenX;
            if (is_sprite_in_front(transformY, rayStripe, game->screen_width))
            {
                draw_extract_stripe(game, rayStripe, drawStartY, drawEndY, distance);
            }
        }

        // Now render the texture
        for (int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            if (is_sprite_in_front(transformY, stripe, game->screen_width))
            {
                draw_sprite_stripe(game, extract_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
            }
        }
    }
    else if (game->extract[0].is_landing == 1)
    {
        render_extract_multi_tile(game, game->extract[0].position.x, game->extract[0].position.y);
    }
}

