/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus12.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:15:11 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/25 17:25:38 by vitenner         ###   ########.fr       */
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
    char            *pixel;
    unsigned int    color;

    // Debug print
    printf("Debug: get_pixel_color\n");
    printf("Context: %p\n", (void*)ctx);
    if (ctx) {
        printf("Position: (%.2f, %.2f)\n", ctx->position.x, ctx->position.y);
        printf("Texture: %p\n", (void*)ctx->texture);
        if (ctx->texture) {
            printf("Texture path: %s\n", ctx->texture->path ? ctx->texture->path : "NULL");
            printf("Texture data: %p\n", (void*)ctx->texture->data);
            printf("Texture dimensions: %d x %d\n", ctx->texture->width, ctx->texture->height);
            printf("Texture bpp: %d, line_len: %d, endian: %d\n",
                   ctx->texture->bpp, ctx->texture->line_len, ctx->texture->endian);
        }
    }
    printf("Texture coordinates: (%.2f, %.2f)\n", tex.x, tex.y);

    if (!ctx || !ctx->texture || !ctx->texture->data)
    {
        printf("Error: Null pointer detected\n");
        return (-1);
    }
    if (tex.x < 0 || tex.x >= ctx->texture->width \
    || tex.y < 0 || tex.y >= ctx->texture->height)
    {
        printf("Error: Texture coordinates out of bounds\n");
        return (-1);
    }

    size_t offset = (size_t)((int)tex.y * ctx->texture->line_len + (int)tex.x * (ctx->texture->bpp / 8));
    size_t texture_size = (size_t)ctx->texture->width * (size_t)ctx->texture->height * ((size_t)ctx->texture->bpp / 8);

    if (offset >= texture_size)
    {
        printf("Error: Calculated offset out of bounds\n");
        return (-1);
    }

    pixel = ctx->texture->data + offset;

    if ((uintptr_t)pixel >= (uintptr_t)ctx->texture->data + texture_size)
    {
        printf("Error: Pixel pointer out of bounds\n");
        return (-1);
    }

    color = *(unsigned int *)pixel;
    if (color == 0)
        return (-1);
    return (color);
}

void	init_sprite_render_context(t_sprite_render_context *ctx, \
t_game *game, t_vector2d position, t_texture *texture)
{
	ctx->game = game;
	ctx->position = position;
	ctx->texture = texture;
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
