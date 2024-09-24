/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_bonus00.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:59:49 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/20 16:59:49 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	get_hit(t_game *game)
{
	if (game->player->hp)
		game->player->hp--;
	game->player->is_hit = 0;
	player_need_stims(game);
}

void	menu_background(t_game *game)
{
	if (game->game_sequence == 0)
		play_audio_file(game, "audio/menu02.mp3", 2);
}

void	menu_background_voice(t_game *game)
{
	if (game->game_sequence == 0)
		play_audio_file(game, "audio/menu03.mp3", 2);
}
