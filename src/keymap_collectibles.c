/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap_collectibles.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:07:42 by toto              #+#    #+#             */
/*   Updated: 2024/08/10 18:07:58 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define COLLECTION_DISTANCE 1.0f  // Adjust this value as needed

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

void handle_key_e(t_game *game)
{
    if (game->key_state[K_E] == 1 && is_player_close_to_collectible(game))
	{
		game->collectibles[0].collected = 1;
		// playAudioFile("audio/samplepickup.mp3");
        // stopAudio();

		// playAudioFile("audio/raresampleacquired.mp3");
        // stopAudio();
	
    	// const char* audio_files[] = {
		// 	"audio/raresampleacquired.mp3",
		// 	"audio/samplepickup.mp3",
		// };
		// playAudioFiles(audio_files, 2);

	}
	// add case for terminal
}