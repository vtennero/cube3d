/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:11:09 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/18 16:28:36 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void calculate_sprite_transforms(t_game *game, t_vector2d position, float *transformX, float *transformY)
// {
//     float spriteX, spriteY;
//     calculate_sprite_position(game, position.x, position.y, &spriteX, &spriteY);
//     transform_sprite(game, spriteX, spriteY, transformX, transformY);
// }

// void calculate_sprite_dimensions(t_game *game, float transformY, int spriteScreenX,
//                                  int *spriteHeight, int *drawStartY, int *drawEndY,
//                                  int *spriteWidth, int *drawStartX, int *drawEndX)
// {
//     calculate_sprite_height(game, transformY, spriteHeight, drawStartY, drawEndY);
//     calculate_sprite_width(game, transformY, spriteScreenX, spriteWidth, drawStartX, drawEndX);
// }

// void render_sprite_common(t_game *game, t_vector2d position, t_texture *texture)
// {
//     float transformX, transformY;
//     calculate_sprite_transforms(game, position, &transformX, &transformY);

//     int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

//     int spriteHeight, drawStartY, drawEndY, spriteWidth, drawStartX, drawEndX;
//     calculate_sprite_dimensions(game, transformY, spriteScreenX,
//                                 &spriteHeight, &drawStartY, &drawEndY,
//                                 &spriteWidth, &drawStartX, &drawEndX);

//     for (int stripe = drawStartX; stripe < drawEndX; stripe++)
//     {
//         if (is_sprite_in_front(transformY, stripe, game->screen_width))
//         {
//             draw_sprite_stripe(game, texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
//         }
//     }
// }


