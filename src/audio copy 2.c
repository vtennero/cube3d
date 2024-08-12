/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio copy 2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:17:52 by toto              #+#    #+#             */
/*   Updated: 2024/08/12 17:59:52 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <mpg123.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this works for several files!!!! it rocks.

ALCdevice *device = NULL;
ALCcontext *context = NULL;
ALuint source = 0;
ALuint buffer = 0;
ALuint currentBuffer = 0;  // Add this as a global variable

int initializeAudio() {
    device = alcOpenDevice(NULL);
    if (!device) {
        fprintf(stderr, "Unable to open default device\n");
        return -1;
    }

    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    alGenSources(1, &source);
    // Remove the buffer generation here

    // Initialize libmpg123
    mpg123_init();

    return 0;
}

void cleanupAudio() {
    if (source) {
        alSourceStop(source);
        alDeleteSources(1, &source);
    }
    if (currentBuffer) {
        alDeleteBuffers(1, &currentBuffer);
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
    currentBuffer = 0;

    mpg123_exit();
}


int playAudioFile(const char* filename) {
    printf("playing audio %s\n", filename);
    
    // libmpg123 variables
    mpg123_handle *mh;
    unsigned char *buffer_data;
    size_t buffer_size;
    size_t done;
    int channels, encoding;
    long rate;

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

    // Stop the current source and delete the old buffer
    alSourceStop(source);
    if (currentBuffer != 0) {
        alDeleteBuffers(1, &currentBuffer);
    }

    // Generate a new buffer
    alGenBuffers(1, &currentBuffer);

    // Load audio data into AL buffer
    ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    alBufferData(currentBuffer, format, totalBuffer, totalSize, rate);

    // Set source buffer and play
    alSourcei(source, AL_BUFFER, currentBuffer);
    alSourcePlay(source);

    // Clean up
    free(totalBuffer);
    free(buffer_data);
    mpg123_close(mh);
    mpg123_delete(mh);

    return 0;
}