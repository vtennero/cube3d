/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:14:21 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/12 15:15:45 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d_audio_bonus.h"

int initialize_audio_device(t_audio_manager *audio) {
    audio->device = alcOpenDevice(NULL);
    if (!audio->device) {
        fprintf(stderr, "Unable to open default device\n");
        return -1;
    }
    return 0;
}

int initialize_audio_context(t_audio_manager *audio) {
    audio->context = alcCreateContext(audio->device, NULL);
    if (!audio->context) {
        fprintf(stderr, "Failed to create audio context\n");
        return -1;
    }
    alcMakeContextCurrent(audio->context);
    return 0;
}

void initialize_audio_sources(t_audio_manager *audio) {
    alGenSources(MAX_SOURCES, audio->sources);
    audio->source_count = MAX_SOURCES;
    for (int i = 0; i < MAX_SOURCES; i++) {
        gettimeofday(&audio->last_play_time[i], NULL);
    }
}

int initialize_audio(t_game *game) {
    t_audio_manager *audio = malloc(sizeof(t_audio_manager));
    if (!audio) {
        fprintf(stderr, "Failed to allocate memory for audio manager\n");
        return -1;
    }
    game->audio = audio;

    if (initialize_audio_device(audio) != 0) {
        free(audio);
        game->audio = NULL;
        return -1;
    }

    if (initialize_audio_context(audio) != 0) {
        alcCloseDevice(audio->device);
        free(audio);
        game->audio = NULL;
        return -1;
    }

    initialize_audio_sources(audio);
    mpg123_init();
    return 0;
}

void cleanup_audio_sources(t_audio_manager *audio) {
    if (audio->source_count > 0) {
        for (int i = 0; i < audio->source_count; i++) {
            alSourceStop(audio->sources[i]);
            alDeleteSources(1, &audio->sources[i]);
        }
    }
}

void cleanup_audio_context(t_audio_manager *audio) {
    if (audio->context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(audio->context);
    }
}

void cleanup_audio_device(t_audio_manager *audio) {
    if (audio->device) {
        alcCloseDevice(audio->device);
    }
}

void cleanup_audio(t_game *game) {
    if (!game->audio) return;
    t_audio_manager *audio = game->audio;

    cleanup_audio_sources(audio);
    cleanup_audio_context(audio);
    cleanup_audio_device(audio);

    mpg123_exit();
    free(audio);
    game->audio = NULL;
}

int find_available_source(t_audio_manager *audio) {
    ALint state;
    for (int i = 0; i < audio->source_count; i++) {
        alGetSourcei(audio->sources[i], AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING) {
            return i;
        }
    }
    return -1; // No available source
}

double calculate_delay(t_audio_manager *audio, int sourceIndex, float requestedDelay) {
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    double timeSinceLastPlay = (currentTime.tv_sec - audio->last_play_time[sourceIndex].tv_sec)
        + (currentTime.tv_usec - audio->last_play_time[sourceIndex].tv_usec) / 1000000.0;

    if (timeSinceLastPlay < requestedDelay) {
        return requestedDelay - timeSinceLastPlay;
    }
    return 0;
}

int decode_audio_file(const char *filename, char **buffer, size_t *bufferSize, long *rate, int *channels) {
    mpg123_handle *mh = mpg123_new(NULL, NULL);
    unsigned char *buffer_data;
    size_t buffer_size, done;
    int encoding;

    mpg123_open(mh, filename);
    mpg123_getformat(mh, rate, channels, &encoding);

    buffer_size = mpg123_outblock(mh);
    buffer_data = malloc(buffer_size * sizeof(unsigned char));

    *bufferSize = 0;
    *buffer = NULL;
    while (mpg123_read(mh, buffer_data, buffer_size, &done) == MPG123_OK) {
        *buffer = realloc(*buffer, *bufferSize + done);
        memcpy(*buffer + *bufferSize, buffer_data, done);
        *bufferSize += done;
    }

    free(buffer_data);
    mpg123_close(mh);
    mpg123_delete(mh);
    return 0;
}

int create_and_fill_al_buffer(const char *data, size_t dataSize, int channels, long rate, ALuint *buffer) {
    alGenBuffers(1, buffer);
    ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    alBufferData(*buffer, format, data, dataSize, rate);
    return 0;
}

int play_audio_with_delay(t_audio_manager *audio, int sourceIndex, ALuint buffer, float delay) {
    alSourcei(audio->sources[sourceIndex], AL_BUFFER, buffer);
    if (delay > 0) {
        alSourcef(audio->sources[sourceIndex], AL_SEC_OFFSET, -delay);
    }
    alSourcePlay(audio->sources[sourceIndex]);
    gettimeofday(&audio->last_play_time[sourceIndex], NULL);
    return 0;
}

int play_audio_file(t_game *game, const char *filename, float delayInSeconds) {
    t_audio_manager *audio = game->audio;
    int sourceIndex = find_available_source(audio);
    if (sourceIndex == -1) {
        fprintf(stderr, "No available sources to play audio\n");
        return -1;
    }

    float actualDelay = calculate_delay(audio, sourceIndex, delayInSeconds);
    printf("Playing audio %s on source %d with delay %.2f seconds\n", filename, sourceIndex, actualDelay);

    char *totalBuffer;
    size_t totalSize;
    long rate;
    int channels;
    decode_audio_file(filename, &totalBuffer, &totalSize, &rate, &channels);

    ALuint buffer;
    create_and_fill_al_buffer(totalBuffer, totalSize, channels, rate, &buffer);

    play_audio_with_delay(audio, sourceIndex, buffer, actualDelay);

    strncpy(audio->playing_tracks[sourceIndex].filename, filename, 255);
    audio->playing_tracks[sourceIndex].filename[255] = '\0';
    audio->playing_tracks[sourceIndex].source_index = sourceIndex;

    free(totalBuffer);
    return 0;
}

int stop_audio_file(t_game *game, const char *filename) {
    t_audio_manager *audio = game->audio;

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
