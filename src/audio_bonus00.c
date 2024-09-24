/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:14:21 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:16:57 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d_audio_bonus.h"

int	initialize_audio(t_game *game)
{
	if (allocate_audio_manager(game) != 0)
		return (-1);
	if (initialize_openal(game->audio) != 0)
	{
		free(game->audio);
		game->audio = NULL;
		return (-1);
	}
	initialize_sources(game->audio);
	mpg123_init();
	return (0);
}

int	play_audio_file(t_game *game, const char *filename, float delay_in_seconds)
{
	t_audio_manager	*audio;
	int				source_index;
	mpg123_handle	*mh;
	int				result;

	(void)delay_in_seconds;
	audio = game->audio;
	source_index = find_and_prepare_source(game, filename);
	if (source_index == -1)
		return (-1);
	mh = initialize_mpg123(filename, NULL, NULL, NULL);
	if (!mh)
		return (-1);
	result = process_audio_data(mh, audio, source_index, filename);
	cleanup_mpg123(mh);
	return (result);
}

int	stop_audio_file(t_game *game, const char *filename)
{
	t_audio_manager	*audio;
	int				i;

	audio = game->audio;
	i = 0;
	while (i < MAX_SOURCES)
	{
		if (ft_strcmp(audio->playing_tracks[i].filename, filename) == 0)
		{
			alSourceStop(audio->sources[audio->playing_tracks[i].source_index]);
			audio->playing_tracks[i].filename[0] = '\0';
			return (0);
		}
		i++;
	}
	printf("stop_audio_file: Audio  %s not found or not playing\n", filename);
	return (-1);
}

void	cleanup_audio(t_game *game)
{
	t_audio_manager	*audio;

	audio = game->audio;
	if (!audio)
		return ;
	cleanup_audio_sources(audio);
	cleanup_audio_context(audio);
	cleanup_audio_device(audio);
	mpg123_exit();
	free(audio);
	game->audio = NULL;
	alGetError();
	alcMakeContextCurrent(NULL);
}
