/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:38:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/27 17:39:38 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void    play_bug_death(t_game *game)
{
    int random_call = random_int(game, 6);
    
    (void)game;
    // Create the audio file name based on the random number
    char audio_file[] = "audio/bug00.mp3";
    // char audio_file[] = "audio/eaglec00.mp3";
    audio_file[9] = '0' + random_call / 10;
    audio_file[10] = '0' + random_call % 10;
    
    // Play the selected audio file with no delay
    playAudioFileWithDelay(audio_file, 0);
}

void script_strike_enemies(t_game *game)
{
	if (game->strike[0].is_active)
	{
    float strikeX = game->strike[0].position.x;
    float strikeY = game->strike[0].position.y;
    
    // Define the radius for considering an enemy "close"
    // Assuming each tile is 1.0f x 1.0f, this radius covers the current tile and adjacent tiles
    float strike_radius = 4.0f;

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
            play_bug_death(game);
            // Optionally, you can add some visual or sound effect here
            // printf("Enemy %d struck down!\n", i);
        }
    }
	}

}

void script_strike_player(t_game *game)
{
    if (game->strike[0].is_active)
    {
        float strikeX = game->strike[0].position.x;
        float strikeY = game->strike[0].position.y;
        
        // Define the radius for considering the player "close"
        // Assuming each tile is 1.0f x 1.0f, this radius covers the current tile and adjacent tiles
        float strike_radius = 4.0f;

        float playerX = game->player->position.x;
        float playerY = game->player->position.y;

        // Calculate the distance between the strike and the player
        float dx = strikeX - playerX;
        float dy = strikeY - playerY;
        float distance = sqrt(dx * dx + dy * dy);

        // Check if the player is within the strike radius
        if (distance <= strike_radius)
        {
            game->player->hp = 0;
            // Optionally, you can add some visual or sound effect here
            // printf("Player struck down!\n");
        }
    }
}

void script_napalm_enemies(t_game *game, int strike_no, float radius)
{
	if (game->strike[strike_no].is_active)
	{
    float strikeX = game->strike[strike_no].position.x;
    float strikeY = game->strike[strike_no].position.y;
    
    // Define the radius for considering an enemy "close"
    // Assuming each tile is 1.0f x 1.0f, this radius covers the current tile and adjacent tiles

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
        if (distance <= radius)
        {
            game->enemies[i].is_alive = 0;
            play_bug_death(game);
            // Optionally, you can add some visual or sound effect here
            // printf("Enemy %d struck down!\n", i);
        }
    }
	}

}

void script_napalm_player(t_game *game, int strike_no, float radius)
{
    if (game->strike[strike_no].is_active)
    {
        float strikeX = game->strike[strike_no].position.x;
        float strikeY = game->strike[strike_no].position.y;
        
        // Define the radius for considering the player "close"
        // Assuming each tile is 1.0f x 1.0f, this radius covers the current tile and adjacent tiles

        float playerX = game->player->position.x;
        float playerY = game->player->position.y;

        // Calculate the distance between the strike and the player
        float dx = strikeX - playerX;
        float dy = strikeY - playerY;
        float distance = sqrt(dx * dx + dy * dy);

        // Check if the player is within the strike radius
        if (distance <= radius)
        {
            game->player->hp--;
            // Optionally, you can add some visual or sound effect here
            // printf("Player struck down!\n");
        }
    }
}

void script_barrage_enemies(t_game *game)
{
	if (game->strike[2].is_active)
	{
    float strikeX = game->strike[2].position.x;
    float strikeY = game->strike[2].position.y;
    
    // Define the radius for considering an enemy "close"
    // Assuming each tile is 1.0f x 1.0f, this radius covers the current tile and adjacent tiles
    float strike_radius = 4.0f;

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
        if (distance <= strike_radius && game->strike[2].is_animating)
        {
            game->enemies[i].is_alive = 0;
            play_bug_death(game);
            // Optionally, you can add some visual or sound effect here
            // printf("Enemy %d struck down!\n", i);
        }
    }
	}

}

void script_barrage_player(t_game *game)
{
    if (game->strike[2].is_active)
    {
        float strikeX = game->strike[2].position.x;
        float strikeY = game->strike[2].position.y;
        
        // Define the radius for considering the player "close"
        // Assuming each tile is 1.0f x 1.0f, this radius covers the current tile and adjacent tiles
        float strike_radius = 4.0f;

        float playerX = game->player->position.x;
        float playerY = game->player->position.y;

        // Calculate the distance between the strike and the player
        float dx = strikeX - playerX;
        float dy = strikeY - playerY;
        float distance = sqrt(dx * dx + dy * dy);

        // Check if the player is within the strike radius
        if (distance <= strike_radius && game->strike[2].is_animating)
        {
            game->player->hp = 0;
            // Optionally, you can add some visual or sound effect here
            // printf("Player struck down!\n");
        }
    }
}


void	play_land_voice(t_game *game)
{
    int random_call = random_int(game, 9);
    
    // Create the audio file name based on the random number
    char audio_file[] = "audio/land00.mp3";
    // char audio_file[] = "audio/eaglec00.mp3";
    audio_file[10] = '0' + random_call / 10;
    audio_file[11] = '0' + random_call % 10;
    
    // Play the selected audio file with no delay
    playAudioFileWithDelay(audio_file, 0);
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

void	script_die(t_game *game)
{
	// printf("script die\n");
	if (game->player->hp == 0 && game->player->is_dead == 0)
	{
		reset_game_start_time(game);
		game->player->is_dead = 1;
		playAudioFileWithDelay("audio/death.mp3", 0);
		playAudioFileWithDelay("audio/kia00.mp3", 0);
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
        game->extract[0].is_landing = 0;
        game->player->is_extracting = 1;
	}
}

void    script_takeoff(t_game *game)
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