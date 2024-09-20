/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strikes_bonus00.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:55:16 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/20 14:55:16 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float calculate_screen_shake(t_game *game, int current_frame)
{
	if (current_frame >= STRIKE_SHAKE_DURATION || game->player->is_dead == 1)
		return 0.0f;

	// Use the random number generator for unpredictable shake
	float random_offset = (float)random_int(game, 1000) / 1000.0f;

	// Calculate a decreasing intensity over time
	float intensity = STRIKE_SHAKE_INTENSITY * (1.0f - (float)current_frame / STRIKE_SHAKE_DURATION);

	// Use a sine wave for a bouncing effect
	float shake = sinf(current_frame * 0.5f) * intensity;

	// Combine the sine wave with the random offset for more chaotic movement
	return shake * random_offset;
}

int	calculate_color_with_base(int i, int total_width, int white_width, int base_color)
{
	float	gradient;
	int		color_value;

	if (i == 0 || (i >= -white_width / 2 && i < white_width / 2))
		return (0xFFFFFF);
	else
	{
		gradient = 1.0f - (float)abs(i) / (total_width / 2);
		color_value = 128 + (int)(127 * gradient);
		return (color_value << (base_color == 0xFF0000 ? 16 : 0));
	}
}

void	draw_strike_call(t_game *game, int stripe, int draw_end_y, float distance)
{
	int	total_width;
	int	white_width;
	int	y;
	int	i;
	int	color;

	calculate_widths(game, distance, &total_width, &white_width);
	y = 0;
	while (y < draw_end_y)
	{
		i = -total_width / 2;
		while (i < total_width / 2)
		{
			color = calculate_color_with_base(i, total_width, white_width, 0xFF0000);
			draw_stripe_pixel(game, stripe + i, y, color);
			i++;
		}
		y++;
	}
}

void render_call_strike(t_game *game, t_vector2d position)
{
	t_sprite_render_context ctx;
	init_sprite_render_context(&ctx, game, position, NULL);

	calc_sprite_transforms(&ctx);
	calc_sprite_dimensions(&ctx);

	float distance = calculate_distance_to_player(game, position);

	int stripe = ctx.calc.sprite_screen_x;
	if (ctx.calc.transform.y > 0 && stripe > 0 && stripe < game->screen_width)
		draw_strike_call(game, stripe, ctx.calc.draw_end_y, distance);
}

void reset_strike(t_game *game)
{
	game->strike[0].is_active = 0;
	game->strike[0].is_animating = 0;
	for (int i = 0; i < NUM_OFFSETS; i++)
	{
		game->strike[0].frame_counts[i] = rand() % (NUM_AIRSTRIKE_FRAMES * 100);
	}
}

void setup_sprite_context(t_sprite_render_context *ctx, t_game *game, t_vector2d offset, t_texture *texture)
{
	ctx->texture = texture;
	ctx->position.x = game->strike[0].position.x + offset.x;
	ctx->position.y = game->strike[0].position.y + offset.y;

	calc_sprite_transforms(ctx);
	calc_sprite_dimensions(ctx);
}

void render_single_sprite(t_sprite_render_context *ctx)
{
	for (int stripe = ctx->calc.draw_start_x; stripe < ctx->calc.draw_end_x; stripe++)
	{
		if (is_sprite_in_front(ctx->calc.transform.y, stripe, ctx->game->screen_width))
			draw_sprite_stripe(ctx, stripe);
	}
}






