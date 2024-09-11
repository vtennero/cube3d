/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:28:47 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 18:28:47 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <mpg123.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

typedef struct	s_audio_track
{
	char	filename[256];
	int		source_index;
}				t_audio_track;

typedef struct	s_audio_manager
{
	ALCdevice		*device;
	ALCcontext		*context;
	ALuint			sources[MAX_SOURCES];
	int				source_count;
	struct timeval	last_play_time[MAX_SOURCES];
	t_audio_track	playing_tracks[MAX_SOURCES];
}				t_audio_manager;

int initialize_audio(t_game *game)
{
    game->audio.device = alcOpenDevice(NULL);
    if (!game->audio.device) {
        fprintf(stderr, "Unable to open default device\n");
        return -1;
    }
    game->audio.context = alcCreateContext(game->audio.device, NULL);
    alcMakeContextCurrent(game->audio.context);

    alGenSources(MAX_SOURCES, game->audio.sources);
    game->audio.sourceCount = MAX_SOURCES;

    for (int i = 0; i < MAX_SOURCES; i++) {
        gettimeofday(&game->audio.lastPlayTime[i], NULL);
    }

    mpg123_init();
    return 0;
}

// Cleanup function
void cleanup_audio(t_game *game)
{
    if (game->audio.sourceCount > 0) {
        for (int i = 0; i < game->audio.sourceCount; i++) {
            alSourceStop(game->audio.sources[i]);
            alDeleteSources(1, &game->audio.sources[i]);
        }
    }
    if (game->audio.context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(game->audio.context);
    }
    if (game->audio.device) {
        alcCloseDevice(game->audio.device);
    }
    game->audio.device = NULL;
    game->audio.context = NULL;
    game->audio.sourceCount = 0;
    mpg123_exit();
}

int find_available_source(t_game *game)
{
    ALint state;
    for (int i = 0; i < game->audio.sourceCount; i++) {
        alGetSourcei(game->audio.sources[i], AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING) {
            return i;
        }
    }
    return -1; // No available source
}

int play_audio_file(t_game *game, const char *filename, float delayInSeconds)
{
    int             sourceIndex;
    struct timeval  currentTime;
    double          timeSinceLastPlay;
    mpg123_handle   *mh;
    unsigned char   *buffer_data;
    size_t          buffer_size;
    size_t          done;
    long            rate;
    size_t          totalSize;
    char            *totalBuffer;
    ALuint          buffer;
    ALenum          format;

    sourceIndex = find_available_source(game);
    if (sourceIndex == -1)
    {
        fprintf(stderr, "No available sources to play audio\n");
        return (-1);
    }
    gettimeofday(&currentTime, NULL);
    // Check if enough time has passed since the last play
    timeSinceLastPlay = (currentTime.tv_sec - game->audio.lastPlayTime[sourceIndex].tv_sec)
        + (currentTime.tv_usec - game->audio.lastPlayTime[sourceIndex].tv_usec) / 1000000.0;
    if (timeSinceLastPlay < delayInSeconds)
    {
        // If not enough time has passed, schedule the sound to play later
        delayInSeconds -= timeSinceLastPlay;
    }
    else
    {
        delayInSeconds = 0; // Play immediately
    }
    printf("Playing audio %s on source %d with delay %.2f seconds\n", filename,
        sourceIndex, delayInSeconds);
    // libmpg123 variables
    int channels, encoding;
    mh = mpg123_new(NULL, NULL);
    mpg123_open(mh, filename);
    mpg123_getformat(mh, &rate, &channels, &encoding);
    // Set the stream format
    buffer_size = mpg123_outblock(mh);
    buffer_data = (unsigned char *)malloc(buffer_size * sizeof(unsigned char));
    // Read and play
    totalSize = 0;
    totalBuffer = NULL;
    while (mpg123_read(mh, buffer_data, buffer_size, &done) == MPG123_OK)
    {
        totalBuffer = realloc(totalBuffer, totalSize + done);
        memcpy(totalBuffer + totalSize, buffer_data, done);
        totalSize += done;
    }
    // Generate a new buffer
    alGenBuffers(1, &buffer);
    // Load audio data into AL buffer
    format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    alBufferData(buffer, format, totalBuffer, totalSize, rate);
    // Set source buffer and play
    alSourcei(game->audio.sources[sourceIndex], AL_BUFFER, buffer);
    if (delayInSeconds > 0)
    {
        alSourcef(game->audio.sources[sourceIndex], AL_SEC_OFFSET, -delayInSeconds);
    }
    alSourcePlay(game->audio.sources[sourceIndex]);
    // Update last play time
    gettimeofday(&game->audio.lastPlayTime[sourceIndex], NULL);
    // Add to playing tracks
    strncpy(game->audio.playingTracks[sourceIndex].filename, filename, 255);
    game->audio.playingTracks[sourceIndex].filename[255] = '\0'; // Ensure null-termination
    game->audio.playingTracks[sourceIndex].sourceIndex = sourceIndex;
    // Clean up
    free(totalBuffer);
    free(buffer_data);
    mpg123_close(mh);
    mpg123_delete(mh);
    return (0);
}

int stop_audio_file(t_game *game, const char *filename)
{
    for (int i = 0; i < MAX_SOURCES; i++)
    {
        if (strcmp(game->audio.playingTracks[i].filename, filename) == 0)
        {
            alSourceStop(game->audio.sources[game->audio.playingTracks[i].sourceIndex]);
            game->audio.playingTracks[i].filename[0] = '\0'; // Clear the filename
            return (0);
        }
    }
    fprintf(stderr, "stop_audio_file: Audio file %s not found or not playing\n",
        filename);
    return (-1);
}
