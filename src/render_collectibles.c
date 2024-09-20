/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:44:50 by toto              #+#    #+#             */
/*   Updated: 2024/08/22 23:09:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int get_pixel_color(t_sprite_render_context *ctx, int tex_x, int tex_y)
{
	if (tex_x < 0 || tex_x >= ctx->texture->width || tex_y < 0 || tex_y >= ctx->texture->height)
		return -1;

	char *pixel = ctx->texture->data + (tex_y * ctx->texture->tex_line_len + tex_x * (ctx->texture->tex_bpp / 8));
	unsigned int color = *(unsigned int *)pixel;

	if (color == 0)
		return -1;

	return color;
}

void init_sprite_render_context(t_sprite_render_context *ctx, t_game *game, t_vector2d position, t_texture *texture)
{
	ctx->game = game;
	ctx->position = position;
	ctx->texture = texture;
}

void calc_sprite_position(t_sprite_render_context *ctx)
{
	ctx->calc.sprite.x = ctx->position.x - ctx->game->player->position.x;
	ctx->calc.sprite.y = ctx->position.y - ctx->game->player->position.y;
}

void transf_sprite(t_sprite_render_context *ctx)
{
	float invDet = 1.0f / (ctx->game->player->plane.x * ctx->game->player->direction.y - ctx->game->player->direction.x * ctx->game->player->plane.y);
	ctx->calc.transform.x = invDet * (ctx->game->player->direction.y * ctx->calc.sprite.x - ctx->game->player->direction.x * ctx->calc.sprite.y);
	ctx->calc.transform.y = invDet * (-ctx->game->player->plane.y * ctx->calc.sprite.x + ctx->game->player->plane.x * ctx->calc.sprite.y);
	ctx->calc.transform.y -= ctx->game->player->height;
}

void calc_sprite_screen_x(t_sprite_render_context *ctx)
{
	ctx->calc.sprite_screen_x = (int)((ctx->game->screen_width / 2) * (1 + ctx->calc.transform.x / ctx->calc.transform.y));
}

void calc_sprite_height(t_sprite_render_context *ctx)
{
	ctx->calc.sprite_height = abs((int)(ctx->game->screen_height / ctx->calc.transform.y)) * OBJECT_SIZE;
	int pitch_offset = (int)(ctx->game->player->pitch * ctx->game->screen_height);
	int height_offset = (int)(ctx->game->player->height * ctx->game->screen_height / ctx->calc.transform.y);

	ctx->calc.draw_start_y = -ctx->calc.sprite_height / 2 + ctx->game->screen_height / 2 + pitch_offset + height_offset;
	ctx->calc.draw_start_y = (ctx->calc.draw_start_y < 0) ? 0 : ctx->calc.draw_start_y;
	ctx->calc.draw_end_y = ctx->calc.sprite_height / 2 + ctx->game->screen_height / 2 + pitch_offset + height_offset;
	ctx->calc.draw_end_y = (ctx->calc.draw_end_y >= ctx->game->screen_height) ? ctx->game->screen_height - 1 : ctx->calc.draw_end_y;
}

void calc_sprite_width(t_sprite_render_context *ctx)
{
	ctx->calc.sprite_width = abs((int)(ctx->game->screen_height / ctx->calc.transform.y)) * OBJECT_SIZE;
	ctx->calc.draw_start_x = -ctx->calc.sprite_width / 2 + ctx->calc.sprite_screen_x;
	ctx->calc.draw_start_x = (ctx->calc.draw_start_x < 0) ? 0 : ctx->calc.draw_start_x;
	ctx->calc.draw_end_x = ctx->calc.sprite_width / 2 + ctx->calc.sprite_screen_x;
	ctx->calc.draw_end_x = (ctx->calc.draw_end_x >= ctx->game->screen_width) ? ctx->game->screen_width - 1 : ctx->calc.draw_end_x;
}

void calc_sprite_transforms(t_sprite_render_context *ctx)
{
	calc_sprite_position(ctx);
	transf_sprite(ctx);
}

void calc_sprite_dimensions(t_sprite_render_context *ctx)
{
	calc_sprite_screen_x(ctx);
	calc_sprite_height(ctx);
	calc_sprite_width(ctx);
}

void draw_sprite_stripe(t_sprite_render_context *ctx, int stripe)
{
	int tex_x = (int)(256 * (stripe - (-ctx->calc.sprite_width / 2 + ctx->calc.sprite_screen_x)) * ctx->texture->width / ctx->calc.sprite_width) / 256;

	t_ray_node *current = find_ray_node(ctx->game, stripe);

	if (current && ctx->calc.transform.y < current->ray.perpWallDist)
	{
		for (int y = ctx->calc.draw_start_y; y < ctx->calc.draw_end_y; y++)
		{
			int pitch_offset = (int)(ctx->game->player->pitch * ctx->game->screen_height);
			int height_offset = (int)(ctx->game->player->height * ctx->game->screen_height / ctx->calc.transform.y);
			int d = (y - pitch_offset - height_offset) * 256 - ctx->game->screen_height * 128 + ctx->calc.sprite_height * 128;
			int tex_y = ((d * ctx->texture->height) / ctx->calc.sprite_height) / 256;

			tex_y = (tex_y < 0) ? 0 : (tex_y >= ctx->texture->height) ? ctx->texture->height - 1 : tex_y;
			int color = get_pixel_color(ctx, tex_x, tex_y);
			if (color != -1)
				img_pix_put(&ctx->game->img, stripe, y, color);
		}
	}
}

void render_sprite(t_sprite_render_context *ctx)
{
	for (int stripe = ctx->calc.draw_start_x; stripe < ctx->calc.draw_end_x; stripe++)
	{
		if (is_sprite_in_front(ctx->calc.transform.y, stripe, ctx->game->screen_width))
		{
			draw_sprite_stripe(ctx, stripe);
		}
	}
}

void render_sprite_common(t_game *game, t_vector2d position, t_texture *texture)
{
	t_sprite_render_context ctx;
	init_sprite_render_context(&ctx, game, position, texture);

	calc_sprite_transforms(&ctx);
	calc_sprite_dimensions(&ctx);
	render_sprite(&ctx);
}


