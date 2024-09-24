/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_enemies_bonus00.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:51:17 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:26:49 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_e_momentum(t_enemy *enemy, float dx)
{
	if (dx > 0)
	{
		if (enemy->momentum < 3)
			enemy->momentum += 1;
		else
			enemy->momentum = 3;
	}
	else if (dx < 0)
	{
		if (enemy->momentum > -3)
			enemy->momentum -= 1;
		else
			enemy->momentum = -3;
	}
	else
	{
		if (enemy->momentum > 0)
			enemy->momentum -= 1;
		else if (enemy->momentum < 0)
			enemy->momentum += 1;
		else
			enemy->momentum = 0;
	}
}

void	relocate_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].is_alive)
		{
			relocate_enemy(game, &game->enemies[i], i);
		}
		i++;
	}
}

void	handle_enemy_stop(t_enemy *enemy, unsigned long long *enemy_seed)
{
	if (enemy->stop_counter > 0)
	{
		enemy->stop_counter--;
	}
	else if (xorshift64(enemy_seed) % 1000000 < E_STOP_PROBABILITY)
	{
		enemy->stop_counter = E_STOP_DURATION;
	}
}

void	move_enemy(t_game *game, t_enemy *enemy, unsigned long long *enemy_seed)
{
	t_vector2d	direction;

	if (should_move(enemy_seed))
	{
		direction = (t_vector2d){0, 0};
		calc_e_dir(game, enemy, &direction);
		if (!check_wall_collision(game, enemy, direction))
		{
			update_e_position(enemy, direction);
			update_e_momentum(enemy, direction.x);
		}
	}
}

void	relocate_enemy(t_game *game, t_enemy *enemy, int index)
{
	unsigned long long	enemy_seed;

	enemy_seed = game->random_seed ^ (index * 1099511628211ULL);
	handle_enemy_stop(enemy, &enemy_seed);
	if (enemy->stop_counter == 0)
	{
		move_enemy(game, enemy, &enemy_seed);
	}
}
