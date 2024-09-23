/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:52:34 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 12:52:34 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_pixel_color(t_sprite_render_context *ctx, t_vector2d tex)
{
	char			*pixel;
	unsigned int	color;

	if (tex.x < 0 || tex.x >= ctx->texture->width \
	|| tex.y < 0 || tex.y >= ctx->texture->height)
		return (-1);
	pixel = ctx->texture->data + ((int)tex.y \
	* ctx->texture->tex_line_len + (int)tex.x * (ctx->texture->tex_bpp / 8));
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

float	calculate_sprite_tex_x(t_sprite_render_context *ctx, int stripe)
{
	return ((256.0f * (stripe - (-ctx->calc.s_width \
	/ 2 + ctx->calc.sprite_screen_x)) \
	* ctx->texture->width / ctx->calc.s_width) / 256.0f);
}

void	draw_sprite_stripe(t_sprite_render_context *ctx, int stripe)
{
	t_vector2d	tex;
	t_ray_node	*current;
	int			y;
	int			d;
	int			color;

	tex.x = (int)calculate_sprite_tex_x(ctx, stripe);
	current = find_ray_node(ctx->game, stripe);
	if (current && ctx->calc.transform.y < current->ray.perpwalldist)
	{
		y = ctx->calc.draw_start_y;
		while (y < ctx->calc.draw_end_y)
		{
			d = calc_sprite_dist(ctx, y);
			tex.y = ((d * ctx->texture->height) / ctx->calc.s_height) / 256;
			if (tex.y < 0)
				tex.y = 0;
			else if (tex.y >= ctx->texture->height)
				tex.y = ctx->texture->height - 1;
			color = get_pixel_color(ctx, tex);
			if (color != -1)
				img_pix_put(&ctx->game->img, stripe, y, color);
			y++;
		}
	}
}

void	render_sprite(t_sprite_render_context *ctx)
{
	int	stripe;

	stripe = ctx->calc.draw_start_x;
	while (stripe < ctx->calc.draw_end_x)
	{
		if (is_sprite_in_front(ctx->calc.transform.y, \
		stripe, ctx->game->screen_width))
			draw_sprite_stripe(ctx, stripe);
		stripe++;
	}
}

void	render_sprite_common(t_game *game, \
t_vector2d position, t_texture *texture)
{
	t_sprite_render_context	ctx;

	init_sprite_render_context(&ctx, game, position, texture);
	calc_sprite_transforms(&ctx);
	calc_sprite_dimensions(&ctx);
	render_sprite(&ctx);
}
