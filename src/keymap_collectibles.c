/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:07:42 by toto              #+#    #+#             */
/*   Updated: 2024/08/27 17:59:40 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define COLLECTION_DISTANCE 1.0f  // Adjust this value as needed

int	is_player_close_to_extract(t_game *game)
{
	float	dx;
	float	dy;
	float	distance_squared;

	dx = game->player->position.x - game->extract[0].position.x;
	dy = game->player->position.y - game->extract[0].position.y;
	distance_squared = dx * dx + dy * dy;
	if (distance_squared <= (COLLECTION_DISTANCE * COLLECTION_DISTANCE))
		return (1);
	return (0);
}
int	is_player_close_to_collectible(t_game *game)
{
	int		i;
	float	dx;
	float	dy;
	float	distance_squared;

	i = 0;
	while (i < game->num_collectibles)
	{
		if (!game->collectibles[i].collected)
		{
			dx = game->player->position.x - game->collectibles[i].position.x;
			dy = game->player->position.y - game->collectibles[i].position.y;
			distance_squared = dx * dx + dy * dy;
			if (distance_squared <= (COLLECTION_DISTANCE * COLLECTION_DISTANCE))
				return (1);
		}
		i++;
	}
	return (0);
}


// Modify handle_key_e to remove the key state check
void handle_key_e(t_game *game)
{
    game->key_state[K_E] = 1;
    if (is_player_close_to_collectible(game))
    {
        game->collectibles[0].collected = 1;
        game->extract[0].is_available = 1;
        playAudioFileWithDelay("audio/samplepickup.mp3", 0);
        add_script(game, sample_acquired, 1);
        add_script(game, extraction_available, 5);
        
    }
    else if (is_player_close_to_extract(game) && game->extract->is_available)
    {
        // add_script(game, testscript, 3);
        playAudioFileWithDelay("audio/extract01.mp3", 0);
        playAudioFileWithDelay("audio/extractkeyboard.mp3", 0);
        game->extract[0].is_available = 0;
        game->extract[0].is_activated = 1;
        add_script(game, trigger_extract_music, 1);
        add_script(game, trigger_landing, EXTRACT_CALL_TIME);

        int extract_eta = EXTRACT_CALL_TIME - 10;
        printf("extract eta %d\n", extract_eta);
        // if (EXTRACT_CALL_TIME - 10 > 0)
        // {
            // printf("prelanding warning triggered\n");
            add_script(game, trigger_prelanding, extract_eta);
        // }
        // else
            // printf("prelanding not triggered EXTRACT_CALL_TIME - 10%d\n", EXTRACT_CALL_TIME - 10);
    }
}

void    handle_key_1(t_game *game)
{
    game->key_state[K_1] = 1;
    if (game->strike[0].is_launching == 0 && game->strike[0].is_active == 0 && game->game_sequence == 3)
    {
        printf("launching eagle strike at %f, %f\n", game->center_floor_coords.y, game->center_floor_coords.x);
        game->strike[0].position.y = game->center_floor_coords.y;
        game->strike[0].position.x = game->center_floor_coords.x;
        game->strike[0].is_launching = 1;
        play_random_strike_sound(game);
		add_script(game, eagle_inbound, 3);
    }
}
void    handle_key_2(t_game *game)
{
    game->key_state[K_2] = 1;
    if (game->strike[1].is_launching == 0 && game->strike[1].is_active == 0 && game->game_sequence == 3)
    {
        printf("launching napalm strike at %f, %f\n", game->center_floor_coords.y, game->center_floor_coords.x);
        // add script launch strike
        game->strike[1].position.y = game->center_floor_coords.y;
        game->strike[1].position.x = game->center_floor_coords.x;
        game->strike[1].is_launching = 1;
        // script to choose audio for airstrike
        play_random_strike_sound(game);
        add_script(game, napalm_inbound, 3);
        add_script(game, remove_napalm, 15);

    }
}

#define BARRAGE_CALL_IN_TIME 8
#define BARRAGE_DURATION 30

void	handle_key_3(t_game *game)
{
    game->key_state[K_3] = 1;
	if (game->strike[2].is_launching == 0 
		&& game->strike[2].is_active == 0 
		&& game->game_sequence == 3)
	{
		printf("Launching barrage %f, %f\n", 
        game->center_floor_coords.y, game->center_floor_coords.x);
		game->strike[2].position.y = game->center_floor_coords.y;
		game->strike[2].position.x = game->center_floor_coords.x;
		game->strike[2].base_position.y = game->center_floor_coords.y;
		game->strike[2].base_position.x = game->center_floor_coords.x;
		game->strike[2].is_launching = 1;
		playAudioFileWithDelay("audio/orbitalcall.mp3", 0);
		add_script(game, barrage_inbound, BARRAGE_CALL_IN_TIME);
		add_script(game, play_barrage_shell, 
			BARRAGE_CALL_IN_TIME - 2);
		add_script(game, stop_barrage, BARRAGE_DURATION);
	}
}
