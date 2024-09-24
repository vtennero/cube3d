/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike02_bonus00.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:48:45 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:57:03 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	initialize_barrage(t_game *game)
{
	if (!game->strike[2].is_active)
		return (-1);
	return (get_next_barrage_frame(&game->strike[2]));
}

void	apply_barrage_screen_shake(t_game *game, int current_frame)
{
	float	shake_offset;

	shake_offset = calculate_screen_shake(game, current_frame);
	if (game->player->is_dead == 0)
		game->player->height = PLAYER_B_HEIGHT + shake_offset;
}

void	render_ongoing_barrage(t_game *game)
{
	int	current_frame;

	current_frame = initialize_barrage(game);
	if (current_frame == -1)
		return ;
	apply_barrage_screen_shake(game, current_frame);
	render_barrage_sprite(game, current_frame);
	handle_frame_specific_actions(game, current_frame);
}

void	render_barrage(t_game *game)
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
