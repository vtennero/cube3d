/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement_bonus00.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:08:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 15:08:07 by vitenner         ###   ########.fr       */
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

int	check_collision_at_point(t_game *game, float dirX, float dirY, float t, float buffer)
{
	int	mapX;
	int	mapY;

	mapX = (int)(game->player->position.x + dirX * (t + buffer));
	mapY = (int)(game->player->position.y + dirY * (t + buffer));
	if (mapX < 0 || mapX >= game->map->width ||
		mapY < 0 || mapY >= game->map->height ||
		game->map->data[mapY][mapX] == TILE_WALL)
		return (1);
	return (0);
}

int	detect_collision(t_game *game, float newX, float newY)
{
	float	dirX;
	float	dirY;
	float	length;
	float	t;
	float	buffer;

	buffer = 0.8;
	dirX = newX - game->player->position.x;
	dirY = newY - game->player->position.y;
	length = sqrt(dirX * dirX + dirY * dirY);
	t = 0;
	if (!normalize_direction(&dirX, &dirY, length))
		return (0);
	while (t <= 1)
	{
		if (check_collision_at_point(game, dirX, dirY, length * t, buffer))
			return (1);
		t += 0.1;
	}
	return (0);
}

void handle_movement_up(t_game *game)
{
	if (game->key_state[K_UP] == 1)
	{
		handle_key_up(game);
	}
}

void handle_movement_down(t_game *game)
{
	if (game->key_state[K_DOWN] == 1)
	{
		handle_key_down(game);
	}
}
void handle_key_up(t_game *game)
{
	if (game->player->pitch < 1 && game->bonus && !game->player->is_extracting)
		game->player->pitch += 0.01;
}

void handle_key_down(t_game *game)
{
	if (game->player->pitch > -1 && game->bonus && !game->player->is_extracting)
		game->player->pitch -= 0.01;
}
