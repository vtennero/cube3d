/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_bonus05.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:39:25 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:28:32 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	trigger_extract_victory(t_game *game)
{
	play_audio_file(game, "audio/extract05.mp3", 0);
	(void)game;
}

void	trigger_extract_music(t_game *game)
{
	play_audio_file(game, "audio/extractmusic00.mp3", 0);
	(void)game;
}

void	trigger_landing(t_game *game)
{
	game->extract[0].is_landing = 1;
	game->extract[0].is_activated = 0;
	play_audio_file(game, "audio/pelican00.mp3", 0);
}

void	trigger_prelanding(t_game *game)
{
	(void)game;
	play_audio_file(game, "audio/eta.mp3", 0);
}

void	extraction_available(t_game *game)
{
	(void)game;
	if (game->extract[0].is_activated == 0)
		play_audio_file(game, "audio/extractionready.mp3", 0);
}
