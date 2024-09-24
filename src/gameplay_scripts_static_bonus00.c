/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_static_bonus00.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:00:18 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:49:23 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	calculate_distance(t_vector2d point1, t_vector2d point2)
{
	t_vector2d	delta;

	delta.x = point1.x - point2.x;
	delta.y = point1.y - point2.y;
	return (sqrt(delta.x * delta.x + delta.y * delta.y));
}

void	play_random_burn_cry(t_game *game)
{
	int		random_call;
	char	audio_file[17];

	random_call = random_int(game, 4);
	ft_strcpy(audio_file, "audio/burn00.mp3");
	audio_file[10] = '0' + random_call / 10;
	audio_file[11] = '0' + random_call % 10;
	play_audio_file(game, audio_file, 0);
}

void	play_random_strike_sound(t_game *game)
{
	char	audio_file[19];
	int		random_strike;

	ft_strcpy(audio_file, "audio/strike00.mp3");
	random_strike = random_int(game, 3);
	audio_file[13] = '0' + random_strike;
	play_audio_file(game, audio_file, 0);
	play_audio_file(game, "audio/orbitalcall.mp3", 0);
}

void	play_land_voice(t_game *game)
{
	int		random_call;
	char	audio_file[17];

	random_call = random_int(game, 9);
	ft_strcpy(audio_file, "audio/land00.mp3");
	audio_file[10] = '0' + random_call / 10;
	audio_file[11] = '0' + random_call % 10;
	play_audio_file(game, audio_file, 0);
}
