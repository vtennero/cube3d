/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement_bonus00.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/21 16:53:03 by cliew             #+#    #+#             */
/*   Updated: 2024/09/21 16:53:03 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	normalize_direction(float *dirX, float *dirY, float length)
{
	if (length != 0)
	{
		*dirX /= length;
		*dirY /= length;
		return (1);
	}
	return (0);
}

int	check_collision_at_point(t_game *game, t_vector2d dir, float t,
		float buffer)
{
	int	map_x;
	int	map_y;

	map_x = (int)(game->player->position.x + dir.x * (t + buffer));
	map_y = (int)(game->player->position.y + dir.y * (t + buffer));
	if (map_x < 0 || map_x >= game->map->width || map_y < 0
		|| map_y >= game->map->height
		|| game->map->data[map_y][map_x] == TILE_WALL)
		return (1);
	return (0);
}

int	detect_collision(t_game *game, float newX, float newY)
{
	t_vector2d	dir;
	float		length;
	float		t;
	float		buffer;

	buffer = 0.8;
	dir.x = newX - game->player->position.x;
	dir.y = newY - game->player->position.y;
	length = sqrt(dir.x * dir.x + dir.y * dir.y);
	t = 0;
	if (!normalize_direction(&dir.x, &dir.y, length))
		return (0);
	while (t <= 1)
	{
		if (check_collision_at_point(game, dir, length * t, buffer))
			return (1);
		t += 0.1;
	}
	return (0);
}

void	handle_movement_up(t_game *game)
{
	if (game->key_state[K_UP] == 1)
	{
		handle_key_up(game);
	}
}

void	handle_movement_down(t_game *game)
{
	if (game->key_state[K_DOWN] == 1)
	{
		handle_key_down(game);
	}
}

void	handle_key_up(t_game *game)
{
	if (game->player->pitch < 1 && game->bonus && !game->player->is_extracting)
		game->player->pitch += 0.01;
}

void	handle_key_down(t_game *game)
{
	if (game->player->pitch > -1 && game->bonus
		&& !game->player->is_extracting)
		game->player->pitch -= 0.01;
}
