/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus03.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:14:12 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:18:28 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d_audio_bonus.h"

void	play_and_record_audio(t_audio_manager *audio, int source_index,
				ALuint buffer, const char *filename)
{
	alSourcei(audio->sources[source_index], AL_BUFFER, buffer);
	alSourcePlay(audio->sources[source_index]);
	gettimeofday(&audio->last_play_time[source_index], NULL);
	ft_strncpy(audio->playing_tracks[source_index].filename, filename, 255);
	audio->playing_tracks[source_index].filename[255] = '\0';
	audio->playing_tracks[source_index].source_index = source_index;
}

void	cleanup_audio_sources(t_audio_manager *audio)
{
	int		i;
	ALint	buffer;

	i = 0;
	if (audio->source_count > 0)
	{
		while (i < audio->source_count)
		{
			alSourceStop(audio->sources[i]);
			alSourcei(audio->sources[i], AL_BUFFER, 0);
			alGetSourcei(audio->sources[i], AL_BUFFER, &buffer);
			if (buffer)
				alDeleteBuffers(1, (ALuint *)&buffer);
			alDeleteSources(1, &audio->sources[i]);
			i++;
		}
	}
}

void	cleanup_audio_context(t_audio_manager *audio)
{
	if (audio->context)
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(audio->context);
		audio->context = NULL;
	}
}

void	cleanup_audio_device(t_audio_manager *audio)
{
	if (audio->device)
	{
		alcMakeContextCurrent(NULL);
		alcCloseDevice(audio->device);
		audio->device = NULL;
	}
}
