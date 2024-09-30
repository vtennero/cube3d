/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus11.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:15:51 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:15:51 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	calculate_sprite_tex_x(t_sprite_render_context *ctx, int stripe)
{
	return ((256.0f * (stripe - (-ctx->calc.s_width \
	/ 2 + ctx->calc.sprite_screen_x)) \
	* ctx->texture->width / ctx->calc.s_width) / 256.0f);
}

void	draw_sprite_pixel(t_sprite_render_context *ctx, \
int stripe, int y, t_vector2d tex)
{
	int	color;

	color = get_pixel_color(ctx, tex);
	if (color != -1)
		img_pix_put(&ctx->game->img, stripe, y, color);
}

t_vector2d	calculate_texture_coordinates(t_sprite_render_context \
*ctx, int y, int d, int tex_x)
{
	t_vector2d	tex;

	(void)y;
	tex.x = tex_x;
	tex.y = ((d * ctx->texture->height) / ctx->calc.s_height) / 256;
	if (tex.y < 0)
		tex.y = 0;
	else if (tex.y >= ctx->texture->height)
		tex.y = ctx->texture->height - 1;
	if (tex.x < 0)
		tex.x = 0;
	else if (tex.x >= ctx->texture->width)
		tex.x = ctx->texture->width - 1;
	return (tex);
}

void	draw_sprite_stripe(t_sprite_render_context *ctx, int stripe)
{
	t_vector2d	tex;
	t_ray_node	*current;
	int			y;
	int			d;
	int			tex_x;

	tex_x = calculate_sprite_tex_x(ctx, stripe);
	current = find_ray_node(ctx->game, stripe);
	if (current && ctx->calc.transform.y < current->ray.perpwalldist)
	{
		y = ctx->calc.draw_start_y;
		while (y < ctx->calc.draw_end_y)
		{
			d = calc_sprite_dist(ctx, y);
			tex = calculate_texture_coordinates(ctx, y, d, tex_x);
			draw_sprite_pixel(ctx, stripe, y, tex);
			y++;
		}
	}
}

void	render_sprite_common(t_game *game, \
t_vector2d position, t_texture *texture)
{
	t_sprite_render_context	ctx;

	init_sprite_render_context(&ctx, game, position, texture);
	calc_sprite_transforms(&ctx);
	calc_sprite_dimensions(&ctx);
	render_single_sprite(&ctx);
}
