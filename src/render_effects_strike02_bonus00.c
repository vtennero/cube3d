/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike02_bonus00.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:48:45 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/20 16:50:00 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_vector2d generate_random_offset(t_game *game, float proximity_radius)
{
	float angle = random_float(game) * 2 * M_PI;
	float distance = random_float(game) * proximity_radius;

	t_vector2d offset;
	offset.x = cosf(angle) * distance;
	offset.y = sinf(angle) * distance;

	return offset;
}

t_vector2d calculate_new_position(t_vector2d base_position, t_vector2d offset)
{
	t_vector2d new_position;
	new_position.x = base_position.x + offset.x;
	new_position.y = base_position.y + offset.y;
	return new_position;
}

t_vector2d clamp_position(t_vector2d position, int map_width, int map_height)
{
	t_vector2d clamped;
	clamped.x = fmax(0, fmin(position.x, map_width - 1));
	clamped.y = fmax(0, fmin(position.y, map_height - 1));
	return clamped;
}

void reset_strike_parameters(t_strike *strike)
{
	strike->frame_count = 0;
	strike->current_frame = 0;
	strike->is_active = 1;
	strike->is_launching = 1;
	strike->is_animating = 0;
	strike->delay_frames = 0;
	strike->delay_duration = 60 * 2; // 3 seconds at 60 FPS, adjust as needed
}


void print_barrage_loc(t_vector2d new_position, t_vector2d base_position)
{
	printf("New barrage location: (%f, %f), Base position: (%f, %f)\n",
		   new_position.x, new_position.y,
		   base_position.x, base_position.y);
}

void randomize_barrage_location(t_game *game)
{
	int map_width = game->map->width;
	int map_height = game->map->height;
	float proximity_radius = 10.0f;

	t_vector2d offset = generate_random_offset(game, proximity_radius);
	t_vector2d new_position = calculate_new_position(game->strike[2].base_position, offset);
	new_position = clamp_position(new_position, map_width, map_height);

	int attempts = 0;
	while (!is_valid_location(game, (int)new_position.x, (int)new_position.y) && attempts < 10)
	{
		offset = generate_random_offset(game, proximity_radius);
		new_position = calculate_new_position(game->strike[2].base_position, offset);
		new_position = clamp_position(new_position, map_width, map_height);
		attempts++;
	}

	game->strike[2].position.x = new_position.x;
	game->strike[2].position.y = new_position.y;

	reset_strike_parameters(&game->strike[2]);
	print_barrage_loc(new_position, game->strike[2].base_position);
}


int get_next_barrage_frame(t_strike *strike)
{
	strike->frame_count++;

	if (strike->frame_count % AIRSTRIKE_ANIMATION_INTERVAL == 0)
		strike->current_frame = (strike->current_frame + 1) % NUM_AIRSTRIKE_FRAMES;
	return strike->current_frame;
}

void handle_frame_specific_actions(t_game *game, int current_frame)
{
	if (current_frame == 17)
		add_script(game, play_barrage_shell, 1);
	if (current_frame == NUM_AIRSTRIKE_FRAMES - 1)
	{
		game->strike[2].is_animating = 0;
		game->strike[2].delay_frames = 0;
		printf("render_ongoing_barrage: Completed full animation cycle, randomizing location\n");
		printf("Barrage Hit\n");
		randomize_barrage_location(game);
	}
}
void adjust_barrage_sprite_dimensions_for_scaling(t_sprite_calc *calc)
{
	int centerY = (calc->draw_start_y + calc->draw_end_y) / 2;
	int heightDiff = calc->draw_end_y - calc->draw_start_y;
	calc->draw_start_y = centerY - (int)(heightDiff * STRIKE_BARRAGE_SCALE / 2);
	calc->draw_end_y = centerY + (int)(heightDiff * STRIKE_BARRAGE_SCALE / 2);
	int centerX = (calc->draw_start_x + calc->draw_end_x) / 2;
	int widthDiff = calc->draw_end_x - calc->draw_start_x;
	calc->draw_start_x = centerX - (int)(widthDiff * STRIKE_BARRAGE_SCALE / 2);
	calc->draw_end_x = centerX + (int)(widthDiff * STRIKE_BARRAGE_SCALE / 2);
}


int initialize_barrage(t_game *game)
{
	if (!game->strike[2].is_active)
		return -1;

	return get_next_barrage_frame(&game->strike[2]);
}

void apply_barrage_screen_shake(t_game *game, int current_frame)
{
	float shake_offset = calculate_screen_shake(game, current_frame);
	if (game->player->is_dead == 0)
		game->player->height = PLAYER_B_HEIGHT + shake_offset;
}

void render_ongoing_barrage(t_game *game)
{
	int current_frame = initialize_barrage(game);
	if (current_frame == -1) return;

	apply_barrage_screen_shake(game, current_frame);
	render_barrage_sprite(game, current_frame);
	handle_frame_specific_actions(game, current_frame);
}

void render_barrage(t_game *game)
{
	if (game->strike[2].is_launching)
		render_call_strike(game, game->strike[2].base_position);
	if (game->strike[2].is_active)
	{
		if (!game->strike[2].is_animating)
		{
			if (game->strike[2].delay_frames >= game->strike[2].delay_duration)
			{
				game->strike[2].is_animating = 1;
				game->strike[2].current_frame = 0;
				game->strike[2].frame_count = 0;
			}
			else
				game->strike[2].delay_frames++;
		}
		if (game->strike[2].is_animating)
			render_ongoing_barrage(game);
	}
}

void calculate_barrage_sprite_position(t_game *game, t_vector2d *position, t_vector2d *sprite)
{
	t_sprite_render_context ctx;
	init_sprite_render_context(&ctx, game, *position, NULL);
	calc_sprite_position(&ctx);
	*sprite = ctx.calc.sprite;
}

void transform_barrage_sprite(t_game *game, t_vector2d sprite, t_vector2d *transform)
{
	t_sprite_render_context ctx;
	init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);
	ctx.calc.sprite = sprite;
	transf_sprite(&ctx);
	*transform = ctx.calc.transform;
}

void calculate_barrage_sprite_screen_x(t_game *game, t_vector2d transform, int *spriteScreenX)
{
	t_sprite_render_context ctx;
	init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);
	ctx.calc.transform = transform;
	calc_sprite_screen_x(&ctx);
	*spriteScreenX = ctx.calc.sprite_screen_x;
}

void calculate_barrage_sprite_dimensions(t_game *game, float transformY, t_sprite_calc *calc)
{
	t_sprite_render_context ctx;
	init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);
	ctx.calc.transform.y = transformY / STRIKE_BARRAGE_SCALE;
	ctx.calc.sprite_screen_x = calc->sprite_screen_x;

	calc_sprite_height(&ctx);
	calc_sprite_width(&ctx);

	calc->sprite_height = ctx.calc.sprite_height;
	calc->draw_start_y = ctx.calc.draw_start_y;
	calc->draw_end_y = ctx.calc.draw_end_y;
	calc->sprite_width = ctx.calc.sprite_width;
	calc->draw_start_x = ctx.calc.draw_start_x;
	calc->draw_end_x = ctx.calc.draw_end_x;
}

void setup_barrage_sprite_context(t_sprite_render_context *ctx, t_game *game, t_vector2d position, t_texture *texture)
{
	init_sprite_render_context(ctx, game, position, texture);
	calc_sprite_transforms(ctx);
	calc_sprite_dimensions(ctx);

	// Adjust for STRIKE_BARRAGE_SCALE
	adjust_barrage_sprite_dimensions_for_scaling(&ctx->calc);

	ctx->calc.sprite_height *= STRIKE_BARRAGE_SCALE;
	ctx->calc.sprite_width *= STRIKE_BARRAGE_SCALE;
}

void render_barrage_sprite(t_game *game, int current_frame)
{
	t_sprite_render_context ctx;
	t_vector2d position = game->strike[2].position;
	t_texture *strike_texture = &game->airstrike_textures[current_frame];

	setup_barrage_sprite_context(&ctx, game, position, strike_texture);

	render_sprite(&ctx);
}
