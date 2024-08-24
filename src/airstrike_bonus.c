
#include "cube3d.h"

// Updated helper function to draw a strike stripe
void s_calculate_sprite_height(t_game *game, float transformY, int *spriteHeight, int *drawStartY, int *drawEndY)
{
    // Calculate sprite height based on distance (transformY)
    *spriteHeight = abs((int)(game->screen_height / (transformY * OBJECT_SIZE)));
    
    // Calculate vertical position, starting from the top of the screen
    *drawStartY = 0; // Always start from the top
    *drawEndY = *spriteHeight;
    
    // Ensure drawEndY doesn't exceed screen height
    if (*drawEndY >= game->screen_height)
        *drawEndY = game->screen_height - 1;
}

void s_draw_sprite_stripe(t_game *game, t_texture *obj_texture, int stripe, int drawStartY, int drawEndY, int spriteHeight, int spriteWidth, int spriteScreenX, float transformY)
{
    int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * obj_texture->width / spriteWidth) / 256;

    t_ray_node *current = find_ray_node(game, stripe);

    if (current && transformY < current->ray.perpWallDist)
    {
        for (int y = drawStartY; y < drawEndY; y++)
        {
            // Calculate texture Y coordinate
            int d = y * 256 - game->screen_height * 128 + spriteHeight * 128;
            int texY = ((d * obj_texture->height) / spriteHeight) / 256;
            
            // Ensure texY is within bounds
            texY = (texY < 0) ? 0 : (texY >= obj_texture->height) ? obj_texture->height - 1 : texY;
            
            int color = get_pixel_color(texX, texY, obj_texture->width, obj_texture->height, obj_texture->data, obj_texture->tex_bpp, obj_texture->tex_line_len);
            
            if (color != -1)
            {
                img_pix_put(&game->img, stripe, y, color);
            }
        }
    }
}

void draw_strike_stripe(t_game *game, int stripe, int drawStartY, int drawEndY)
{
    int strike_width = 3; // Width of the strike in pixels
    int half_width = strike_width / 2;

    for (int y = drawStartY; y < drawEndY; y++)
    {
        for (int i = -half_width; i <= half_width; i++)
        {
            int x = stripe + i;
            if (x >= 0 && x < game->screen_width)
            {
                int color;
                if (i == 0)
                {
                    color = 0xFFFFFF; // White in the middle
                }
                else
                {
                    color = 0xFF0000; // Red on the sides
                }
                img_pix_put(&game->img, x, y, color);
            }
        }
    }
}

void render_strike(t_game *game, t_vector2d position)
{
    float spriteX, spriteY;
    calculate_sprite_position(game, position.x, position.y, &spriteX, &spriteY);

    float transformX, transformY;
    transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

    int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

    int spriteHeight, drawStartY, drawEndY;
    calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

    // We only need to render a single stripe for the strike
    int stripe = spriteScreenX;
    if (is_sprite_in_front(transformY, stripe, game->screen_width))
    {
        draw_strike_stripe(game, stripe, drawStartY, drawEndY);
    }
}


void    call_airstrike(t_game *game)
{
    if (game->strike->is_launching)
        render_strike(game, game->strike->position);
}