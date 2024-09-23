/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike00_bonus00.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:49:42 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:21:59 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_next_eagle_frame(t_strike *strike, int offset_index)
{
	int	frame;

	strike[0].frame_counts[offset_index]
		+= strike[0].speed_multipliers[offset_index];
	if (strike[0].frame_counts[offset_index] < 0)
		return (-1);
	frame = (int)(strike[0].frame_counts[offset_index] / 100)
		% NUM_AIRSTRIKE_FRAMES;
	return (frame);
}

void	render_ongoing_eagle(t_game *game)
{
	int	current_frame;

	current_frame = initialize_eagle_strike(game);
	if (current_frame == -1)
		return ;
	eagle_apply_screen_shake(game, current_frame);
	render_eagle_sprites(game);
}

void	render_eagle_strike(t_game *game)
{
	int	frame_counter;

	frame_counter = 0;
	frame_counter++;
	if (game->strike[0].is_launching)
		render_call_strike(game, game->strike[0].position);
	else if (game->strike[0].is_active)
		render_ongoing_eagle(game);
}
