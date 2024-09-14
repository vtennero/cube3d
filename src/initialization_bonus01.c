/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization02_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/09 15:28:13 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:28:13 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	create_collectibles(t_game *game)
{
	int	collectibles_repositioned;

	collectibles_repositioned = 0;
	game->num_collectibles = 1;
	randomize_uncollected_collectibles(game, &collectibles_repositioned);
	game->collectibles[0].collected = 0;
	game->collectibles[0].found = 0;
	return (0);
}

int	create_extraction(t_game *game)
{
	randomize_extract_position(game);
	game->extract[0].is_activated = 0;
	game->extract[0].is_available = 0;
	game->extract[0].is_landing = 0;
	return (0);
}

int	randomize_enemy_positions(t_game *game)
{
	int	i;
	int	x;
	int	y;
	int	valid_location_found;

	i = 0;
	while (i < game->num_enemies)
	{
		valid_location_found = 0;
		while (!valid_location_found)
		{
			x = random_int(game, game->map->width);
			y = random_int(game, game->map->height);
			if (game->map->data[y][x] != 1)
				valid_location_found = 1;
		}
		game->enemies[i].position.x = (float)x + 0.5f;
		game->enemies[i].position.y = (float)y + 0.5f;
		i++;
	}
	return (0);
}

int	calculate_enemy_count(t_game *game)
{
	int	map_area;
	int	base_area;
	int	base_count;
	int	enemy_count;

	map_area = game->map->width * game->map->height;
	base_area = 24 * 24;
	if (game->extract->is_landing)
		base_count = 20;
	else if (game->extract->is_activated)
		base_count = 15;
	else if (game->collectibles[0].collected)
		base_count = 5;
	else
		base_count = 2;
	enemy_count = (map_area * base_count) / base_area;
	if (enemy_count < 1)
		enemy_count = 1;
	else if (enemy_count > MAX_ENEMIES)
		enemy_count = MAX_ENEMIES;
	return (enemy_count);
}

int	calculate_supplies(t_game *game)
{
	int	map_area;
	int	base_area;
	int	base_count;
	int	supply_count;

	map_area = game->map->width * game->map->height;
	base_area = 24 * 24;
	base_count = 3;
	supply_count = (map_area * base_count) / base_area;
	if (supply_count < 1)
		supply_count = 1;
	else if (supply_count > MAX_SUPPLIES)
		supply_count = MAX_SUPPLIES;
	return (supply_count);
}
