/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:44:50 by toto              #+#    #+#             */
/*   Updated: 2024/08/22 23:09:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void render_collectible(t_game *game, t_vector2d position)
{
    t_texture *collectible_texture = &game->coll_texture[0];

    float spriteX, spriteY;
    calculate_sprite_position(game, position.x, position.y, &spriteX, &spriteY);

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
            draw_sprite_stripe(game, collectible_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
        }
    }
}


void render_collectibles(t_game *game)
{
    // printf("Rendering collectibles. Total: %d\n", game->num_collectibles);
    for (int i = 0; i < game->num_collectibles; i++)
    {
        if (!game->collectibles[i].collected)
        {
            // printf("Rendering collectible %d at (%.2f, %.2f)\n", i, game->collectibles[i].position.x, game->collectibles[i].position.y);
            render_collectible(game, game->collectibles[i].position);
        }
        else
        {
            // printf("Collectible %d is already collected\n", i);
        }
    }
}
