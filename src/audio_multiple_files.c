/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:17:52 by toto              #+#    #+#             */
/*   Updated: 2024/08/10 15:31:44 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <mpg123.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10

ALCdevice *device = NULL;
ALCcontext *context = NULL;
ALuint source = 0;
ALuint buffers[MAX_QUEUE_SIZE] = {0};
char *filenames[MAX_QUEUE_SIZE] = {NULL};
int queue_size = 0;
int current_buffer = 0;



int loadAudioFile(const char* filename, ALuint buffer)
{
    mpg123_handle *mh;
    unsigned char *buffer_data;
    size_t buffer_size;
    size_t done;
    int channels, encoding;
    long rate;

    // Initialize libmpg123
    mpg123_init();
    mh = mpg123_new(NULL, NULL);
    mpg123_open(mh, filename);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    // Set the stream format
    buffer_size = mpg123_outblock(mh);
    buffer_data = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

    // Read and play
    size_t totalSize = 0;
    char *totalBuffer = NULL;

    while (mpg123_read(mh, buffer_data, buffer_size, &done) == MPG123_OK) {
        totalBuffer = realloc(totalBuffer, totalSize + done);
        memcpy(totalBuffer + totalSize, buffer_data, done);
        totalSize += done;
    }

    // Load audio data into AL buffer
    ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    alBufferData(buffer, format, totalBuffer, totalSize, rate);

    // Clean up
    free(totalBuffer);
    free(buffer_data);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();

    return 0;
}

void audio_callback(void* userdata, ALuint source)
{
    (void)userdata;  // Unused parameter
    
    ALint processed = 0;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);
    
    while (processed--)
    {
        ALuint buffer;
        alSourceUnqueueBuffers(source, 1, &buffer);
        
        current_buffer++;
        if (current_buffer < queue_size)
        {
            // Load and queue the next buffer
            if (loadAudioFile(filenames[current_buffer], buffers[current_buffer]) == 0)
            {
                alSourceQueueBuffers(source, 1, &buffers[current_buffer]);
            }
        }
    }
    
    // Check if the source is still playing, if not, start it again
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state != AL_PLAYING)
    {
        alSourcePlay(source);
    }
}

int initAudio()
{
    device = alcOpenDevice(NULL);
    if (!device) {
        fprintf(stderr, "Unable to open default device\n");
        return -1;
    }

    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    alGenSources(1, &source);
    alGenBuffers(MAX_QUEUE_SIZE, buffers);

    // Set up the source
    alSourcei(source, AL_SOURCE_TYPE, AL_STREAMING);
    alSourcei(source, AL_BUFFER, 0);
    
    // Disable 3D audio features
    alSourcei(source, AL_SOURCE_RELATIVE, AL_TRUE);
    alSourcef(source, AL_ROLLOFF_FACTOR, 0.0f);
    alDopplerFactor(0.0f);

    return 0;
}

int playAudioFiles(const char** files, int count)
{
    if (count > MAX_QUEUE_SIZE) {
        fprintf(stderr, "Too many files to queue\n");
        return -1;
    }

    if (!device && initAudio() != 0) {
        return -1;
    }

    queue_size = count;
    for (int i = 0; i < count; i++) {
        filenames[i] = strdup(files[i]);
    }

    // Load and queue the first file
    if (loadAudioFile(filenames[0], buffers[0]) == 0) {
        alSourceQueueBuffers(source, 1, &buffers[0]);
        alSourcePlay(source);
    }

    return 0;
}

void stopAudio() {
    if (source) {
        alSourceStop(source);
        alDeleteSources(1, &source);
        alDeleteBuffers(MAX_QUEUE_SIZE, buffers);
    }
    if (context) {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
    }
    if (device) {
        alcCloseDevice(device);
    }
    device = NULL;
    context = NULL;
    source = 0;
    for (int i = 0; i < queue_size; i++) {
        free(filenames[i]);
        filenames[i] = NULL;
    }
    queue_size = 0;
    current_buffer = 0;
}