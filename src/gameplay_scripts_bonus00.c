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

void	sample_acquired(t_game *game)
{
	play_audio_file(game, "audio/raresampleacquired.mp3", 2);
	(void)game;
}

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
	printf("landing sequence initiated\n");
	play_audio_file(game, "audio/pelican00.mp3", 0);
}

void	trigger_prelanding(t_game *game)
{
	(void)game;
	printf("prelanding warning\n");
	play_audio_file(game, "audio/eta.mp3", 0);
}

void	extraction_available(t_game *game)
{
	(void)game;
	if (game->extract[0].is_activated == 0)
		play_audio_file(game, "audio/extractionready.mp3", 0);
}

void	play_gun_sound(t_game *game)
{
	stop_audio_file(game, "audio/tmafir00.mp3");
	play_audio_file(game, "audio/tmafir00.mp3", 0);
	if (game->is_shooting)
		add_script(game, play_gun_sound, 0);
}

void	trigger_supply_take(t_game *game)
{
	game->player->taking_supplies = 1;
}

void	cancel_supply_take(t_game *game)
{
	game->player->taking_supplies = 0;
}

void	trigger_gunshots(t_game *game)
{
	if (game->is_shooting)
		add_script(game, play_gun_sound, 3);
}
