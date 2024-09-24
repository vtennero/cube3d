/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_audio_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:43:33 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:15:35 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_AUDIO_BONUS_H
# define CUBE3D_AUDIO_BONUS_H

# include <AL/al.h>
# include <AL/alc.h>
# include <mpg123.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_SOURCES 50

typedef struct s_audio_track
{
	char	filename[256];
	int		source_index;
}				t_audio_track;

typedef struct s_audio_manager
{
	ALCdevice		*device;
	ALCcontext		*context;
	ALuint			sources[MAX_SOURCES];
	int				source_count;
	struct timeval	last_play_time[MAX_SOURCES];
	t_audio_track	playing_tracks[MAX_SOURCES];
}				t_audio_manager;

typedef struct s_audio_format
{
	long	rate;
	int		channels;
	int		encoding;
}			t_audio_format;

// FUNCTION DECLARATIONS START
ALuint			create_al_buffer(const char *total_buffer, size_t total_size,
					int channels, long rate);
char			*decode_mp3(mpg123_handle *mh, size_t *total_size);
int				allocate_audio_manager(t_game *game);
int				find_and_prepare_source(t_game *game, const char *filename);
int				find_available_source(t_game *game);
int				initialize_audio(t_game *game);
int				initialize_openal(t_audio_manager *audio);
int				play_audio_file(t_game *game, const char *filename,
					float delay_in_seconds);
int				process_audio_data(mpg123_handle *mh, t_audio_manager *audio,
					int source_index, const char *filename);
int				stop_audio_file(t_game *game, const char *filename);
mpg123_handle	*initialize_mpg123(const char *filename, long *rate,
					int *channels, int *encoding);
void			cleanup_audio(t_game *game);
void			cleanup_audio_context(t_audio_manager *audio);
void			cleanup_audio_device(t_audio_manager *audio);
void			cleanup_audio_sources(t_audio_manager *audio);
void			cleanup_mpg123(mpg123_handle *mh);
void			initialize_sources(t_audio_manager *audio);
void			play_and_record_audio(t_audio_manager *audio, int source_index,
					ALuint buffer, const char *filename);

// FUNCTION DECLARATIONS END

#endif
