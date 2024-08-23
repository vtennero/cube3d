/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:49:50 by toto              #+#    #+#             */
/*   Updated: 2024/08/23 10:15:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void render_extract(t_game *game)
// {
//     t_texture *extract_texture;

//     if (game->extract[0].is_available == 1 || game->extract[0].is_activated == 1)
//     {
//         extract_texture = &game->extract_texture[0];
//     }
//     else if (game->extract[0].is_landing == 1)
//     {
//         extract_texture = &game->extract_texture[1];
//     }
//     else
//     {
//         return;
//     }

//     float spriteX, spriteY;
//     calculate_sprite_position(game, game->extract[0].position.x, game->extract[0].position.y, &spriteX, &spriteY);

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
//             draw_sprite_stripe(game, extract_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
//         }
//     }
// }

// void render_extract_multi_tile(t_game *game, t_texture *extract_texture, float base_x, float base_y)
// {
//     // Define the number of tiles and their offset
//     const int num_tiles = 3;
//     const float tile_offset = 1.0f; // Assume 1.0 is the width of a tile

//     // Calculate the player's view angle
//     float view_angle = atan2(game->player->direction.y, game->player->direction.x);

//     // Calculate the perpendicular vector to the player's view
//     float perp_x = -sin(view_angle);
//     float perp_y = cos(view_angle);

//     for (int i = 0; i < num_tiles; i++)
//     {
//         // Calculate the position of each tile
//         float tile_x = base_x + perp_x * (i - (num_tiles - 1) / 2.0f) * tile_offset;
//         float tile_y = base_y + perp_y * (i - (num_tiles - 1) / 2.0f) * tile_offset;

//         float spriteX, spriteY;
//         calculate_sprite_position(game, tile_x, tile_y, &spriteX, &spriteY);

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
// }

void render_extract_multi_tile(t_game *game, t_texture *extract_texture, float base_x, float base_y)
{
    const int num_tiles = 3;
    const float tile_offset = 0.9f; // Slightly reduce the offset to create overlap

    float view_angle = atan2(game->player->direction.y, game->player->direction.x);
    float perp_x = -sin(view_angle);
    float perp_y = cos(view_angle);

    for (int i = 0; i < num_tiles; i++)
    {
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

        // Increase the sprite width slightly to ensure overlap
        spriteWidth = (int)(spriteWidth * 1.1f);
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


void render_extract(t_game *game)
{
    t_texture *extract_texture;

    if (game->extract[0].is_available == 1 || game->extract[0].is_activated == 1)
    {
        extract_texture = &game->extract_texture[0];
        
        float spriteX, spriteY;
        calculate_sprite_position(game, game->extract[0].position.x, game->extract[0].position.y, &spriteX, &spriteY);

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
                draw_sprite_stripe(game, extract_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
            }
        }
    }
    else if (game->extract[0].is_landing == 1)
    {
        extract_texture = &game->extract_texture[1];
        render_extract_multi_tile(game, extract_texture, game->extract[0].position.x, game->extract[0].position.y);
    }
}