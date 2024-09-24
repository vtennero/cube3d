/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_srikes_bonus02.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:34:08 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:35:07 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	play_random_eagle_call(t_game *game)
{
	int		random_call;
	char	audio_file[19];

	ft_strcpy(audio_file, "audio/eaglec00.mp3");
	random_call = random_int(game, 6);
	audio_file[12] = '0' + random_call / 10;
	audio_file[13] = '0' + random_call % 10;
	play_audio_file(game, audio_file, 0);
}

void	delay_strike_hit(t_game *game)
{
	game->strike[0].is_active = 1;
}

void	eagle_bombs(t_game *game)
{
	play_random_eagle_call(game);
	add_script(game, delay_strike_hit, 1);
}

void	eagle_inbound(t_game *game)
{
	game->strike[0].is_launching = 0;
	add_script(game, eagle_bombs, 0);
	play_audio_file(game, "audio/eagles00.mp3", 0);
}
