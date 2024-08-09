/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:47:58 by toto              #+#    #+#             */
/*   Updated: 2024/08/09 16:26:02 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define OBJECT_SIZE 1.5  // Size of the object in world units


// Helper function to get pixel color from texture
int get_pixel_color(int x, int y, int width, int height, char *data, int bpp, int line_len)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return -1; // Return -1 for out-of-bounds

    char *pixel = data + (y * line_len + x * (bpp / 8));
    unsigned int color = *(unsigned int *)pixel;

    // Check if the pixel is completely transparent (all bits are 0)
    if (color == 0)
        return -1; // Return -1 for transparent pixels

    return color;
}

// Calculate sprite position relative to camera
void calculate_sprite_position(t_game *game, float objectX, float objectY, float *spriteX, float *spriteY)
{
    *spriteX = objectX - game->player->position.x;
    *spriteY = objectY - game->player->position.y;
}

// Transform sprite with the inverse camera matrix
void transform_sprite(t_game *game, float spriteX, float spriteY, float *transformX, float *transformY)
{
    float invDet = 1.0f / (game->player->plane.x * game->player->direction.y - game->player->direction.x * game->player->plane.y);
    *transformX = invDet * (game->player->direction.y * spriteX - game->player->direction.x * spriteY);
    *transformY = invDet * (-game->player->plane.y * spriteX + game->player->plane.x * spriteY);
}

// Calculate sprite screen X position
int calculate_sprite_screen_x(t_game *game, float transformX, float transformY)
{
    return (int)((game->screen_width / 2) * (1 + transformX / transformY));
}

void calculate_sprite_height(t_game *game, float transformY, int *spriteHeight, int *drawStartY, int *drawEndY)
{
    *spriteHeight = abs((int)(game->screen_height / transformY)) * OBJECT_SIZE;
    
    // Apply pitch offset
    int pitchOffset = (int)(game->player->pitch * game->screen_height);
    
    *drawStartY = -(*spriteHeight) / 2 + game->screen_height / 2 + pitchOffset;
    *drawStartY = (*drawStartY < 0) ? 0 : *drawStartY;
    *drawEndY = (*spriteHeight) / 2 + game->screen_height / 2 + pitchOffset;
    *drawEndY = (*drawEndY >= game->screen_height) ? game->screen_height - 1 : *drawEndY;
}

// Calculate sprite width on screen
void calculate_sprite_width(t_game *game, float transformY, int spriteScreenX, int *spriteWidth, int *drawStartX, int *drawEndX)
{
    *spriteWidth = abs((int)(game->screen_height / transformY)) * OBJECT_SIZE;
    *drawStartX = -(*spriteWidth) / 2 + spriteScreenX;
    *drawStartX = (*drawStartX < 0) ? 0 : *drawStartX;
    *drawEndX = (*spriteWidth) / 2 + spriteScreenX;
    *drawEndX = (*drawEndX >= game->screen_width) ? game->screen_width - 1 : *drawEndX;
}

// Check if sprite is in front of camera plane
int is_sprite_in_front(float transformY, int stripe, int screen_width)
{
    return (transformY > 0 && stripe > 0 && stripe < screen_width);
}

// Find ray node for current stripe
t_ray_node* find_ray_node(t_game *game, int stripe)
{
    t_ray_node *current = game->ray_list;
    while (current && current->ray.x != stripe)
        current = current->next;
    return current;
}

// Draw sprite vertical stripe, now accounting for pitch
void draw_sprite_stripe(t_game *game, t_texture *obj_texture, int stripe, int drawStartY, int drawEndY, int spriteHeight, int spriteWidth, int spriteScreenX, float transformY)
{
    int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * obj_texture->width / spriteWidth) / 256;

    t_ray_node *current = find_ray_node(game, stripe);

    if (current && transformY < current->ray.perpWallDist)
    {
        for (int y = drawStartY; y < drawEndY; y++)
        {
            // Apply pitch to texture coordinate calculation
            int pitchOffset = (int)(game->player->pitch * game->screen_height);
            int d = (y - pitchOffset) * 256 - game->screen_height * 128 + spriteHeight * 128;
            int texY = ((d * obj_texture->height) / spriteHeight) / 256;
            
            // Ensure texY is within bounds
            texY = (texY < 0) ? 0 : (texY >= obj_texture->height) ? obj_texture->height - 1 : texY;
            
            int color = get_pixel_color(texX, texY, obj_texture->width, obj_texture->height, obj_texture->data, obj_texture->tex_bpp, obj_texture->tex_line_len);
            
            if (color != -1)
                img_pix_put(&game->img, stripe, y, color);
        }
    }
}

void render_object(t_game *game, float objectX, float objectY)
{
    t_texture *obj_texture = &game->obj_texture[0];

    float spriteX, spriteY;
    calculate_sprite_position(game, objectX, objectY, &spriteX, &spriteY);

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
            draw_sprite_stripe(game, obj_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
        }
    }
}

void render_objects(t_game *game)
{
    render_object(game, 20.5f, 11.5f);
}