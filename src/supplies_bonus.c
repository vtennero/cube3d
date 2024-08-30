
// texture loading
// rendering
// add to render loop

// is close to supplies
// collection logic, hp increase, audio script

#include "cube3d.h"

#define SUPPLY_DISTANCE 2.0f  // Increased to 2 or more tiles away

void render_supply_take(t_game *game)
{
    int x, y;
    int solid_white = 0xFFFFFF; 
    
    if (game->player->taking_supplies)
    {
        for (y = 0; y < game->screen_height; y++)
    {
        for (x = 0; x < game->screen_width; x++)
        {
            // Decide whether to render this pixel based on a pattern
            if ((x + y) % 3 == 0)  // This creates a diagonal pattern
            {
                img_pix_put(&game->img, x, y, solid_white);
            }
        }
    }
    }

}

int find_closest_supply(t_game *game)
{
    int closest_index = -1;
    float closest_distance_squared = SUPPLY_DISTANCE * SUPPLY_DISTANCE;

    for (int i = 0; i < game->num_supplies; i++)
    {
        if (!game->supplies[i].collected)
        {
            float dx = game->player->position.x - game->supplies[i].position.x;
            float dy = game->player->position.y - game->supplies[i].position.y;
            
            // Calculate the squared distance
            float distance_squared = dx * dx + dy * dy;
            
            // If this supply is closer than the current closest and within range
            if (distance_squared <= closest_distance_squared)
            {
                closest_distance_squared = distance_squared;
                closest_index = i;
            }
        }
    }
    
    return closest_index;
}

#define TILE_EPSILON 0.5f  // Half a tile width to consider player on the same tile

int find_supply_on_player_tile(t_game *game)
{
    for (int i = 0; i < game->num_supplies; i++)
    {
        if (!game->supplies[i].collected)
        {
            // Check if player is on the same tile as the supply
            if (fabs(game->player->position.x - game->supplies[i].position.x) < TILE_EPSILON &&
                fabs(game->player->position.y - game->supplies[i].position.y) < TILE_EPSILON)
            {
                return i;  // Return the index of the supply on the same tile
            }
        }
    }
    
    return -1;  // No supply found on the same tile as the player
}

void render_supply(t_game *game, t_vector2d position)
{
    t_texture *supply_texture = &game->supplies_texture[0];

    // printf("Rendering supply at position (%.2f, %.2f)\n", position.x, position.y);

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
            render_supply(game, game->supplies[i].position);
        }
        else
        {
            // printf("Collectible %d is already collected\n", i);
        }
    }
}

