/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike00_bonus00.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:49:42 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/20 16:34:40 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int initialize_eagle_strike(t_game *game)
{
	if (!game->strike[0].is_active)
		return -1;

	int min_index = get_min_starting_index_eagle(&game->strike[0]);
	int current_frame = get_next_eagle_frame(&game->strike[0], min_index);

	if (game->strike[0].frame_counts[min_index] >= NUM_AIRSTRIKE_FRAMES * 100)
	{
		reset_strike(game);
		return -1;
	}

	return current_frame;
}

int get_min_starting_index_eagle(t_strike *strike)
{
	int min_index = 0;
	for (int i = 1; i < NUM_OFFSETS; i++)
	{
		if (strike->frame_counts[i] < strike->frame_counts[min_index])
		{
			min_index = i;
		}
	}
	return min_index;
}


void eagle_apply_screen_shake(t_game *game, int current_frame)
{
	float shake_offset = calculate_screen_shake(game, current_frame);
	if (game->player->is_dead == 0)
		game->player->height = PLAYER_B_HEIGHT + shake_offset;
}

void render_eagle_sprites(t_game *game)
{
	t_vector2d offsets[NUM_OFFSETS] = {
		{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1},
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1},
		{2, 0}, {-2, 0}, {0, 2}, {0, -2}
	};

	t_sprite_render_context ctx;
	init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);

	for (int i = 0; i < NUM_OFFSETS; i++)
	{
		int offset_frame = get_next_eagle_frame(&game->strike[0], i);
		if (offset_frame == -1)
			continue;

		setup_sprite_context(&ctx, game, offsets[i], &game->airstrike_textures[offset_frame]);
		render_single_sprite(&ctx);
	}
}

int get_next_eagle_frame(t_strike *strike, int offset_index)
{
	strike[0].frame_counts[offset_index] += strike[0].speed_multipliers[offset_index];

	if (strike[0].frame_counts[offset_index] < 0)
		return -1;  // Indicate that nothing should be displayed

	int frame = (int)(strike[0].frame_counts[offset_index] / 100) % NUM_AIRSTRIKE_FRAMES;
	return frame;
}

void render_ongoing_eagle(t_game *game)
{
	int current_frame = initialize_eagle_strike(game);
	if (current_frame == -1) return;  // Strike not active or needs reset

	eagle_apply_screen_shake(game, current_frame);
	render_eagle_sprites(game);
}

void render_eagle_strike(t_game *game)
{
	int frame_counter = 0;
	frame_counter++;


	if (game->strike[0].is_launching)
		render_call_strike(game, game->strike[0].position);
	else if (game->strike[0].is_active)
		render_ongoing_eagle(game);
}
