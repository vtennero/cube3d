/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:38:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/23 18:39:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    script_found_sth(t_game *game)
{
    if (game->game_sequence == 3 && game->collectibles->found == 0 && is_player_close_to_collectible(game) == 1)
	{
        printf("found something\n");
		playAudioFileWithDelay("audio/foundsth.mp3", 0);
		game->collectibles->found = 1;
	}
}

void    script_found_supplies(t_game *game)
{
	int found = find_closest_supply(game);
    if (game->game_sequence == 3 && found >= 0 && game->supplies[found].found == 0)
	{
        printf("found supplies\n");
		playAudioFileWithDelay("audio/supplies00.mp3", 0);
		game->supplies[found].found = 1;
	}
}

void    script_take_supplies(t_game *game)
{
	int found = find_supply_on_player_tile(game);
    if (game->game_sequence == 3 && found >= 0 && game->supplies[found].collected == 0)
	{
        printf("restored health\n");
		playAudioFileWithDelay("audio/stims02.mp3", 0);
		game->supplies[found].collected = 1;
		game->player->hp = MAX_HEALTH;
	}
}


void    script_board(t_game *game)
{
	if (is_player_close_to_extract(game) && game->extract[0].is_landing == 1)
	{
    	stopAudioFile("audio/extractmusic00.mp3");
		playAudioFileWithDelay("audio/extractmusic01.mp3", 0);
		playAudioFileWithDelay("audio/extract04.mp3", 0);
		add_script(game, trigger_extract_victory, 5);

		// play audio extraction complete voice
		game->game_sequence = 4;
		reset_game_start_time(game);
    	// printf("game sequence: %d\n", game->game_sequence);

	}
}