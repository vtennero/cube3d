/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:17:52 by toto              #+#    #+#             */
/*   Updated: 2024/08/27 11:45:27 by vitenner         ###   ########.fr       */
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

#define MAX_SOURCES 50

ALCdevice *device = NULL;
ALCcontext *context = NULL;
ALuint sources[MAX_SOURCES];
int sourceCount = 0;
struct timeval lastPlayTime[MAX_SOURCES];

// New structure to keep track of playing audio files
typedef struct {
    char filename[256];
    int sourceIndex;
} AudioTrack;

AudioTrack playingTracks[MAX_SOURCES];

// Initialization function
int initializeAudio()
{
    device = alcOpenDevice(NULL);
    if (!device) {
        fprintf(stderr, "Unable to open default device\n");
        return -1;
    }

    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    // Generate multiple sources
    alGenSources(MAX_SOURCES, sources);
    sourceCount = MAX_SOURCES;

    // Initialize lastPlayTime for each source
    for (int i = 0; i < MAX_SOURCES; i++) {
        gettimeofday(&lastPlayTime[i], NULL);
    }

    // Initialize libmpg123
    mpg123_init();

    return 0;
}

// Cleanup function
void cleanupAudio()
{
    if (sourceCount > 0) {
        for (int i = 0; i < sourceCount; i++) {
            alSourceStop(sources[i]);
            alDeleteSources(1, &sources[i]);
        }
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
    sourceCount = 0;

    mpg123_exit();
}

// Function to find an available source
int findAvailableSource()
{
    ALint state;
    for (int i = 0; i < sourceCount; i++) {
        alGetSourcei(sources[i], AL_SOURCE_STATE, &state);
        if (state != AL_PLAYING) {
            return i;
        }
    }
    return -1;  // No available source
}

int stopAudioFile(const char* filename)
{
    for (int i = 0; i < MAX_SOURCES; i++) {
        if (strcmp(playingTracks[i].filename, filename) == 0) {
            alSourceStop(sources[playingTracks[i].sourceIndex]);
            playingTracks[i].filename[0] = '\0';  // Clear the filename
            return 0;
        }
    }
    fprintf(stderr, "Audio file %s not found or not playing\n", filename);
    return -1;
}

// Function to play audio with optional delay
int playAudioFileWithDelay(const char* filename, float delayInSeconds)
{
    int sourceIndex = findAvailableSource();
    if (sourceIndex == -1) {
        fprintf(stderr, "No available sources to play audio\n");
        return -1;
    }

    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    // Check if enough time has passed since the last play
    double timeSinceLastPlay = (currentTime.tv_sec - lastPlayTime[sourceIndex].tv_sec) + 
                               (currentTime.tv_usec - lastPlayTime[sourceIndex].tv_usec) / 1000000.0;

    if (timeSinceLastPlay < delayInSeconds) {
        // If not enough time has passed, schedule the sound to play later
        delayInSeconds -= timeSinceLastPlay;
    } else {
        delayInSeconds = 0;  // Play immediately
    }

    printf("Playing audio %s on source %d with delay %.2f seconds\n", filename, sourceIndex, delayInSeconds);

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

    // Generate a new buffer
    ALuint buffer;
    alGenBuffers(1, &buffer);

    // Load audio data into AL buffer
    ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    alBufferData(buffer, format, totalBuffer, totalSize, rate);

    // Set source buffer and play
    alSourcei(sources[sourceIndex], AL_BUFFER, buffer);
    
    if (delayInSeconds > 0) {
        alSourcef(sources[sourceIndex], AL_SEC_OFFSET, -delayInSeconds);
    }
    
    alSourcePlay(sources[sourceIndex]);

    // Update last play time
    gettimeofday(&lastPlayTime[sourceIndex], NULL);

    // Add to playing tracks
    strncpy(playingTracks[sourceIndex].filename, filename, 255);
    playingTracks[sourceIndex].filename[255] = '\0';  // Ensure null-termination
    playingTracks[sourceIndex].sourceIndex = sourceIndex;

    // Update last play time
    gettimeofday(&lastPlayTime[sourceIndex], NULL);

    // Clean up
    free(totalBuffer);
    free(buffer_data);
    mpg123_close(mh);
    mpg123_delete(mh);

    return 0;
}

// int stopAudioFile(const char* filename) {
//     for (int i = 0; i < MAX_SOURCES; i++) {
//         if (strcmp(playingTracks[i].filename, filename) == 0) {
//             alSourceStop(sources[playingTracks[i].sourceIndex]);
//             playingTracks[i].filename[0] = '\0';  // Clear the filename
//             return 0;
//         }
//     }
//     fprintf(stderr, "Audio file %s not found or not playing\n", filename);
//     return -1;
// }