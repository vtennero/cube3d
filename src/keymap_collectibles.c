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

int is_player_close_to_extract(t_game *game)
{

    float dx = game->player->position.x - game->extract[0].position.x;
    float dy = game->player->position.y - game->extract[0].position.y;
    
    // Calculate the squared distance
    float distance_squared = dx * dx + dy * dy;
    
    // If the squared distance is less than the squared collection distance,
    // printf("EXTRACT: extract position %f, %f | player position %f, %f | distance_squared %f\n", game->extract[0].position.x, game->extract[0].position.y, game->player->position.x, game->player->position.y, distance_squared);
    // return 1
    if (distance_squared <= (COLLECTION_DISTANCE * COLLECTION_DISTANCE))
    {
        // printf("EXTRACT: player is close to extract\n");
        return 1;
    }
        // printf("EXTRACT: player is not close to extract\n");
    // printf("**************\n");
    return 0;
}

int is_player_close_to_collectible(t_game *game)
{
    for (int i = 0; i < game->num_collectibles; i++)
    {
        if (!game->collectibles[i].collected)
        {
            float dx = game->player->position.x - game->collectibles[i].position.x;
            float dy = game->player->position.y - game->collectibles[i].position.y;
            
            // Calculate the squared distance
            float distance_squared = dx * dx + dy * dy;
            // printf("distance_squared %f\n", distance_squared);
            
            // If the squared distance is less than the squared collection distance,
            // return 1
            if (distance_squared <= (COLLECTION_DISTANCE * COLLECTION_DISTANCE))
            {
                return 1;
            }
        }
    }
    
    return 0;
}

// void handle_key_e(t_game *game)
// {
//     if (game->key_state[K_E] == 1)
//     {
//         if (is_player_close_to_collectible(game))
//         {
//             game->collectibles[0].collected = 1;

//             // playAudioFileWithDelay("audio/samplepickup.mp3", 0);
//             // playAudioFileWithDelay("audio/raresampleacquired.mp3", 2);
//             game->extract[0].is_activated = 1;
//         }
//     if (is_player_close_to_extract(game) && game->extract->is_activated)
//         {
//             add_script(game, testscript, 3); // Add testscript to run after 3 seconds
//             // playAudioFileWithDelay("audio/extract01.mp3", 2);
//         }
//     }
// }

// Modify handle_key_e to remove the key state check
void handle_key_e(t_game *game)
{
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

void    handle_key_2(t_game *game)
{
    
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

void    handle_key_3(t_game *game)
{
    
    if (game->strike[2].is_launching == 0 && game->strike[2].is_active == 0 && game->game_sequence == 3)
    {
        printf("launching barrage %f, %f\n", game->center_floor_coords.y, game->center_floor_coords.x);
        // add script launch strike
        game->strike[2].position.y = game->center_floor_coords.y;
        game->strike[2].position.x = game->center_floor_coords.x;
        game->strike[2].base_position.y = game->center_floor_coords.y;
        game->strike[2].base_position.x = game->center_floor_coords.x;
        game->strike[2].is_launching = 1;

        playAudioFileWithDelay("audio/orbitalcall.mp3", 0);
        add_script(game, barrage_inbound, BARRAGE_CALL_IN_TIME);
        add_script(game, play_barrage_shell,BARRAGE_CALL_IN_TIME - 2);
        add_script(game, stop_barrage, BARRAGE_DURATION);

    }
}