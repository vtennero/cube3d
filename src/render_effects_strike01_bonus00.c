/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike01_bonus00.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:51:06 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:44:24 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	apply_napalm_screen_shake(t_game *game, int first_visible_frame)
{
	float	shake_offset;

	if (game->strike[1].is_animating && first_visible_frame != -1)
	{
		shake_offset = calculate_screen_shake(game, first_visible_frame);
		if (game->player->is_dead == 0)
		{
			game->player->height = PLAYER_B_HEIGHT + shake_offset;
		}
		if (game->strike[1].frame_counts[0] >= NUM_NAPALM_FRAMES * 50)
		{
			game->strike[1].is_animating = 0;
		}
	}
	else if (game->player->is_dead == 0)
		game->player->height = PLAYER_B_HEIGHT;
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
