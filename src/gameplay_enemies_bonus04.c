/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_enemies_bonus04.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:26:09 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:26:47 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	should_move(unsigned long long *enemy_seed)
{
	return (xorshift64(enemy_seed) % 1000000 < E_MOVEMENT_PROBABILITY);
}

void	calc_e_dir(t_game *game, t_enemy *enemy, t_vector2d *dir)
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
		dir->x = vector.x * E_MOVEMENT_SPEED;
		dir->y = vector.y * E_MOVEMENT_SPEED;
	}
	else
	{
		dir->x = 0;
		dir->y = 0;
	}
}

int	check_wall_collision(t_game *game, t_enemy *enemy, t_vector2d dir)
{
	float		speed;
	t_vector2d	normalized_dir;
	t_vector2d	new_pos;
	int			map_x;
	int			map_y;

	speed = sqrt(dir.x * dir.x + dir.y * dir.y);
	normalized_dir.x = dir.x / speed;
	normalized_dir.y = dir.y / speed;
	new_pos.x = enemy->position.x + dir.x;
	new_pos.y = enemy->position.y + dir.y;
	map_x = (int)(new_pos.x + normalized_dir.x * E_STOP_DISTANCE);
	map_y = (int)(new_pos.y + normalized_dir.y * E_STOP_DISTANCE);
	if (map_x >= 0 && map_x < game->map->width \
	&& map_y >= 0 && map_y < game->map->height \
	&& game->map->data[map_y][map_x] != TILE_WALL)
		return (0);
	return (1);
}

void	update_e_position(t_enemy *enemy, t_vector2d direction)
{
	enemy->position.x += direction.x;
	enemy->position.y += direction.y;
}
