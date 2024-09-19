/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:49:50 by toto              #+#    #+#             */
/*   Updated: 2024/08/23 11:44:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calculate_perpendicular(t_game *game, float *perp_x, float *perp_y)
{
	float	view_angle;

	view_angle = atan2(game->player->direction.y, game->player->direction.x);
	*perp_x = -sin(view_angle);
	*perp_y = cos(view_angle);
}

void	render_single_tile(t_game *game, t_vector2d tile_pos, int tex_index)
{
	t_texture	*extract_texture;

	extract_texture = &game->extract_texture[tex_index];
	col_render_sprite_common(game, tile_pos, extract_texture);
}

void	calculate_widths(t_game *game, float distance, int *total_width, \
int *white_width)
{
	*total_width = (int)(0.05 * game->screen_width / distance);
	if (*total_width < 3)
		*total_width = 3;
	if (*total_width < 3)
		*white_width = 1;
	else
		*white_width = *total_width / 2;
}

void	draw_stripe_pixel(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < game->screen_width)
		img_pix_put(&game->img, x, y, color);
}

void	draw_extract_stripe(t_game *game, int s, int start_y, float d)
{
	int	total_width;
	int	white_width;
	int	y;
	int	i;
	int	color;

	calculate_widths(game, d, &total_width, &white_width);
	y = 0;
	while (y < start_y)
	{
		i = -total_width / 2;
		while (i < total_width / 2)
		{
			color = calculate_color_with_base(i, total_width, white_width, 0x0000FF);
			draw_stripe_pixel(game, s + i, y, color);
			i++;
		}
		y++;
	}
}

int	is_extract_active(t_game *game)
{
	return (game->extract[0].is_available == 1 \
	|| game->extract[0].is_activated == 1);
}

float	calculate_distance_to_player(t_game *game, t_vector2d position)
{
	float	dx;
	float	dy;

	dx = position.x - game->player->position.x;
	dy = position.y - game->player->position.y;
	return (sqrt(dx * dx + dy * dy));
}

void	render_extract_ray(t_sprite_render_context *ctx)
{
	float	distance;

	col_calculate_sprite_transforms(ctx);
	col_calculate_sprite_dimensions(ctx);
	if (is_sprite_in_front(ctx->calc.transform_y, \
	ctx->calc.sprite_screen_x, ctx->game->screen_width))
	{
		distance = calculate_distance_to_player(ctx->game, ctx->position);
		draw_extract_stripe(ctx->game, ctx->calc.sprite_screen_x, \
		ctx->calc.draw_start_y, distance);
	}
}

void	render_active_extract(t_game *game)
{
	t_sprite_render_context	ctx;

	col_initialize_sprite_render_context(&ctx, game, \
	game->extract[0].position, &game->extract_texture[0]);
	col_render_sprite_common(ctx.game, ctx.position, ctx.texture);
	if (game->extract[0].is_available == 1)
		render_extract_ray(&ctx);
}

t_vector2d	calculate_tile_position(t_vector2d base, t_vector2d perp, int i)
{
	float	offset;

	offset = (i - (EXTRACT_N_TILES - 1) / 2.0f) * EXTRACT_OFFSET;
	return ((t_vector2d){
		base.x + perp.x * offset,
		base.y + perp.y * offset
	});
}

void	render_extract_multi_tile(t_game *game, t_vector2d base)
{
	t_vector2d				perp;
	t_sprite_render_context	ctx;
	int						i;

	calculate_perpendicular(game, &perp.x, &perp.y);
	col_initialize_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);
	i = 0;
	while (i < EXTRACT_N_TILES)
	{
		ctx.position = calculate_tile_position(base, perp, i);
		ctx.texture = &game->extract_texture[i + 1];
		col_render_sprite_common(ctx.game, ctx.position, ctx.texture);
		i++;
	}
}

void	render_extract(t_game *game)
{
	if (is_extract_active(game))
		render_active_extract(game);
	else if (game->extract[0].is_landing == 1)
		render_extract_multi_tile(game, game->extract[0].position);
}
