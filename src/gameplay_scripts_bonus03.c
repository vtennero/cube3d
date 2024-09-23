/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_bonus03.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:08:01 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 16:40:22 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	play_random_eagle_call(t_game *game)
{
	int		random_call;
	char	audio_file[18];

	ft_strcpy(audio_file, "audio/eaglec00.mp3");
	random_call = random_int(game, 6);
	audio_file[12] = '0' + random_call / 10;
	audio_file[13] = '0' + random_call % 10;
	play_audio_file(game, audio_file, 0);
}

void	remove_napalm(t_game *game)
{
	game->strike[1].is_active = 0;
}

void	delay_strike_hit(t_game *game)
{
	game->strike[0].is_active = 1;
}

void	delay_napalm_hit(t_game *game)
{
	game->strike[1].is_active = 1;
}

void	napalm_bombs(t_game *game)
{
	play_random_eagle_call(game);
	add_script(game, delay_napalm_hit, 1);
}

void	napalm_inbound(t_game *game)
{
	game->strike[1].is_launching = 0;
	add_script(game, napalm_bombs, 0);
	play_audio_file(game, "audio/eagles00.mp3", 0);
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

void	barrage_inbound(t_game *game)
{
	int		random_call;
	char	audio_file[30];

	random_call = random_int(game, 1);
	ft_strcpy(audio_file, "audio/orbitalbarragecall00.mp3");
	game->strike[2].is_active = 1;
	audio_file[24] = '0' + random_call / 10;
	audio_file[25] = '0' + random_call % 10;
	play_audio_file(game, audio_file, 0);
}

void	stop_barrage(t_game *game)
{
	game->strike[2].is_active = 0;
	game->strike[2].is_launching = 0;
	printf("Barrage over\n");
}

void	play_barrage_shell(t_game *game)
{
	int		random_call;
	char	audio_file[26];

	random_call = random_int(game, 2);
	ft_strcpy(audio_file, "audio/orbitalbarrage00.mp3");
	audio_file[20] = '0' + random_call / 10;
	audio_file[21] = '0' + random_call % 10;
	play_audio_file(game, audio_file, 0);
}
