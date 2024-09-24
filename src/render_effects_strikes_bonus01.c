/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strikes_bonus01.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:52:50 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:53:06 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	reset_strike(t_game *game)
{
	int	i;

	game->strike[0].is_active = 0;
	game->strike[0].is_animating = 0;
	i = 0;
	while (i < NUM_OFFSETS)
	{
		game->strike[0].frame_counts[i] = rand() % (NUM_AIRSTRIKE_FRAMES * 100);
		i++;
	}
}

float	calculate_screen_shake(t_game *game, int current_frame)
{
	float	random_offset;
	float	intensity;
	float	shake;

	if (current_frame >= STRIKE_SHAKE_DURATION || game->player->is_dead == 1)
		return (0.0f);
	random_offset = (float)random_int(game, 1000) / 1000.0f;
	intensity = STRIKE_SHAKE_INTENSITY \
	* (1.0f - (float)current_frame / STRIKE_SHAKE_DURATION);
	shake = sinf(current_frame * 0.5f) * intensity;
	return (shake * random_offset);
}
