/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus12.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:15:11 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/25 17:21:30 by vitenner         ###   ########.fr       */
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

    if (!ctx || !ctx->texture || !ctx->texture->data)
        return (-1);
    if (tex.x < 0 || tex.x >= ctx->texture->width \
    || tex.y < 0 || tex.y >= ctx->texture->height)
        return (-1);

    // Calculate the offset
    size_t offset = (size_t)((int)tex.y * ctx->texture->line_len + (int)tex.x * (ctx->texture->bpp / 8));

    // Check if the offset is within the texture data bounds
    size_t texture_size = (size_t)ctx->texture->width * (size_t)ctx->texture->height * ((size_t)ctx->texture->bpp / 8);
    if (offset >= texture_size)
        return (-1);

    pixel = ctx->texture->data + offset;

    // Additional check to ensure we're not reading past the end of the texture data
    if ((uintptr_t)pixel >= (uintptr_t)ctx->texture->data + texture_size)
        return (-1);

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
