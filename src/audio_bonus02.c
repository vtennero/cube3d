/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:44:14 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 14:56:17 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d_audio_bonus.h"

void	cleanup_audio_sources(t_audio_manager *audio)
{
	int	i;

	if (audio->source_count > 0)
	{
		i = 0;
		while (i < audio->source_count)
		{
			alSourceStop(audio->sources[i]);
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

void cleanup_audio_device(t_audio_manager *audio)
{
	if (audio->device)
	{
		ALCboolean closed = alcCloseDevice(audio->device);
		if (!closed)
			fprintf(stderr, "Failed to close audio device\n");
		audio->device = NULL;
	}
}

// void	cleanup_audio_device(t_audio_manager *audio)
// {
// 	if (audio->device)
// 		alcCloseDevice(audio->device);
// }

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
}
