/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_bonus04.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:08:06 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:40:22 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	sample_acquired(t_game *game)
{
	play_audio_file(game, "audio/raresampleacquired.mp3", 2);
	(void)game;
}

void	trigger_supply_take(t_game *game)
{
	game->player->taking_supplies = 1;
}

void	cancel_supply_take(t_game *game)
{
	game->player->taking_supplies = 0;
}

void	play_gun_sound(t_game *game)
{
	stop_audio_file(game, "audio/tmafir00.mp3");
	play_audio_file(game, "audio/tmafir00.mp3", 0);
	if (game->is_shooting)
		add_script(game, play_gun_sound, 0);
}

void	trigger_gunshots(t_game *game)
{
	if (game->is_shooting)
		add_script(game, play_gun_sound, 3);
}
