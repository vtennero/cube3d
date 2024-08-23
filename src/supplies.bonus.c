
// texture loading
// rendering
// add to render loop

// is close to supplies
// collection logic, hp increase, audio script

#include "cube3d.h"


void render_supply(t_game *game, t_vector2d position)
{
    t_texture *supply_texture = &game->supplies_texture[0];

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
            draw_sprite_stripe(game, supply_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
        }
    }
}


void render_supplies(t_game *game)
{
    for (int i = 0; i < game->num_supplies; i++)
    {
        if (!game->supplies[i].collected)
        {
            // printf("Rendering collectible %d at (%.2f, %.2f)\n", i, game->supplies[i].position.x, game->supplies[i].position.y);
            render_collectible(game, game->supplies[i].position);
        }
        else
        {
            // printf("Collectible %d is already collected\n", i);
        }
    }
}

