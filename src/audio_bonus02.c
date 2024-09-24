/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:44:14 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 15:30:48 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d_audio_bonus.h"

// void	cleanup_audio_sources(t_audio_manager *audio)
// {
// 	int	i;

// 	if (audio->source_count > 0)
// 	{
// 		i = 0;
// 		while (i < audio->source_count)
// 		{
// 			alSourceStop(audio->sources[i]);
// 			alDeleteSources(1, &audio->sources[i]);
// 			i++;
// 		}
// 	}
// }

void cleanup_audio_sources(t_audio_manager *audio)
{
    int i;
    ALint buffer;

    if (audio->source_count > 0)
    {
        for (i = 0; i < audio->source_count; i++)
        {
            // Stop the source
            alSourceStop(audio->sources[i]);

            // Detach the buffer from the source
            alSourcei(audio->sources[i], AL_BUFFER, 0);

            // Get the buffer attached to the source
            alGetSourcei(audio->sources[i], AL_BUFFER, &buffer);

            // If there was a buffer attached, delete it
            if (buffer)
                alDeleteBuffers(1, (ALuint*)&buffer);

            // Delete the source
            alDeleteSources(1, &audio->sources[i]);
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

// void	cleanup_audio(t_game *game)
// {
// 	t_audio_manager	*audio;

// 	audio = game->audio;
// 	if (!audio)
// 		return ;
// 	cleanup_audio_sources(audio);
// 	cleanup_audio_context(audio);
// 	cleanup_audio_device(audio);
// 	mpg123_exit();
// 	free(audio);
// 	game->audio = NULL;
// }

void cleanup_audio(t_game *game)
{
    t_audio_manager *audio;

    audio = game->audio;
    if (!audio)
        return;

	printf("cleanup_audio: cleaning up audio\n");
    // Stop all sources and delete them
    cleanup_audio_sources(audio);

    // Destroy the context
    cleanup_audio_context(audio);

    // Close the device
    cleanup_audio_device(audio);

    // Shutdown mpg123
    mpg123_exit();

    // Free the audio manager
    free(audio);
    game->audio = NULL;

    // Ensure all OpenAL operations are complete
    alGetError(); // Clear any existing errors
    alcMakeContextCurrent(NULL);

    // Instead of waiting in a loop, we'll just ensure the current context is null
    if (alcGetCurrentContext() != NULL) {
        fprintf(stderr, "Warning: OpenAL context still exists after cleanup\n");
    }
}
