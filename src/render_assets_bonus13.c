/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus13.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:15:09 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:15:40 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calc_s_height(t_sprite_render_context *ctx)
{
	int	pitch_offset;
	int	height_offset;

	ctx->calc.s_height = abs((int)(ctx->game->screen_height \
	/ ctx->calc.transform.y)) * OBJECT_SIZE;
	pitch_offset = (int)(ctx->game->player->pitch \
	* ctx->game->screen_height);
	height_offset = (int)(ctx->game->player->height \
	* ctx->game->screen_height / ctx->calc.transform.y);
	ctx->calc.draw_start_y = -ctx->calc.s_height \
	/ 2 + ctx->game->screen_height / 2 + pitch_offset + height_offset;
	if (ctx->calc.draw_start_y < 0)
		ctx->calc.draw_start_y = 0;
	ctx->calc.draw_end_y = ctx->calc.s_height \
	/ 2 + ctx->game->screen_height / 2 + pitch_offset + height_offset;
	if (ctx->calc.draw_end_y >= ctx->game->screen_height)
		ctx->calc.draw_end_y = ctx->game->screen_height - 1;
}

void	calc_s_width(t_sprite_render_context *ctx)
{
	ctx->calc.s_width = abs((int)(ctx->game->screen_height \
	/ ctx->calc.transform.y)) * OBJECT_SIZE;
	ctx->calc.draw_start_x = -ctx->calc.s_width / 2 \
	+ ctx->calc.sprite_screen_x;
	if (ctx->calc.draw_start_x < 0)
		ctx->calc.draw_start_x = 0;
	ctx->calc.draw_end_x = ctx->calc.s_width / 2 \
	+ ctx->calc.sprite_screen_x;
	if (ctx->calc.draw_end_x >= ctx->game->screen_width)
		ctx->calc.draw_end_x = ctx->game->screen_width - 1;
}

void	calc_sprite_transforms(t_sprite_render_context *ctx)
{
	calc_sprite_position(ctx);
	transf_sprite(ctx);
}

void	calc_sprite_dimensions(t_sprite_render_context *ctx)
{
	calc_sprite_screen_x(ctx);
	calc_s_height(ctx);
	calc_s_width(ctx);
}

int	calc_sprite_dist(t_sprite_render_context *ctx, int y)
{
	int	pitch_offset;
	int	height_offset;
	int	dist;

	pitch_offset = (int)(ctx->game->player->pitch \
	* ctx->game->screen_height);
	height_offset = (int)(ctx->game->player->height \
	* ctx->game->screen_height / ctx->calc.transform.y);
	dist = (y - pitch_offset - height_offset) * 256 \
	- ctx->game->screen_height * 128 + ctx->calc.s_height * 128;
	return (dist);
}
