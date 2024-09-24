/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_static_bonus05.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:01:08 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/13 13:01:08 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	script_die(t_game *game)
{
	if (game->player->hp <= 0 && game->player->is_dead == 0)
	{
		reset_game_start_time(game);
		game->player->is_dead = 1;
		game->player->is_burning = 0;
		game->player->hp = MAX_HEALTH;
		stop_audio_file(game, "audio/burn00.mp3");
		stop_audio_file(game, "audio/burn01.mp3");
		stop_audio_file(game, "audio/burn02.mp3");
		stop_audio_file(game, "audio/burn03.mp3");
		play_audio_file(game, "audio/death.mp3", 0);
		play_audio_file(game, "audio/kia00.mp3", 0);
	}
}

void	player_need_stims(t_game *game)
{
	int	random_value;

	random_value = random_int(game, 3);
	if (random_value == 0 && game->player->hp <= 0.25 * MAX_HEALTH)
	{
		stop_audio_file(game, "audio/stims00.mp3");
		play_audio_file(game, "audio/stims00.mp3", 0);
	}
}
