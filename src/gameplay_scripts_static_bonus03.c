/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_static_bonus03.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:00:40 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:48:41 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	script_found_sth(t_game *game)
{
	if (game->game_sequence == 3
		&& game->collectibles->found == 0
		&& is_player_close_to_collectible(game) == 1)
	{
		play_audio_file(game, "audio/foundsth.mp3", 0);
		game->collectibles->found = 1;
	}
}

void	script_found_supplies(t_game *game)
{
	int	found;

	found = find_closest_supply(game);
	if (game->game_sequence == 3 && found >= 0 && \
	game->supplies[found].found == 0)
	{
		play_audio_file(game, "audio/supplies00.mp3", 0);
		game->supplies[found].found = 1;
	}
}

void	script_take_supplies(t_game *game)
{
	int	found;

	found = find_supply_on_player_tile(game);
	if (game->game_sequence == 3 && found >= 0 && \
	game->supplies[found].collected == 0)
	{
		printf("restored health\n");
		play_audio_file(game, "audio/stims02.mp3", 0);
		play_audio_file(game, "audio/stims03.mp3", 0);
		add_script(game, trigger_supply_take, 0);
		add_script(game, cancel_supply_take, 1);
		game->supplies[found].collected = 1;
		game->player->is_burning = 0;
		game->player->hp = MAX_HEALTH;
		stop_audio_file(game, "audio/burn00.mp3");
		stop_audio_file(game, "audio/burn01.mp3");
		stop_audio_file(game, "audio/burn02.mp3");
		stop_audio_file(game, "audio/burn03.mp3");
	}
}

void	script_board(t_game *game)
{
	if (is_player_close_to_extract(game) && game->extract[0].is_landing == 1)
	{
		stop_audio_file(game, "audio/extractmusic00.mp3");
		play_audio_file(game, "audio/extractmusic01.mp3", 0);
		play_audio_file(game, "audio/extract04.mp3", 0);
		add_script(game, trigger_extract_victory, 5);
		game->extract[0].is_landing = 0;
		game->player->is_extracting = 1;
	}
}

void	script_takeoff(t_game *game)
{
	if (game->player->is_extracting == 1)
	{
		if (game->player->height >= 3)
		{
			game->player->is_extracting = 0;
			game->game_sequence = 4;
			reset_game_start_time(game);
		}
		else
		{
			game->player->height *= 1.03;
			game->player->is_extracting = 1;
		}
	}
}
