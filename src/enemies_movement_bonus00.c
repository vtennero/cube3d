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

static int	should_move(unsigned long long *enemy_seed)
{
	return (xorshift64(enemy_seed) % 1000000 < E_MOVEMENT_PROBABILITY);
}

static void	calculate_direction(t_game *game, t_enemy *enemy, t_vector2d *direction)
{
	t_vector2d	player_pos;
	t_vector2d	vector;
	float		distance_to_player;

	player_pos.x = game->player->position.x;
	player_pos.y = game->player->position.y;
	vector.x = player_pos.x - enemy->position.x;
	vector.y = player_pos.y - enemy->position.y;
	distance_to_player = sqrt(vector.x * vector.x + vector.y * vector.y);
	if (distance_to_player > E_STOP_DISTANCE)
	{
		vector.x /= distance_to_player;
		vector.y /= distance_to_player;
		direction->x = vector.x * E_MOVEMENT_SPEED;
		direction->y = vector.y * E_MOVEMENT_SPEED;
	}
	else
	{
		direction->x = 0;
		direction->y = 0;
	}
}

static int	check_wall_collision(t_game *game, t_enemy *enemy, t_vector2d direction)
{
	float		speed;
	t_vector2d	normalized_direction;
	t_vector2d	new_pos;
	int			map_x;
	int			map_y;

	speed = sqrt(direction.x * direction.x + direction.y * direction.y);
	normalized_direction.x = direction.x / speed;
	normalized_direction.y = direction.y / speed;
	new_pos.x = enemy->position.x + direction.x;
	new_pos.y = enemy->position.y + direction.y;
	map_x = (int)(new_pos.x + normalized_direction.x * E_STOP_DISTANCE);
	map_y = (int)(new_pos.y + normalized_direction.y * E_STOP_DISTANCE);
	if (map_x >= 0 && map_x < game->map->width &&
		map_y >= 0 && map_y < game->map->height &&
		game->map->data[map_y][map_x] != TILE_WALL)
		return (0);
	return (1);
}

static void update_position(t_enemy *enemy, t_vector2d direction)
{
	enemy->position.x += direction.x;
	enemy->position.y += direction.y;
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
		t_vector2d direction = {0, 0};
		calculate_direction(game, enemy, &direction);

		if (!check_wall_collision(game, enemy, direction))
		{
			update_position(enemy, direction);
			update_momentum(enemy, direction.x);
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
