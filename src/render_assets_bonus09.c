/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus09.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:12:56 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:14:11 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_enemy_frame_count(t_enemy *enemy)
{
	enemy->frame_count++;
	enemy->animation_steps++;
}

int	handle_periodic_jump(t_enemy *enemy)
{
	int	jump;

	if (enemy->animation_steps >= E_JUMP_INT && (rand() % 100) < 10)
	{
		jump = (rand() % 6) + 5;
		if (rand() % 2 == 0)
			jump = -jump;
		enemy->current_frame = (enemy->current_frame \
		+ jump + E_N_FRAMES) % E_N_FRAMES;
		enemy->momentum = 0;
		enemy->animation_steps = 0;
		return (1);
	}
	return (0);
}

void	adjust_momentum(t_enemy *enemy)
{
	if (enemy->momentum > 0)
		enemy->momentum--;
	else if (enemy->momentum < 0)
		enemy->momentum++;
}

int	determine_e_direction(t_enemy *enemy)
{
	if (enemy->momentum > 0)
		return (1);
	if (enemy->momentum < 0)
		return (-1);
	if (rand() % 2 == 0)
		return (1);
	else
		return (-1);
}

int	calculate_move_chance(int momentum_strength)
{
	if (momentum_strength >= 2)
		return (80);
	if (momentum_strength == 1)
		return (65);
	return (0);
}
