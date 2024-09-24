/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_srikes_bonus01.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:34:00 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:35:27 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	barrage_inbound(t_game *game)
{
	int		random_call;
	char	audio_file[31];

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
	char	audio_file[27];

	random_call = random_int(game, 2);
	ft_strcpy(audio_file, "audio/orbitalbarrage00.mp3");
	audio_file[20] = '0' + random_call / 10;
	audio_file[21] = '0' + random_call % 10;
	play_audio_file(game, audio_file, 0);
}
