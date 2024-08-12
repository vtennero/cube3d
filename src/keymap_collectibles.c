/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:07:42 by toto              #+#    #+#             */
/*   Updated: 2024/08/12 19:27:25 by toto             ###   ########.fr       */
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
    printf("distance_squared %f\n", distance_squared);
    // return 1
    if (distance_squared <= (COLLECTION_DISTANCE * COLLECTION_DISTANCE))
    {
        printf("player is close to extract\n");
        return 1;
    }
        printf("player is not close to extract\n");
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
            printf("distance_squared %f\n", distance_squared);
            
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
//     if (game->key_state[K_E] == 1 && is_player_close_to_collectible(game))
// 	{
// 		game->collectibles[0].collected = 1;

//         playAudioFileWithDelay("audio/samplepickup.mp3", 0);
// 		playAudioFileWithDelay("audio/raresampleacquired.mp3", 2);
// 	    game->extract[0].is_activated = 1;

// 		// playAudioFile("audio/samplepickup.mp3");
// 		// playAudioFile("audio/raresampleacquired.mp3");


// 	}
//     else if (game->key_state[K_E] == 1 && is_player_close_to_extract(game))
//     {
// 		playAudioFileWithDelay("audio/extract01.mp3", 2);
// 		playAudioFileWithDelay("audio/extract02.mp3", 2);
//     }
// 	// add case for terminal
// }

void handle_key_e(t_game *game)
{
    if (game->key_state[K_E] == 1)
    {
        if (is_player_close_to_collectible(game))
        {
            game->collectibles[0].collected = 1;

            playAudioFileWithDelay("audio/samplepickup.mp3", 0);
            playAudioFileWithDelay("audio/raresampleacquired.mp3", 2);
            game->extract[0].is_activated = 1;
        }
        else if (is_player_close_to_extract(game) && game->extract->is_activated)
        {
            playAudioFileWithDelay("audio/extract01.mp3", 2);
            // playAudioFileWithDelay("audio/extract02.mp3", 2);
        }
    }
}