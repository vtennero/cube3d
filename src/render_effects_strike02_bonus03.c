/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike02_bonus03.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:54:58 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/30 16:20:20 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calculate_barrage_sprite_screen_x(t_game *game, \
t_vector2d transform, int *sprite_screen_x)
{
	t_sprite_render_context	ctx;

	init_sprite_render_context(&ctx, game, \
	(t_vector2d){0, 0}, &game->t_extract[0]);
	ctx.calc.transform = transform;
	calc_sprite_screen_x(&ctx);
	*sprite_screen_x = ctx.calc.sprite_screen_x;
}

void	calculate_barrage_sprite_dimensions(t_game *game, \
float transform_y, t_sprite_calc *calc)
{
	t_sprite_render_context	ctx;

	init_sprite_render_context(&ctx, game, \
	(t_vector2d){0, 0}, &game->t_extract[0]);
	ctx.calc.transform.y = transform_y / STRIKE_BARRAGE_SCALE;
	ctx.calc.sprite_screen_x = calc->sprite_screen_x;
	calc_s_height(&ctx);
	calc_s_width(&ctx);
	calc->s_height = ctx.calc.s_height;
	calc->draw_start_y = ctx.calc.draw_start_y;
	calc->draw_end_y = ctx.calc.draw_end_y;
	calc->s_width = ctx.calc.s_width;
	calc->draw_start_x = ctx.calc.draw_start_x;
	calc->draw_end_x = ctx.calc.draw_end_x;
}

void	setup_barrage_sprite_context(t_sprite_render_context *ctx, \
t_game *game, t_vector2d position, t_texture *texture)
{
	init_sprite_render_context(ctx, game, position, texture);
	calc_sprite_transforms(ctx);
	calc_sprite_dimensions(ctx);
	adjust_barrage_sprite_dimensions(&ctx->calc);
	ctx->calc.s_height *= STRIKE_BARRAGE_SCALE;
	ctx->calc.s_width *= STRIKE_BARRAGE_SCALE;
}

void	render_barrage_sprite(t_game *game, int current_frame)
{
	t_sprite_render_context	ctx;
	t_vector2d				position;
	t_texture				*strike_texture;

	position = game->strike[2].position;
	strike_texture = &game->t_eagle[current_frame];
	setup_barrage_sprite_context(&ctx, game, position, strike_texture);
	render_single_sprite(&ctx);
}
