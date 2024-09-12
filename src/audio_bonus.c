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
#include "cube3d_audio_bonus.h"
int initialize_audio(t_game *game)
{
    t_audio_manager *audio = malloc(sizeof(t_audio_manager));
    if (!audio) {
        fprintf(stderr, "Failed to allocate memory for audio manager\n");
        return -1;
    }
    game->audio = audio;

    audio->device = alcOpenDevice(NULL);
    if (!audio->device) {
        fprintf(stderr, "Unable to open default device\n");
        free(audio);
        game->audio = NULL;
        return -1;
    }
    audio->context = alcCreateContext(audio->device, NULL);
    alcMakeContextCurrent(audio->context);

    alGenSources(MAX_SOURCES, audio->sources);
    audio->source_count = MAX_SOURCES;

    for (int i = 0; i < MAX_SOURCES; i++) {
        gettimeofday(&audio->last_play_time[i], NULL);
    }

    mpg123_init();
    return 0;
}

void cleanup_audio(t_game *game)
{
    if (!game->audio) return;
    t_audio_manager *audio = (t_audio_manager *)game->audio;

    if (audio->source_count > 0) {
        for (int i = 0; i < audio->source_count; i++) {
            alSourceStop(audio->sources[i]);
            alDeleteSources(1, &audio->sources[i]);
        }
    }
    if (audio->context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(audio->context);
    }
    if (audio->device) {
        alcCloseDevice(audio->device);
    }
    mpg123_exit();
    free(audio);
    game->audio = NULL;
}

int find_available_source(t_game *game)
{
    t_audio_manager *audio = (t_audio_manager *)game->audio;

    ALint state;
    for (int i = 0; i < audio->source_count; i++) {
        alGetSourcei(audio->sources[i], AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING) {
            return i;
        }
    }
    return -1; // No available source
}

int play_audio_file(t_game *game, const char *filename, float delayInSeconds)
{
    t_audio_manager *audio = (t_audio_manager *)game->audio;
    int sourceIndex;
    struct timeval currentTime;
    double timeSinceLastPlay;
    mpg123_handle *mh;
    unsigned char *buffer_data;
    size_t buffer_size;
    size_t done;
    long rate;
    size_t totalSize;
    char *totalBuffer;
    ALuint buffer;
    ALenum format;
    int channels, encoding;

    sourceIndex = find_available_source(game);
    if (sourceIndex == -1) {
        fprintf(stderr, "No available sources to play audio\n");
        return -1;
    }

    gettimeofday(&currentTime, NULL);
    timeSinceLastPlay = (currentTime.tv_sec - audio->last_play_time[sourceIndex].tv_sec)
        + (currentTime.tv_usec - audio->last_play_time[sourceIndex].tv_usec) / 1000000.0;

    if (timeSinceLastPlay < delayInSeconds) {
        delayInSeconds -= timeSinceLastPlay;
    } else {
        delayInSeconds = 0;
    }

    printf("Playing audio %s on source %d with delay %.2f seconds\n", filename, sourceIndex, delayInSeconds);

    mh = mpg123_new(NULL, NULL);
    mpg123_open(mh, filename);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    buffer_size = mpg123_outblock(mh);
    buffer_data = (unsigned char *)malloc(buffer_size * sizeof(unsigned char));

    totalSize = 0;
    totalBuffer = NULL;
    while (mpg123_read(mh, buffer_data, buffer_size, &done) == MPG123_OK) {
        totalBuffer = realloc(totalBuffer, totalSize + done);
        memcpy(totalBuffer + totalSize, buffer_data, done);
        totalSize += done;
    }

    alGenBuffers(1, &buffer);
    format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    alBufferData(buffer, format, totalBuffer, totalSize, rate);

    alSourcei(audio->sources[sourceIndex], AL_BUFFER, buffer);
    if (delayInSeconds > 0) {
        alSourcef(audio->sources[sourceIndex], AL_SEC_OFFSET, -delayInSeconds);
    }
    alSourcePlay(audio->sources[sourceIndex]);

    gettimeofday(&audio->last_play_time[sourceIndex], NULL);

    strncpy(audio->playing_tracks[sourceIndex].filename, filename, 255);
    audio->playing_tracks[sourceIndex].filename[255] = '\0';
    audio->playing_tracks[sourceIndex].source_index = sourceIndex;

    free(totalBuffer);
    free(buffer_data);
    mpg123_close(mh);
    mpg123_delete(mh);
    return 0;
}

int stop_audio_file(t_game *game, const char *filename)
{
    t_audio_manager *audio = (t_audio_manager *)game->audio;

    for (int i = 0; i < MAX_SOURCES; i++) {
        if (strcmp(audio->playing_tracks[i].filename, filename) == 0) {
            alSourceStop(audio->sources[audio->playing_tracks[i].source_index]);
            audio->playing_tracks[i].filename[0] = '\0';
            return 0;
        }
    }
    fprintf(stderr, "stop_audio_file: Audio file %s not found or not playing\n", filename);
    return -1;
}