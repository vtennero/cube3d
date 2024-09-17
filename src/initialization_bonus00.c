/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization01_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/09/09 15:28:15 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:28:17 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	strike_helper(t_game *game, int i, int *j)
{
	game->strike[i].position.x = 0;
	game->strike[i].position.y = 0;
	game->strike[i].is_active = 0;
	game->strike[i].is_launching = 0;
	game->strike[i].current_frame = 0;
	game->strike[i].frame_count = 0;
	game->strike[i].is_animating = 0;
	game->strike[i].delay_duration = 60 * 2;
	game->strike[i].delay_frames = 0;
	*j = 0;
	if (i == 0)
	{
		while (*j < NUM_OFFSETS)
		{
			game->strike[i].frame_counts[*j] = rand() % (NUM_AIRSTRIKE_FRAMES
					* 100);
			game->strike[i].speed_multipliers[*j] = 15.0f + ((float)rand()
					/ RAND_MAX) * 10.0f;
			(*j)++;
		}
	}
}

int	create_strike(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAX_STRIKES)
	{
		strike_helper(game, i, &j);
		if (i == 1)
		{
			while (j < NUM_NAPALM_OFFSETS)
			{
				game->strike[i].frame_counts[j] = rand() % (NUM_NAPALM_FRAMES
						* 100);
				game->strike[i].speed_multipliers[j] = 0.25f + ((float)rand()
						/ RAND_MAX) * 0.2f;
				j++;
			}
		}
		i++;
	}
	return (1);
}

int	randomize_extract_position(t_game *game)
{
	int	x;
	int	y;
	int	valid_position;

	valid_position = 0;
	while (!valid_position)
	{
		x = random_int(game, game->map->width);
		y = random_int(game, game->map->height);
		if (game->map->data[y][x] != 1 && (x == 0 || game->map->data[y][x
				- 1] != 1) && (x == game->map->width - 1 || game->map->data[y][x
				+ 1] != 1) && (y == 0 || game->map->data[y - 1][x] != 1)
			&& (y == game->map->height - 1 || game->map->data[y + 1][x] != 1)
			&& (x == 0 || y == 0 || game->map->data[y - 1][x - 1] != 1)
			&& (x == game->map->width - 1 || y == 0 || game->map->data[y - 1][x
				+ 1] != 1) && (x == 0 || y == game->map->height - 1
				|| game->map->data[y + 1][x - 1] != 1) && (x == game->map->width
				- 1 || y == game->map->height - 1 || game->map->data[y + 1][x
				+ 1] != 1))
			valid_position = 1;
	}
	game->extract[0].position.x = (float)x + 0.5f;
	game->extract[0].position.y = (float)y + 0.5f;
	return (1);
}

void	randomize_uncollected_collectibles(t_game *game,
		int *collectibles_repositioned)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < game->num_collectibles)
	{
		if (game->collectibles[i].collected == 0)
		{
			x = random_int(game, game->map->width);
			y = random_int(game, game->map->height);
			while (game->map->data[y][x] == 1)
			{
				x = random_int(game, game->map->width);
				y = random_int(game, game->map->height);
			}
			game->collectibles[i].position.x = (float)x + 0.5f;
			game->collectibles[i].position.y = (float)y + 0.5f;
			game->collectibles[i].collected = 0;
			game->collectibles[i].found = 0;
			collectibles_repositioned++;
		}
		i++;
	}
}

int	respawn_player(t_game *game)
{
	int	x;
	int	y;
	int	valid_location_found;

	valid_location_found = 0;
	game->player->is_burning = 0;
	game->player->hp = MAX_HEALTH;
	stop_audio_file(game, "audio/burn00.mp3");
	stop_audio_file(game, "audio/burn01.mp3");
	stop_audio_file(game, "audio/burn02.mp3");
	stop_audio_file(game, "audio/burn03.mp3");
	if (game->player->is_dead == 1)
	{
		valid_location_found = 0;
		while (!valid_location_found)
		{
			x = random_int(game, game->map->width);
			y = random_int(game, game->map->height);
			if (is_valid_location(game, x, y))
				valid_location_found = 1;
		}
		game->player->position.x = (float)x + 0.5f;
		game->player->position.y = (float)y + 0.5f;
	}
	return (0);
}
