/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_item_collection_bonus00.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:29:17 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:29:17 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

void	handle_key_e(t_game *game)
{
	int	extract_eta;

	game->key_state[K_E] = 1;
	if (is_player_close_to_collectible(game))
	{
		game->collectibles[0].collected = 1;
		game->extract[0].is_available = 1;
		play_audio_file(game, "audio/samplepickup.mp3", 0);
		add_script(game, sample_acquired, 1);
		add_script(game, extraction_available, 5);
	}
	else if (is_player_close_to_extract(game) && game->extract->is_available)
	{
		play_audio_file(game, "audio/extract01.mp3", 0);
		play_audio_file(game, "audio/extractkeyboard.mp3", 0);
		game->extract[0].is_available = 0;
		game->extract[0].is_activated = 1;
		add_script(game, trigger_extract_music, 1);
		add_script(game, trigger_landing, EXTRACT_CALL_TIME);
		extract_eta = EXTRACT_CALL_TIME - 10;
		if (EXTRACT_CALL_TIME - 10 > 0)
			add_script(game, trigger_prelanding, extract_eta);
	}
}
