/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus12.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:15:11 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/25 17:45:06 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// int	get_pixel_color(t_sprite_render_context *ctx, t_vector2d tex)
// {
// 	char			*pixel;
// 	unsigned int	color;

// 	if (!ctx || !ctx->texture || !ctx->texture->data)
// 		return (-1);
// 	if (tex.x < 0 || tex.x >= ctx->texture->width
// 	|| tex.y < 0 || tex.y >= ctx->texture->height)
// 		return (-1);
// 	pixel = ctx->texture->data + ((int)tex.y
// 	* ctx->texture->line_len + (int)tex.x * (ctx->texture->bpp / 8));
// 	color = *(unsigned int *)pixel;
// 	if (color == 0)
// 		return (-1);
// 	return (color);
// }

int get_pixel_color(t_sprite_render_context *ctx, t_vector2d tex)
{
    if (!ctx || !ctx->texture || !ctx->texture->data)
    {
        printf("Error: Null pointer detected (ctx: %p, texture: %p, data: %p)\n",
               (void*)ctx, ctx ? (void*)ctx->texture : NULL,
               (ctx && ctx->texture) ? (void*)ctx->texture->data : NULL);
        return (-1);
    }

    // Check if texture dimensions are valid
    if (ctx->texture->width <= 0 || ctx->texture->height <= 0 ||
        ctx->texture->bpp <= 0 || ctx->texture->line_len <= 0)
    {
        printf("Error: Invalid texture dimensions or properties\n");
        return (-1);
    }

    // Stricter bound checking
    if (tex.x < 0 || tex.x >= ctx->texture->width ||
        tex.y < 0 || tex.y >= ctx->texture->height ||
        isnan(tex.x) || isnan(tex.y))
    {
        printf("Error: Texture coordinates out of bounds or NaN. tex: (%.2f, %.2f), dimensions: %d x %d\n",
               tex.x, tex.y, ctx->texture->width, ctx->texture->height);
        return (-1);
    }

    size_t offset = (size_t)((int)tex.y * ctx->texture->line_len + (int)tex.x * (ctx->texture->bpp / 8));
    size_t texture_size = (size_t)ctx->texture->width * (size_t)ctx->texture->height * ((size_t)ctx->texture->bpp / 8);

    if (offset >= texture_size)
    {
        printf("Error: Calculated offset out of bounds. offset: %zu, texture_size: %zu\n",
               offset, texture_size);
        return (-1);
    }

    char *pixel = ctx->texture->data + offset;

    // Check both lower and upper bounds
    if ((uintptr_t)pixel < (uintptr_t)ctx->texture->data ||
        (uintptr_t)pixel + sizeof(unsigned int) > (uintptr_t)ctx->texture->data + texture_size)
    {
        printf("Error: Pixel pointer out of bounds. pixel: %p, valid range: [%p, %p)\n",
               (void*)pixel, (void*)ctx->texture->data,
               (void*)((uintptr_t)ctx->texture->data + texture_size));
        return (-1);
    }

    unsigned int color = *(unsigned int *)pixel;

    // Reintroduced check for color == 0
    if (color == 0)
        return (-1);

    return color;
}

// void	init_sprite_render_context(t_sprite_render_context *ctx,
// t_game *game, t_vector2d position, t_texture *texture)
// {
// 	ctx->game = game;
// 	ctx->position = position;
// 	ctx->texture = texture;
// }

#include <ctype.h>

int is_texture_valid(t_texture *texture)
{
    if (!texture)
    {
        printf("Error: Texture pointer is NULL\n");
        return 0;
    }

    printf("Texture validation for texture at %p:\n", (void*)texture);
    printf("  Path: %s\n", texture->path ? texture->path : "NULL");
    printf("  Data pointer: %p\n", (void*)texture->data);
    printf("  Dimensions: %d x %d\n", texture->width, texture->height);
    printf("  BPP: %d, Line length: %d\n", texture->bpp, texture->line_len);

    if (texture->data)
    {
        printf("  First 20 characters of data: ");
        for (int i = 0; i < 20 && texture->data[i]; i++)
        {
            char c = texture->data[i];
            if (isprint(c))
                printf("%c", c);
            else
                printf(".");
        }
        printf("\n");
    }

    if (!texture->data ||
        texture->width <= 0 || texture->height <= 0 ||
        texture->bpp <= 0 || texture->line_len <= 0)
    {
        printf("Error: Invalid texture properties\n");
        return 0;  // 0 indicates invalid texture
    }

    return 1;  // 1 indicates valid texture
}

int init_sprite_render_context(t_sprite_render_context *ctx,
                               t_game *game, t_vector2d position, t_texture *texture)
{
    if (!ctx || !game)
    {
        printf("Error: Null context or game pointer\n");
        return 0;  // Initialization failed
    }

    printf("Initializing sprite render context:\n");
    printf("  Position: (%.2f, %.2f)\n", position.x, position.y);

    if (!is_texture_valid(texture))
    {
        printf("Error: Invalid texture passed to init_sprite_render_context\n");
        return 0;  // Initialization failed
    }

    ctx->game = game;
    ctx->position = position;
    ctx->texture = texture;

    return 1;  // Initialization succeeded
}

void	calc_sprite_position(t_sprite_render_context *ctx)
{
	ctx->calc.sprite.x = ctx->position.x - ctx->game->player->position.x;
	ctx->calc.sprite.y = ctx->position.y - ctx->game->player->position.y;
}

void	transf_sprite(t_sprite_render_context *ctx)
{
	float	inv_det;

	inv_det = 1.0f / (ctx->game->player->plane.x \
	* ctx->game->player->direction.y - ctx->game->player->direction.x \
	* ctx->game->player->plane.y);
	ctx->calc.transform.x = inv_det * (ctx->game->player->direction.y \
	* ctx->calc.sprite.x \
	- ctx->game->player->direction.x * ctx->calc.sprite.y);
	ctx->calc.transform.y = inv_det * (-ctx->game->player->plane.y \
	* ctx->calc.sprite.x \
	+ ctx->game->player->plane.x * ctx->calc.sprite.y);
	ctx->calc.transform.y -= ctx->game->player->height;
}

void	calc_sprite_screen_x(t_sprite_render_context *ctx)
{
	ctx->calc.sprite_screen_x = (int)((ctx->game->screen_width / 2) \
	* (1 + ctx->calc.transform.x / ctx->calc.transform.y));
}
