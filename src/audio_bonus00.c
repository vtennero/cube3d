/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:14:21 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/12 16:25:32 by vitenner         ###   ########.fr       */
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
		printf("Failed to allocate memory for audio manager\n");
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
		printf("Unable to open default device\n");
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
	}
}

void	cleanup_audio_device(t_audio_manager *audio)
{
	if (audio->device)
		alcCloseDevice(audio->device);
}

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

int	find_available_source(t_game *game)
{
	t_audio_manager	*audio;
	ALint			state;
	int				i;

	audio = game->audio;
	i = 0;
	while (i < audio->source_count)
	{
		alGetSourcei(audio->sources[i], AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING)
			return (i);
		i++;
	}
	return (-1);
}

static int	find_and_prepare_source(t_game *game, const char *filename)
{
	int	source_index;

	source_index = find_available_source(game);
	if (source_index == -1)
	{
		printf("No available sources to play audio\n");
		return (-1);
	}
	printf("Playing audio %s on source %d\n", filename, source_index);
	return (source_index);
}

static mpg123_handle	*initialize_mpg123(const char *filename, long *rate,
						int *channels, int *encoding)
{
	mpg123_handle	*mh;

	mh = mpg123_new(NULL, NULL);
	mpg123_open(mh, filename);
	mpg123_getformat(mh, rate, channels, encoding);
	return (mh);
}

static char	*decode_mp3(mpg123_handle *mh, size_t *total_size)
{
	size_t			buffer_size;
	unsigned char	*buffer_data;
	char			*total_buffer;
	size_t			done;

	buffer_size = mpg123_outblock(mh);
	buffer_data = malloc(buffer_size * sizeof(unsigned char));
	total_buffer = NULL;
	*total_size = 0;
	while (mpg123_read(mh, buffer_data, buffer_size, &done) == MPG123_OK)
	{
		total_buffer = realloc(total_buffer, *total_size + done);
		memcpy(total_buffer + *total_size, buffer_data, done);
		*total_size += done;
	}
	free(buffer_data);
	return (total_buffer);
}

static ALuint	create_al_buffer(const char *total_buffer, size_t total_size,
				int channels, long rate)
{
	ALuint	buffer;
	ALenum	format;

	alGenBuffers(1, &buffer);
	if (channels == 1)
		format = AL_FORMAT_MONO16;
	else
		format = AL_FORMAT_STEREO16;
	alBufferData(buffer, format, total_buffer, total_size, rate);
	return (buffer);
}

static void	play_and_record_audio(t_audio_manager *audio, int source_index,
				ALuint buffer, const char *filename)
{
	alSourcei(audio->sources[source_index], AL_BUFFER, buffer);
	alSourcePlay(audio->sources[source_index]);
	gettimeofday(&audio->last_play_time[source_index], NULL);
	strncpy(audio->playing_tracks[source_index].filename, filename, 255);
	audio->playing_tracks[source_index].filename[255] = '\0';
	audio->playing_tracks[source_index].source_index = source_index;
}

static void	cleanup_mpg123(mpg123_handle *mh)
{
	mpg123_close(mh);
	mpg123_delete(mh);
}

static int    process_audio_data(mpg123_handle *mh, t_audio_manager *audio,
                int source_index, const char *filename)
{
    size_t    total_size;
    char    *total_buffer;
    long    rate;
    int        channels;
    int        encoding;
    ALuint    buffer;

    total_buffer = decode_mp3(mh, &total_size);
    if (!total_buffer)
    {
        cleanup_mpg123(mh);
        return (-1);
    }
    mpg123_getformat(mh, &rate, &channels, &encoding);
    buffer = create_al_buffer(total_buffer, total_size, channels, rate);
    play_and_record_audio(audio, source_index, buffer, filename);
    free(total_buffer);
    return (0);
}

int	play_audio_file(t_game *game, const char *filename, float delay_in_seconds)
{
	t_audio_manager	*audio;
	int				source_index;
	mpg123_handle	*mh;
	int				result;

	(void)delay_in_seconds;
	audio = game->audio;
	source_index = find_and_prepare_source(game, filename);
	if (source_index == -1)
		return (-1);
	mh = initialize_mpg123(filename, NULL, NULL, NULL);
	if (!mh)
		return (-1);
	result = process_audio_data(mh, audio, source_index, filename);
	cleanup_mpg123(mh);
	return (result);
}

int	stop_audio_file(t_game *game, const char *filename)
{
	t_audio_manager	*audio;
	int				i;

	audio = game->audio;
	i = 0;
	while (i < MAX_SOURCES)
	{
		if (strcmp(audio->playing_tracks[i].filename, filename) == 0)
		{
			alSourceStop(audio->sources[audio->playing_tracks[i].source_index]);
			audio->playing_tracks[i].filename[0] = '\0';
			return (0);
		}
		i++;
	}
	printf("stop_audio_file: Audio  %s not found or not playing\n", filename);
	return (-1);
}
