/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus08.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:12:47 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:12:47 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_frame_and_momentum(t_enemy *enemy, int direction, int move)
{
	if (move)
	{
		enemy->current_frame = (enemy->current_frame \
		+ direction + E_N_FRAMES) % E_N_FRAMES;
		enemy->momentum += direction;
	}
	else
	{
		enemy->current_frame = (enemy->current_frame \
		- direction + E_N_FRAMES) % E_N_FRAMES;
		enemy->momentum -= direction;
	}
	if (enemy->momentum > 3)
		enemy->momentum = 3;
	else if (enemy->momentum < -3)
		enemy->momentum = -3;
}

void	handle_normal_transition(t_enemy *enemy)
{
	int	roll;
	int	direction;
	int	momentum_strength;
	int	move_chance;
	int	move;

	roll = rand() % 100;
	if (roll < 95)
		adjust_momentum(enemy);
	else
	{
		direction = determine_e_direction(enemy);
		momentum_strength = abs(enemy->momentum);
		move_chance = calculate_move_chance(momentum_strength);
		move = (rand() % 100) < move_chance;
		update_frame_and_momentum(enemy, direction, move);
	}
}

int	get_next_enemy_frame(t_enemy *enemy)
{
	update_enemy_frame_count(enemy);
	if (enemy->frame_count % E_ANIM_INT != 0)
		return (enemy->current_frame);
	if (handle_periodic_jump(enemy))
		return (enemy->current_frame);
	handle_normal_transition(enemy);
	return (enemy->current_frame);
}

void	render_enemy(t_game *game, t_enemy *enemy)
{
	int			current_frame;
	t_texture	*enemy_texture;

	current_frame = get_next_enemy_frame(enemy);
	enemy_texture = &game->enemy_textures[current_frame];
	render_sprite_common(game, enemy->position, enemy_texture);
}

void	render_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].is_alive)
			render_enemy(game, &game->enemies[i]);
		i++;
	}
}
