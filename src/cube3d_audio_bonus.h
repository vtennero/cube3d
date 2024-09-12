/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_audio_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:43:33 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/12 13:53:27 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUBE3D_AUDIO_BONUS_H
# define CUBE3D_AUDIO_BONUS_H

#include <AL/al.h>
#include <AL/alc.h>
#include <mpg123.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SOURCES 50


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


#endif
