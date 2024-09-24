/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_bonus02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:44:14 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:17:54 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d_audio_bonus.h"

mpg123_handle	*initialize_mpg123(const char *filename, long *rate,
						int *channels, int *encoding)
{
	mpg123_handle	*mh;

	mh = mpg123_new(NULL, NULL);
	mpg123_open(mh, filename);
	mpg123_getformat(mh, rate, channels, encoding);
	return (mh);
}

char	*decode_mp3(mpg123_handle *mh, size_t *total_size)
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
		ft_memcpy(total_buffer + *total_size, buffer_data, done);
		*total_size += done;
	}
	free(buffer_data);
	return (total_buffer);
}

ALuint	create_al_buffer(const char *total_buffer, size_t total_size,
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

void	cleanup_mpg123(mpg123_handle *mh)
{
	mpg123_close(mh);
	mpg123_delete(mh);
}

int	process_audio_data(mpg123_handle *mh, t_audio_manager *audio,
				int source_index, const char *filename)
{
	size_t			total_size;
	char			*total_buffer;
	t_audio_format	format;
	ALuint			buffer;

	total_buffer = decode_mp3(mh, &total_size);
	if (!total_buffer)
	{
		cleanup_mpg123(mh);
		return (-1);
	}
	mpg123_getformat(mh, &format.rate, &format.channels, &format.encoding);
	buffer = create_al_buffer(total_buffer, total_size, \
	format.channels, format.rate);
	play_and_record_audio(audio, source_index, buffer, filename);
	free(total_buffer);
	return (0);
}
