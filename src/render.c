/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/13 16:47:25 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define MLX_SUCCESS 0
#define MLX_ERROR -1
#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF

void img_pix_put(t_img *img, int x, int y, int color)
{
    char *pixel;
    int i;

    if (x < 0 || x >= DEFAULT_S_WIDTH || y < 0 || y >= DEFAULT_S_HEIGHT)
    {
        fprintf(stderr, "Attempted to write pixel out of bounds: x=%d, y=%d\n", x, y);
        return; // Skip drawing for invalid coordinates
    }

    i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    while (i >= 0)
    {
        /* big endian, MSB is the leftmost bit */
        if (img->endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        /* little endian, LSB is the leftmost bit */
        else
            *pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
}

// void render_ray(t_img *img, t_ray ray, t_texture *texture) {
//     if (img->bpp != texture->tex_bpp || img->endian != texture->tex_endian) {
//         fprintf(stderr, "Error: Texture and screen format mismatch\n");
//         exit(EXIT_FAILURE);
//     }

//     // Use the pre-calculated texX for the ray
//     int texX = ray.texX;  // This value is already calculated and should be valid for the texture width

//     int y = ray.draw_start;
//     while (y < ray.draw_end) {
//         // Calculate texY based on the proportion of the wall's visible height
//         // printf("renderray: texture dimensions width %d x height %d", texture->width, texture->height);
//         int texY = ((y - ray.draw_start) * texture->height) / ray.lineHeight;
//         texY %= texture->height;  // Wrap around if necessary
//         int color = get_texture_color(texture, texX, texY);
//         img_pix_put(img, ray.x, y, color);
//         y++;
//     }
// }

// void render_ray(t_img *img, t_ray ray, t_texture *texture)
// {
//     if (img->bpp != texture->tex_bpp || img->endian != texture->tex_endian)
//     {
//         fprintf(stderr, "Error: Texture and screen format mismatch\n");
//         exit(EXIT_FAILURE);
//     }

//     int texX = ray.texX;

//     // Perspective correction code
//     double step = 1.0 * texture->height / ray.lineHeight;
//     double texPos = (ray.draw_start - DEFAULT_S_HEIGHT / 2 + ray.lineHeight / 2) * step;

//     for (int y = ray.draw_start; y < ray.draw_end; y++)
//     {
//         int texY = (int)texPos & (texture->height - 1);
//         texPos += step;
//         int color = get_texture_color(texture, texX, texY);
//         img_pix_put(img, ray.x, y, color);
//     }
// }

void render_ray(t_img *img, t_ray ray, t_texture *texture)
{
    if (img->bpp != texture->tex_bpp || img->endian != texture->tex_endian)
    {
        fprintf(stderr, "Error: Texture and screen format mismatch\n");
        exit(EXIT_FAILURE);
    }

    // Use doubles for increased precision
    double wallX = ray.wallX;
    int texX = (int)(wallX * (double)(texture->width));
    if (ray.side == 0 && ray.rayDirX > 0)
        texX = texture->width - texX - 1;
    if (ray.side == 1 && ray.rayDirY < 0)
        texX = texture->width - texX - 1;

    // Calculate the height of the wall slice to be drawn
    int lineHeight = (int)(DEFAULT_S_HEIGHT / ray.perpWallDist);

    // Calculate the lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + DEFAULT_S_HEIGHT / 2;
    if (drawStart < 0)
        drawStart = 0;
    int drawEnd = lineHeight / 2 + DEFAULT_S_HEIGHT / 2;
    if (drawEnd >= DEFAULT_S_HEIGHT)
        drawEnd = DEFAULT_S_HEIGHT - 1;

    // Texture step and initial texture position
    double step = 1.0 * texture->height / lineHeight;
    double texPos = (drawStart - DEFAULT_S_HEIGHT / 2 + lineHeight / 2) * step;

    for (int y = drawStart; y < drawEnd; y++)
    {
        int texY = (int)texPos & (texture->height - 1);
        texPos += step;
        int color = get_texture_color(texture, texX, texY);
        img_pix_put(img, ray.x, y, color);
    }
}

// void render_sky(t_img *img, void *mlx_ptr, char *sky_texture_path)
// {
//     int sky_width, sky_height;
//     void *sky_texture;
//     char *sky_data;
//     int bpp, line_len, endian;

//     // Load the sky texture
//     sky_texture = mlx_xpm_file_to_image(mlx_ptr, sky_texture_path, &sky_width, &sky_height);
//     sky_data = mlx_get_data_addr(sky_texture, &bpp, &line_len, &endian);

//     for (int i = 0; i < DEFAULT_S_HEIGHT / 2; i++)
//     {
//         for (int j = 0; j < DEFAULT_S_WIDTH; j++)
//         {
//             // Calculate pixel position in the texture
//             int tx = (j * sky_width) / DEFAULT_S_WIDTH;         // repeat texture if needed
//             int ty = (i * sky_height) / (DEFAULT_S_HEIGHT / 2); // repeat texture vertically

//             // Get the color from the texture
//             int color = *((int *)(sky_data + ty * line_len + tx * (bpp / 8)));

//             // Put the color into the main image
//             // printf("render_sky: calling img_pix_put\n");
//             img_pix_put(img, j, i, color);
//         }
//     }

//     // Clean up the texture
//     mlx_destroy_image(mlx_ptr, sky_texture);
// }

void render_sky(t_game *game, char *sky_texture_path)
{
    static void *sky_texture = NULL;
    static char *sky_data = NULL;
    static int sky_width = 0, sky_height = 0;
    static int bpp, line_len, endian;

    // Load the sky texture only once
    if (sky_texture == NULL)
    {
        sky_texture = mlx_xpm_file_to_image(game->mlx_ptr, sky_texture_path, &sky_width, &sky_height);
        if (sky_texture == NULL)
        {
            fprintf(stderr, "Failed to load sky texture\n");
            return;
        }
        sky_data = mlx_get_data_addr(sky_texture, &bpp, &line_len, &endian);
    }

    // Calculate the angle of the player's direction
    float angle = atan2(game->player->direction.y, game->player->direction.x);

    // Adjust rotation speed (smaller value = slower rotation)
    float rotation_speed = 0.25; // Adjust this value to change rotation speed

    // Calculate the pixel offset in the texture
    int texture_offset = (int)(fmodf(angle / (2 * M_PI) * rotation_speed * sky_width + sky_width, sky_width));

    for (int i = 0; i < game->screen_height / 2; i++)
    {
        for (int j = 0; j < game->screen_width; j++)
        {
            // Calculate texture coordinates
            int tx = (texture_offset + (j * sky_width / game->screen_width)) % sky_width;
            int ty = i * sky_height / (game->screen_height / 2);

            // Ensure tx and ty are within bounds
            tx = (tx < 0) ? 0 : (tx >= sky_width) ? sky_width - 1
                                                  : tx;
            ty = (ty < 0) ? 0 : (ty >= sky_height) ? sky_height - 1
                                                   : ty;

            // Calculate the pixel position in the texture data
            int pixel_pos = ty * line_len + tx * (bpp / 8);

            // Ensure we're not reading out of bounds
            if (pixel_pos >= 0 && pixel_pos < sky_height * line_len)
            {
                int color = *((int *)(sky_data + pixel_pos));
                img_pix_put(&game->img, j, i, color);
            }
        }
    }
}

// void render_sky(t_game *game, char *sky_texture_path)
// {
//     static void *sky_texture = NULL;
//     static char *sky_data = NULL;
//     static int sky_width = 0, sky_height = 0;
//     static int bpp, line_len, endian;

//     // Load the sky texture only once
//     if (sky_texture == NULL)
//     {
//         sky_texture = mlx_xpm_file_to_image(game->mlx_ptr, sky_texture_path, &sky_width, &sky_height);
//         if (sky_texture == NULL)
//         {
//             fprintf(stderr, "Failed to load sky texture\n");
//             return;
//         }
//         sky_data = mlx_get_data_addr(sky_texture, &bpp, &line_len, &endian);
//     }

//     // Calculate the angle of the player's direction
//     float angle = atan2(game->player->direction.y, game->player->direction.x);

//     // Normalize angle to [0, 1)
//     float texture_offset = fmodf(angle / (2 * M_PI) + 1, 1);

//     for (int i = 0; i < game->screen_height / 2; i++)
//     {
//         for (int j = 0; j < game->screen_width; j++)
//         {
//             // Calculate texture coordinates
//             float tx_f = fmodf(texture_offset + (float)j / game->screen_width, 1.0f);
//             int tx = (int)(tx_f * sky_width);
//             int ty = i * sky_height / (game->screen_height / 2);

//             // Ensure tx and ty are within bounds
//             tx = (tx < 0) ? 0 : (tx >= sky_width) ? sky_width - 1
//                                                   : tx;
//             ty = (ty < 0) ? 0 : (ty >= sky_height) ? sky_height - 1
//                                                    : ty;

//             // Calculate the pixel position in the texture data
//             int pixel_pos = ty * line_len + tx * (bpp / 8);

//             // Ensure we're not reading out of bounds
//             if (pixel_pos >= 0 && pixel_pos < sky_height * line_len)
//             {
//                 int color = *((int *)(sky_data + pixel_pos));
//                 img_pix_put(&game->img, j, i, color);
//             }
//         }
//     }
// }

// as of july 8, this works best. but not perfect
// void render_sky(t_game *game, char *sky_texture_path)
// {
//     static void *sky_texture = NULL;
//     static char *sky_data = NULL;
//     static int sky_width = 0, sky_height = 0;
//     static int bpp, line_len, endian;

//     // Load the sky texture only once
//     if (sky_texture == NULL)
//     {
//         sky_texture = mlx_xpm_file_to_image(game->mlx_ptr, sky_texture_path, &sky_width, &sky_height);
//         if (sky_texture == NULL)
//         {
//             fprintf(stderr, "Failed to load sky texture\n");
//             return;
//         }
//         sky_data = mlx_get_data_addr(sky_texture, &bpp, &line_len, &endian);
//     }

//     // Calculate the angle of the player's direction
//     float angle = atan2(game->player->direction.y, game->player->direction.x);

//     // Normalize angle to [0, 2π)
//     angle = fmodf(angle + 2 * M_PI, 2 * M_PI);

//     // Calculate the FOV
//     float fov = 2 * atan(game->player->plane.y);

//     for (int i = 0; i < game->screen_height / 2; i++)
//     {
//         float v = (float)i / (game->screen_height / 2);
//         for (int j = 0; j < game->screen_width; j++)
//         {
//             // Calculate the horizontal angle for this pixel
//             float phi = angle + (j / (float)game->screen_width - 0.5f) * fov;

//             // Convert the angle to a texture coordinate
//             float tx_f = 0.5f + atan2(sin(phi), cos(phi)) / (2 * M_PI);
//             tx_f = fmodf(tx_f, 1.0f);
//             int tx = (int)(tx_f * sky_width);

//             // Calculate the vertical texture coordinate
//             int ty = (int)(v * sky_height);

//             // Ensure tx and ty are within bounds
//             tx = (tx < 0) ? 0 : (tx >= sky_width) ? sky_width - 1
//                                                   : tx;
//             ty = (ty < 0) ? 0 : (ty >= sky_height) ? sky_height - 1
//                                                    : ty;

//             // Calculate the pixel position in the texture data
//             int pixel_pos = ty * line_len + tx * (bpp / 8);

//             // Ensure we're not reading out of bounds
//             if (pixel_pos >= 0 && pixel_pos < sky_height * line_len)
//             {
//                 int color = *((int *)(sky_data + pixel_pos));
//                 img_pix_put(&game->img, j, i, color);
//             }
//         }
//     }

//     // Note: We're not destroying the texture after each render to improve performance
//     // You should add a separate function to clean up the sky texture when your program exits
// }

// this is even better
// void render_sky(t_game *game, char *sky_texture_path)
// {
//     static void *sky_texture = NULL;
//     static char *sky_data = NULL;
//     static int sky_width = 0, sky_height = 0;
//     static int bpp, line_len, endian;

//     // Load the sky texture only once
//     if (sky_texture == NULL)
//     {
//         sky_texture = mlx_xpm_file_to_image(game->mlx_ptr, sky_texture_path, &sky_width, &sky_height);
//         if (sky_texture == NULL)
//         {
//             fprintf(stderr, "Failed to load sky texture\n");
//             return;
//         }
//         sky_data = mlx_get_data_addr(sky_texture, &bpp, &line_len, &endian);
//     }

//     // Calculate the angle of the player's direction
//     float angle = atan2(game->player->direction.y, game->player->direction.x);

//     // Normalize angle to [0, 2π)
//     angle = fmodf(angle + 2 * M_PI, 2 * M_PI);

//     // Adjust rotation speed (smaller value = slower rotation)
//     float rotation_factor = 0.25; // Adjust this value to change rotation speed

//     // Convert angle to texture offset with adjusted rotation speed
//     float texture_offset = (angle / (2 * M_PI)) * rotation_factor;

//     // Calculate the portion of the texture to display based on FOV
//     float fov = 2 * atan(game->player->plane.y);
//     float texture_portion = fov / (2 * M_PI);

//     for (int i = 0; i < game->screen_height / 2; i++)
//     {
//         for (int j = 0; j < game->screen_width; j++)
//         {
//             // Calculate the horizontal texture coordinate
//             float tx_f = fmodf(texture_offset + (j / (float)game->screen_width) * texture_portion, 1.0f);
//             int tx = (int)(tx_f * sky_width);

//             // Ensure tx is within bounds
//             tx = (tx < 0) ? 0 : (tx >= sky_width) ? sky_width - 1
//                                                   : tx;

//             // Calculate the vertical texture coordinate
//             int ty = (i * sky_height) / (game->screen_height / 2);
//             ty = (ty < 0) ? 0 : (ty >= sky_height) ? sky_height - 1
//                                                    : ty;

//             // Calculate the pixel position in the texture data
//             int pixel_pos = ty * line_len + tx * (bpp / 8);

//             // Ensure we're not reading out of bounds
//             if (pixel_pos >= 0 && pixel_pos < sky_height * line_len)
//             {
//                 int color = *((int *)(sky_data + pixel_pos));
//                 img_pix_put(&game->img, j, i, color);
//             }
//         }
//     }
// }

// this works except for texture stretching
// void render_sky(t_game *game, char *sky_texture_path)
// {
//     static void *sky_texture = NULL;
//     static char *sky_data = NULL;
//     static int sky_width = 0, sky_height = 0;
//     static int bpp, line_len, endian;

//     // Load the sky texture only once
//     if (sky_texture == NULL)
//     {
//         sky_texture = mlx_xpm_file_to_image(game->mlx_ptr, sky_texture_path, &sky_width, &sky_height);
//         if (sky_texture == NULL)
//         {
//             fprintf(stderr, "Failed to load sky texture\n");
//             return;
//         }
//         sky_data = mlx_get_data_addr(sky_texture, &bpp, &line_len, &endian);
//     }

//     // Calculate the angle of the player's direction
//     float angle = atan2(game->player->direction.y, game->player->direction.x);

//     // Normalize angle to [0, 2π)
//     angle = fmodf(angle + 2 * M_PI, 2 * M_PI);

//     // Convert angle to texture offset
//     float texture_offset = angle / (2 * M_PI);

//     // Calculate the portion of the texture to display based on FOV
//     float fov = 2 * atan(game->player->plane.y);
//     float texture_portion = fov / (2 * M_PI);

//     printf("Angle: %.2f, Texture Offset: %.2f, FOV: %.2f, Texture Portion: %.2f\n",
//            angle, texture_offset, fov, texture_portion);

//     for (int i = 0; i < game->screen_height / 2; i++)
//     {
//         for (int j = 0; j < game->screen_width; j++)
//         {
//             // Calculate the horizontal texture coordinate
//             float tx_f = fmodf(texture_offset + (j / (float)game->screen_width) * texture_portion, 1.0f);
//             int tx = (int)(tx_f * sky_width);

//             // Ensure tx is within bounds
//             tx = (tx < 0) ? 0 : (tx >= sky_width) ? sky_width - 1
//                                                   : tx;

//             // Calculate the vertical texture coordinate
//             int ty = (i * sky_height) / (game->screen_height / 2);
//             ty = (ty < 0) ? 0 : (ty >= sky_height) ? sky_height - 1
//                                                    : ty;

//             // Calculate the pixel position in the texture data
//             int pixel_pos = ty * line_len + tx * (bpp / 8);

//             // Ensure we're not reading out of bounds
//             if (pixel_pos >= 0 && pixel_pos < sky_height * line_len)
//             {
//                 int color = *((int *)(sky_data + pixel_pos));
//                 img_pix_put(&game->img, j, i, color);
//             }
//         }
//     }

//     // Note: We're not destroying the texture after each render to improve performance
// }

void render_ray_list(t_game *game)
{
    int i = 0;
    t_ray_node *ray_list = NULL;
    ray_list = calculate_rays(game, ray_list);
    t_ray_node *current = ray_list;

    while (current != NULL)
    {

        t_texture *used_texture = &game->walltextures[current->ray.wall_face];
        // if (i == 400 || i == 399 || i == 401)
        // printf(" Ray #%d - texX: %d,  lineHeight: %d, perpWallDist: %f\n", i, current->ray.texX, current->ray.lineHeight, current->ray.perpWallDist);
        render_ray(&game->img, current->ray, used_texture);
        current = current->next;
        i++;
    }
}

int render(t_game *game)
{
    if (game->win_ptr == NULL)
        return (1);

    handle_movement_left(game);
    handle_movement_right(game);
    handle_movement_forward(game);
    handle_movement_backward(game);
    handle_movement_strafe_left(game);
    handle_movement_strafe_right(game);
    handle_movement_dash(game);
    // render_sky(game, "textures/sky06.xpm");
    render_sky(game, "textures/sky02.xpm");
    // render_sky(&game->img, game->mlx_ptr, "textures/sky02.xpm");
    render_floor(game);
    render_ray_list(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);

    return (0);
}

int setup_game_mlx(t_game *game)
{

    if (game == NULL)
        return (MLX_ERROR);

    game->mlx_ptr = mlx_init();
    if (game->mlx_ptr == NULL)
        return (MLX_ERROR);
    game->win_ptr = mlx_new_window(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "my window");
    if (game->win_ptr == NULL)
    {
        free(game->win_ptr);
        return (MLX_ERROR);
    }
    preload_textures(game);
    initialize_game_seed(game);
    initialize_floor_texture_weights(game);
    initialize_floor_texture_map(game);

    game->img.mlx_img = mlx_new_image(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp,
                                       &game->img.line_len, &game->img.endian);

    // mlx_hook(recup->data.mlx_win, 33, 1L << 17, ft_exit, recup);
    mlx_hook(game->win_ptr, 2, 1L << 0, ft_key_press, game);
    mlx_loop_hook(game->mlx_ptr, &render, game);
    mlx_hook(game->win_ptr, 3, 1L << 1, ft_key_release, game);
    mlx_loop(game->mlx_ptr);

    /* we will exit the loop if there's no window left, and execute this code */
    // mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
    // mlx_destroy_display(game->mlx_ptr);
    // free(game->mlx_ptr);

    return (0);
}
