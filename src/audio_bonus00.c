/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:14:21 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/12 15:45:42 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d_audio_bonus.h"

static int	allocate_audio_manager(t_game *game)
{
	t_audio_manager	*audio;

	audio = malloc(sizeof(t_audio_manager));
	if (!audio)
	{
		fprintf(stderr, "Failed to allocate memory for audio manager\n");
		return (-1);
	}
	game->audio = audio;
	return (0);
}

static int	initialize_openal(t_audio_manager *audio)
{
	audio->device = alcOpenDevice(NULL);
	if (!audio->device)
	{
		fprintf(stderr, "Unable to open default device\n");
		return (-1);
	}
	audio->context = alcCreateContext(audio->device, NULL);
	alcMakeContextCurrent(audio->context);
	return (0);
}

static void	initialize_sources(t_audio_manager *audio)
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

int	initialize_audio(t_game *game)
{
	if (allocate_audio_manager(game) != 0)
		return (-1);
	if (initialize_openal(game->audio) != 0)
	{
		free(game->audio);
		game->audio = NULL;
		return (-1);
	}
	initialize_sources(game->audio);
	mpg123_init();
	return (0);
}


void cleanup_audio(t_game *game)
{
	t_audio_manager *audio = game->audio;
	if (!audio) return;

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
	t_audio_manager *audio = game->audio;
	ALint state;
	for (int i = 0; i < audio->source_count; i++) {
		alGetSourcei(audio->sources[i], AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING) {
			return i;
		}
	}
	return -1; // No available source
}



static int find_and_prepare_source(t_game *game, const char *filename)
{
	int sourceIndex = find_available_source(game);
	if (sourceIndex == -1) {
		fprintf(stderr, "No available sources to play audio\n");
		return -1;
	}
	printf("Playing audio %s on source %d\n", filename, sourceIndex);
	return sourceIndex;
}

static mpg123_handle *initialize_mpg123(const char *filename, long *rate, int *channels, int *encoding)
{
	mpg123_handle *mh = mpg123_new(NULL, NULL);
	mpg123_open(mh, filename);
	mpg123_getformat(mh, rate, channels, encoding);
	return mh;
}

static char *decode_mp3(mpg123_handle *mh, size_t *totalSize)
{
	size_t buffer_size = mpg123_outblock(mh);
	unsigned char *buffer_data = malloc(buffer_size * sizeof(unsigned char));
	char *totalBuffer = NULL;
	*totalSize = 0;
	size_t done;

	while (mpg123_read(mh, buffer_data, buffer_size, &done) == MPG123_OK) {
		totalBuffer = realloc(totalBuffer, *totalSize + done);
		memcpy(totalBuffer + *totalSize, buffer_data, done);
		*totalSize += done;
	}

	free(buffer_data);
	return totalBuffer;
}

static ALuint create_al_buffer(char *totalBuffer, size_t totalSize, int channels, long rate)
{
	ALuint buffer;
	alGenBuffers(1, &buffer);
	ALenum format = (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
	alBufferData(buffer, format, totalBuffer, totalSize, rate);
	return buffer;
}

static void play_and_record_audio(t_audio_manager *audio, int sourceIndex, ALuint buffer, const char *filename)
{
	alSourcei(audio->sources[sourceIndex], AL_BUFFER, buffer);
	alSourcePlay(audio->sources[sourceIndex]);

	gettimeofday(&audio->last_play_time[sourceIndex], NULL);

	strncpy(audio->playing_tracks[sourceIndex].filename, filename, 255);
	audio->playing_tracks[sourceIndex].filename[255] = '\0';
	audio->playing_tracks[sourceIndex].source_index = sourceIndex;
}
int play_audio_file(t_game *game, const char *filename, float delayInSeconds)
{
	(void)delayInSeconds;  // Unused parameter
	t_audio_manager *audio = game->audio;
	int sourceIndex = find_and_prepare_source(game, filename);
	if (sourceIndex == -1) return -1;

	long rate;
	int channels, encoding;
	mpg123_handle *mh = initialize_mpg123(filename, &rate, &channels, &encoding);
	if (!mh) return -1;

	size_t totalSize;
	char *totalBuffer = decode_mp3(mh, &totalSize);
	if (!totalBuffer) {
		mpg123_close(mh);
		mpg123_delete(mh);
		return -1;
	}

	ALuint buffer = create_al_buffer(totalBuffer, totalSize, channels, rate);

	play_and_record_audio(audio, sourceIndex, buffer, filename);
	free(totalBuffer);
	mpg123_close(mh);
	mpg123_delete(mh);
	return 0;
}


int stop_audio_file(t_game *game, const char *filename)
{
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
