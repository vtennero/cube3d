/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization03_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/09 15:27:50 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:27:51 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_valid_location(t_game *game, int x, int y)
{
	int	extract_x;
	int	extract_y;

	if (x < 0 || x >= game->map->width || y < 0 || y >= game->map->height)
	{
		return (0);
	}
	if (game->map->data[y][x] == 1)
		return (0);
	extract_x = (int)game->extract[0].position.x;
	extract_y = (int)game->extract[0].position.y;
	if (abs(x - extract_x) <= 1 && abs(y - extract_y) <= 1)
		return (0);
	return (1);
}

int	create_enemies(t_game *game)
{
	int	i;

	i = 0;
	game->num_enemies = calculate_enemy_count(game);
	while (i < E_N)
	{
		game->enemies[i].is_alive = 0;
		game->enemies[i].frame_count = 0;
		game->enemies[i].current_frame = 0;
		game->enemies[i].momentum = 0;
		game->enemies[i].animation_steps = 0;
		game->enemies[i].stop_counter = 0;
		i++;
	}
	i = 0;
	while (i < game->num_enemies)
	{
		game->enemies[i].is_alive = 1;
		i++;
	}
	randomize_enemy_positions(game);
	return (0);
}

int	create_supplies(t_game *game)
{
	game->num_supplies = calculate_supplies(game);
	randomize_uncollected_supplies(game);
	return (0);
}

void	randomize_single_supply(t_game *game, t_supplies *supply)
{
	int	x;
	int	y;

	while (1)
	{
		x = random_int(game, game->map->width);
		y = random_int(game, game->map->height);
		if (is_valid_location(game, x, y))
			break ;
	}
	supply->position.x = (float)x + 0.5f;
	supply->position.y = (float)y + 0.5f;
	supply->collected = 0;
	supply->found = 0;
}

int	randomize_uncollected_supplies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_supplies)
	{
		if (game->supplies[i].collected == 0)
			randomize_single_supply(game, &game->supplies[i]);
		i++;
	}
	return (0);
}
