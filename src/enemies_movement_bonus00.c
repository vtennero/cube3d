/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_movement_bonus00.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:03:15 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 14:03:15 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int should_move(unsigned long long *enemy_seed)
{
	return xorshift64(enemy_seed) % 1000000 < E_MOVEMENT_PROBABILITY;
}

static void calculate_direction(t_game *game, t_enemy *enemy, float *dx, float *dy)
{
	float player_x = game->player->position.x;
	float player_y = game->player->position.y;

	float vector_x = player_x - enemy->position.x;
	float vector_y = player_y - enemy->position.y;

	float distance_to_player = sqrt(vector_x * vector_x + vector_y * vector_y);

	if (distance_to_player > E_STOP_DISTANCE)
	{
		vector_x /= distance_to_player;
		vector_y /= distance_to_player;

		*dx = vector_x * E_MOVEMENT_SPEED;
		*dy = vector_y * E_MOVEMENT_SPEED;
	}
	else {
		*dx = 0;
		*dy = 0;
	}
}

static int check_wall_collision(t_game *game, t_enemy *enemy, float dx, float dy)
{
	float speed = sqrt(dx*dx + dy*dy);  // Calculate the speed of movement
	float direction_x = dx / speed;     // Normalize direction
	float direction_y = dy / speed;

	float newX = enemy->position.x + dx;
	float newY = enemy->position.y + dy;

	// Use E_STOP_DISTANCE as the buffer
	int mapX = (int)(newX + direction_x * E_STOP_DISTANCE);
	int mapY = (int)(newY + direction_y * E_STOP_DISTANCE);

	// Check if the new position is within map bounds and not a wall
	if (mapX >= 0 && mapX < game->map->width &&
		mapY >= 0 && mapY < game->map->height &&
		game->map->data[mapY][mapX] != TILE_WALL)
	{
		return 0;  // Not a wall, can move
	}

	return 1;  // Wall detected, can't move
}

static void update_position(t_enemy *enemy, float dx, float dy)
{
	enemy->position.x += dx;
	enemy->position.y += dy;
}

static void update_momentum(t_enemy *enemy, float dx)
{
	if (dx > 0) enemy->momentum = (enemy->momentum < 3) ? enemy->momentum + 1 : 3;
	else if (dx < 0) enemy->momentum = (enemy->momentum > -3) ? enemy->momentum - 1 : -3;
	else enemy->momentum = (enemy->momentum > 0) ? enemy->momentum - 1 :
						   (enemy->momentum < 0) ? enemy->momentum + 1 : 0;
}

void relocate_enemies(t_game *game)
{
	for (int i = 0; i < game->num_enemies; i++)
	{
		if (game->enemies[i].is_alive)
		{
			relocate_enemy(game, &game->enemies[i], i);
		}
	}

}

void handle_enemy_stop(t_enemy *enemy, unsigned long long *enemy_seed)
{
	if (enemy->stop_counter > 0) {
		enemy->stop_counter--;
	} else if (xorshift64(enemy_seed) % 1000000 < E_STOP_PROBABILITY) {
		enemy->stop_counter = E_STOP_DURATION;
	}
}

void move_enemy(t_game *game, t_enemy *enemy, unsigned long long *enemy_seed)
{
	if (should_move(enemy_seed))
	{
		float dx = 0, dy = 0;
		calculate_direction(game, enemy, &dx, &dy);

		if (!check_wall_collision(game, enemy, dx, dy))
		{
			update_position(enemy, dx, dy);
			update_momentum(enemy, dx);
		}
	}
}

void relocate_enemy(t_game *game, t_enemy *enemy, int index)
{
	unsigned long long enemy_seed = game->random_seed ^ (index * 1099511628211ULL);

	handle_enemy_stop(enemy, &enemy_seed);

	if (enemy->stop_counter == 0) {
		move_enemy(game, enemy, &enemy_seed);
	}
}
