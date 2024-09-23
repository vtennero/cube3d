/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike01_bonus00.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:51:06 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 14:35:15 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_next_napalm_frame(t_strike *strike, int offset_index)
{
	int	frame;

	strike->frame_counts[offset_index] += (int)(strike->speed_multipliers[offset_index] * 100);
	if (strike->frame_counts[offset_index] < 0)
		return (-1);
	frame = (strike->frame_counts[offset_index] / 100) % NUM_NAPALM_FRAMES;
	if (strike->frame_counts[offset_index] >= NUM_NAPALM_FRAMES * 100)
		strike->frame_counts[offset_index] = 0;
	return (frame);
}

void	render_ongoing_napalm(t_game *game)
{
	int	current_frames[NUM_NAPALM_OFFSETS];
	int	first_visible_frame;

	first_visible_frame = initialize_napalm(game, current_frames);
	if (first_visible_frame == -1)
		return ;
	apply_napalm_screen_shake(game, first_visible_frame);
	render_napalm_sprites(game, current_frames);
}

int	initialize_napalm(t_game *game, int current_frames[])
{
	int	first_visible_frame;
	int	i;

	if (!game->strike[1].is_active)
		return (-1);
	first_visible_frame = -1;
	i = 0;
	while (i < NUM_NAPALM_OFFSETS)
	{
		current_frames[i] = get_next_napalm_frame(&game->strike[1], i);
		if (first_visible_frame == -1 && current_frames[i] != -1)
			first_visible_frame = current_frames[i];
		i++;
	}
	return (first_visible_frame);
}

void	apply_napalm_screen_shake(t_game *game, int first_visible_frame)
{
	if (game->strike[1].is_animating && first_visible_frame != -1)
	{
		float shake_offset = calculate_screen_shake(game, first_visible_frame);
		if (game->player->is_dead == 0)
			game->player->height = PLAYER_B_HEIGHT + shake_offset;
		if (game->strike[1].frame_counts[0] >= NUM_NAPALM_FRAMES * 50)
			game->strike[1].is_animating = 0;
	}
	else if (game->player->is_dead == 0)
		game->player->height = PLAYER_B_HEIGHT;
}

void	render_napalm_sprites(t_game *game, int current_frames[])
{
	t_vector2d offsets[NUM_NAPALM_OFFSETS] = {
		{0, 0},
		{1, 0}, {-1, 0}, {0, 1}, {0, -1},
		{1, 1}, {1, -1}, {-1, 1}, {-1, -1},
		{2, 0}, {-2, 0}, {0, 2}, {0, -2},
		{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
		{3, 0}, {-3, 0}, {0, 3}, {0, -3},
		{3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {1, 3}, {1, -3}, {-1, 3}, {-1, -3},
		{4, 0}, {-4, 0}, {0, 4}, {0, -4}
	};

	t_sprite_render_context ctx;
	init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);

	for (int i = 0; i < NUM_NAPALM_OFFSETS; i++)
	{
		if (current_frames[i] == -1)
			continue;
		setup_napalm_sprite_context(&ctx, game, offsets[i], &game->np_txture[current_frames[i]]);
		render_single_sprite(&ctx);
	}
}
void	setup_napalm_sprite_context(t_sprite_render_context *ctx, t_game *game, t_vector2d offset, t_texture *texture)
{
	ctx->game = game;
	ctx->texture = texture;
	ctx->position.x = game->strike[1].position.x + offset.x;
	ctx->position.y = game->strike[1].position.y + offset.y;
	calc_sprite_transforms(ctx);
	calc_sprite_dimensions(ctx);
}

void	render_napalm(t_game *game)
{
	if (game->strike[1].is_launching)
	{
		render_call_strike(game, game->strike[1].position);
		game->strike[1].is_animating = 1;
	}
	else if (game->strike[1].is_active)
		render_ongoing_napalm(game);
}
