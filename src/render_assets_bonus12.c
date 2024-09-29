/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus12.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:15:11 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/29 16:35:01 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_pixel_color(t_sprite_render_context *ctx, t_vector2d tex)
{
	char			*pixel;
	unsigned int	color;

	if (!ctx || !ctx->texture || !ctx->texture->data)
		return (-1);
	if (tex.y < 0 || tex.y >= ctx->texture->width || tex.x < 0
		|| tex.x >= ctx->texture->height)
		return (-1);
	pixel = ctx->texture->data + ((int)tex.y * ctx->texture->line_len
			+ (int)tex.x * (ctx->texture->bpp / 8));
	if (pixel < ctx->texture->data || pixel >= ctx->texture->data
		+ (ctx->texture->line_len * ctx->texture->height))
	{
		return (-1);
	}
	color = *(unsigned int *)pixel;
	if (color == 0)
		return (-1);
	return (color);
}

int	init_sprite_render_context(t_sprite_render_context *ctx, t_game *game,
		t_vector2d position, t_texture *texture)
{
	ctx->game = game;
	ctx->position = position;
	ctx->texture = texture;
	return (-1);
}

void	calc_sprite_position(t_sprite_render_context *ctx)
{
	ctx->calc.sprite.x = ctx->position.x - ctx->game->player->position.x;
	ctx->calc.sprite.y = ctx->position.y - ctx->game->player->position.y;
}

void	transf_sprite(t_sprite_render_context *ctx)
{
	float	inv_det;

	inv_det = 1.0f / (ctx->game->player->plane.x
			* ctx->game->player->direction.y - ctx->game->player->direction.x
			* ctx->game->player->plane.y);
	ctx->calc.transform.x = inv_det * (ctx->game->player->direction.y
			* ctx->calc.sprite.x - ctx->game->player->direction.x
			* ctx->calc.sprite.y);
	ctx->calc.transform.y = inv_det * (-ctx->game->player->plane.y
			* ctx->calc.sprite.x + ctx->game->player->plane.x
			* ctx->calc.sprite.y);
	ctx->calc.transform.y -= ctx->game->player->height;
}

void	calc_sprite_screen_x(t_sprite_render_context *ctx)
{
	ctx->calc.sprite_screen_x = (int)((ctx->game->screen_width / 2) * (1
				+ ctx->calc.transform.x / ctx->calc.transform.y));
}
