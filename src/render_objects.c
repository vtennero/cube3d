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

#define OBJECT_SIZE 0.5  // Size of the object in world units

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

//  this works

void render_objects(t_game *game, char *texture_path)
{
    // Load the object texture
    void *obj_texture;
    int obj_width, obj_height;
    int bpp, line_len, endian;
    char *obj_data;

    obj_texture = mlx_xpm_file_to_image(game->mlx_ptr, texture_path, &obj_width, &obj_height);
    if (obj_texture == NULL)
    {
        fprintf(stderr, "Failed to load object texture\n");
        return;
    }
    obj_data = mlx_get_data_addr(obj_texture, &bpp, &line_len, &endian);

    // Object world position
    float objectX = 20.5f;  // Center of tile (20,11)
    float objectY = 11.5f;

    // Calculate sprite position relative to camera
    float spriteX = objectX - game->player->position.x;
    float spriteY = objectY - game->player->position.y;

    // Transform sprite with the inverse camera matrix
    float invDet = 1.0f / (game->player->plane.x * game->player->direction.y - game->player->direction.x * game->player->plane.y);
    float transformX = invDet * (game->player->direction.y * spriteX - game->player->direction.x * spriteY);
    float transformY = invDet * (-game->player->plane.y * spriteX + game->player->plane.x * spriteY);

    int spriteScreenX = (int)((game->screen_width / 2) * (1 + transformX / transformY));

    // Calculate sprite height on screen
    int spriteHeight = abs((int)(game->screen_height / transformY)) * OBJECT_SIZE;
    int drawStartY = -spriteHeight / 2 + game->screen_height / 2;
    if (drawStartY < 0) drawStartY = 0;
    int drawEndY = spriteHeight / 2 + game->screen_height / 2;
    if (drawEndY >= game->screen_height) drawEndY = game->screen_height - 1;

    // Calculate sprite width on screen
    int spriteWidth = abs((int)(game->screen_height / transformY)) * OBJECT_SIZE;
    int drawStartX = -spriteWidth / 2 + spriteScreenX;
    if (drawStartX < 0) drawStartX = 0;
    int drawEndX = spriteWidth / 2 + spriteScreenX;
    if (drawEndX >= game->screen_width) drawEndX = game->screen_width - 1;

    // Loop through every vertical stripe of the sprite on screen
    for (int stripe = drawStartX; stripe < drawEndX; stripe++)
    {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * obj_width / spriteWidth) / 256;

        // Check if the sprite is in front of the camera plane
        if (transformY > 0 && stripe > 0 && stripe < game->screen_width)
        {
            t_ray_node *current = game->ray_list;
            while (current && current->ray.x != stripe)
                current = current->next;

            if (current && transformY < current->ray.perpWallDist)
            {
                for (int y = drawStartY; y < drawEndY; y++)
                {
                    int d = (y) * 256 - game->screen_height * 128 + spriteHeight * 128;
                    int texY = ((d * obj_height) / spriteHeight) / 256;
                    int color = get_pixel_color(texX, texY, obj_width, obj_height, obj_data, bpp, line_len);
                    
                    // Only draw the pixel if it's not transparent (assuming 0 is transparent)
                    if (color != -1)
                        img_pix_put(&game->img, stripe, y, color);
                }
            }
        }
    }
}

// void render_objects(t_game *game, char *texture_path)
// {
//     // Load the object texture (same as before)
//     void *obj_texture;
//     int obj_width, obj_height;
//     int bpp, line_len, endian;
//     char *obj_data;

//     obj_texture = mlx_xpm_file_to_image(game->mlx_ptr, texture_path, &obj_width, &obj_height);
//     if (obj_texture == NULL)
//     {
//         fprintf(stderr, "Failed to load object texture\n");
//         return;
//     }
//     obj_data = mlx_get_data_addr(obj_texture, &bpp, &line_len, &endian);

//     // Object world position
//     float objectX = 20.5f;  // Center of tile (20,11)
//     float objectY = 11.5f;
//     float objectZ = 0.0f;   // Object is on the floor

//     // Calculate sprite position relative to camera
//     float spriteX = objectX - game->player->position.x;
//     float spriteY = objectY - game->player->position.y;
//     float spriteZ = objectZ - game->player->height;

//     // Transform sprite with the inverse camera matrix
//     float invDet = 1.0f / (game->player->plane.x * game->player->direction.y - game->player->direction.x * game->player->plane.y);
//     float transformX = invDet * (game->player->direction.y * spriteX - game->player->direction.x * spriteY);
//     float transformY = invDet * (-game->player->plane.y * spriteX + game->player->plane.x * spriteY);

//     // Adjust for pitch
//     float pitch_adjust = game->player->pitch * transformY;
//     transformY -= spriteZ;

//     int spriteScreenX = (int)((game->screen_width / 2) * (1 + transformX / transformY));

//     // Calculate sprite height on screen
//     int spriteHeight = abs((int)(game->screen_height / transformY)) * OBJECT_SIZE;
//     int drawStartY = -spriteHeight / 2 + game->screen_height / 2 + (int)(pitch_adjust * game->screen_height);
//     if (drawStartY < 0) drawStartY = 0;
//     int drawEndY = spriteHeight / 2 + game->screen_height / 2 + (int)(pitch_adjust * game->screen_height);
//     if (drawEndY >= game->screen_height) drawEndY = game->screen_height - 1;

//     // Calculate sprite width on screen
//     int spriteWidth = abs((int)(game->screen_height / transformY)) * OBJECT_SIZE;
//     int drawStartX = -spriteWidth / 2 + spriteScreenX;
//     if (drawStartX < 0) drawStartX = 0;
//     int drawEndX = spriteWidth / 2 + spriteScreenX;
//     if (drawEndX >= game->screen_width) drawEndX = game->screen_width - 1;

//     // Loop through every vertical stripe of the sprite on screen
//     for (int stripe = drawStartX; stripe < drawEndX; stripe++)
//     {
//         int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * obj_width / spriteWidth) / 256;

//         // Check if the sprite is in front of the camera plane
//         if (transformY > 0 && stripe > 0 && stripe < game->screen_width)
//         {
//             t_ray_node *current = game->ray_list;
//             while (current && current->ray.x != stripe)
//                 current = current->next;

//             if (current && transformY < current->ray.perpWallDist)
//             {
//                 for (int y = drawStartY; y < drawEndY; y++)
//                 {
//                     int d = (y - (int)(pitch_adjust * game->screen_height)) * 256 - game->screen_height * 128 + spriteHeight * 128;
//                     int texY = ((d * obj_height) / spriteHeight) / 256;
//                     int color = get_pixel_color(texX, texY, obj_width, obj_height, obj_data, bpp, line_len);
                    
//                     // Only draw the pixel if it's not transparent (assuming 0 is transparent)
//                     if (color != -1)
//                         img_pix_put(&game->img, stripe, y, color);
//                 }
//             }
//         }
//     }
// }