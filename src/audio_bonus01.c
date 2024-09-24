/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:11:40 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:16:19 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d_audio_bonus.h"

int	allocate_audio_manager(t_game *game)
{
	t_audio_manager	*audio;

	audio = ft_calloc(1, sizeof(t_audio_manager));
	if (!audio)
	{
		printf("Failed to allocate memory for audio manager\n");
		return (-1);
	}
	game->audio = audio;
	return (0);
}

int	initialize_openal(t_audio_manager *audio)
{
	audio->device = alcOpenDevice(NULL);
	if (!audio->device)
	{
		printf("Unable to open default device\n");
		return (-1);
	}
	audio->context = alcCreateContext(audio->device, NULL);
	alcMakeContextCurrent(audio->context);
	return (0);
}

void	initialize_sources(t_audio_manager *audio)
{
	int	i;

	alGenSources(MAX_SOURCES, audio->sources);
	audio->source_count = MAX_SOURCES;
	i = 0;
	while (i < MAX_SOURCES)
	{
		gettimeofday(&audio->last_play_time[i], NULL);
		i++;
	}
}

int	find_available_source(t_game *game)
{
	t_audio_manager	*audio;
	ALint			state;
	int				i;

	audio = game->audio;
	i = 0;
	while (i < audio->source_count)
	{
		alGetSourcei(audio->sources[i], AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING)
			return (i);
		i++;
	}
	return (-1);
}

int	find_and_prepare_source(t_game *game, const char *filename)
{
	int	source_index;

	source_index = find_available_source(game);
	if (source_index == -1)
	{
		printf("No available sources to play audio\n");
		return (-1);
	}
	printf("Playing audio %s on source %d\n", filename, source_index);
	return (source_index);
}
