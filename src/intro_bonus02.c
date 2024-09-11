/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_bonus02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:55:30 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 18:53:07 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	initialize_randomized_frames(t_game *game)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < MAX_OPENING_TEXTURES - SECOND_LOOP_START)
	{
		game->opening_state.randomized_frames[i] = SECOND_LOOP_START + i;
		i++;
	}
	i = MAX_OPENING_TEXTURES - SECOND_LOOP_START - 1;
	while (i > 0)
	{
		j = random_int(game, i + 1);
		temp = game->opening_state.randomized_frames[i];
		game->opening_state.randomized_frames[i] = game->opening_state.randomized_frames[j];
		game->opening_state.randomized_frames[j] = temp;
		i--;
	}
	game->opening_state.randomized_frames_initialized = 1;
}



void	play_audio_on_frame(t_game *game, int frame_to_render)
{
	if (frame_to_render == 5)
		play_audio_file(game, "audio/drop01.mp3", 3);
	if (frame_to_render == 30)
		play_audio_file(game, "audio/drop03.mp3", 10);
}

int	prepare_second_loop(t_game *game)
{
	game->opening_state.current_loop = 1;
	game->opening_state.second_loop_count = 0;
	reset_game_start_time(game);
	if (!game->opening_state.randomized_frames_initialized)
		initialize_randomized_frames(game);
	return (game->opening_state.randomized_frames[0]);
}



void	check_second_loop_end(t_game *game)
{
	if (game->opening_state.second_loop_count >= SECOND_LOOP_REPETITIONS)
	{
		game->game_sequence = 2;
		game->opening_state.current_loop = 0;
		game->opening_state.second_loop_count = 0;
		game->opening_state.randomized_frames_initialized = 0;
	}
	else
		reset_game_start_time(game);
}


