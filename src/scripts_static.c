/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:38:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/25 17:48:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void script_strike_enemies(t_game *game)
{
	if (game->strike->is_active)
	{
    float strikeX = game->strike->position.x;
    float strikeY = game->strike->position.y;
    
    // Define the radius for considering an enemy "close"
    // Assuming each tile is 1.0f x 1.0f, this radius covers the current tile and adjacent tiles
    float strike_radius = 2.0f;

    for (int i = 0; i < game->num_enemies; i++)
    {
        if (!game->enemies[i].is_alive)
            continue;

        float enemyX = game->enemies[i].position.x;
        float enemyY = game->enemies[i].position.y;

        // Calculate the distance between the strike and the enemy
        float dx = strikeX - enemyX;
        float dy = strikeY - enemyY;
        float distance = sqrt(dx * dx + dy * dy);

        // Check if the enemy is within the strike radius
        if (distance <= strike_radius)
        {
            game->enemies[i].is_alive = 0;
            // Optionally, you can add some visual or sound effect here
            // printf("Enemy %d struck down!\n", i);
        }
    }
	}

}

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
		add_script(game, trigger_supply_take, 0);
		add_script(game, cancel_supply_take, 1);
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