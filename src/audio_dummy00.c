/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_dummy00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:41:16 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 17:41:16 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	initialize_audio(t_game *game)
{
	printf("initialize_audio: Audio is deactivated in this configuration. \
Run helldivers3d to play with audio.\n");
	(void)game;
	return (0);
}

void	cleanup_audio(t_game *game)
{
	printf("cleanup_audio: Audio is deactivated in this configuration. \
Run helldivers3d to play with audio.\n");
	(void)game;
}

int	stop_audio_file(t_game *game, const char *filename)
{
	printf("stop_audio_file: Audio is deactivated in this configuration. \
Run helldivers3d to play with audio.\n");
	(void)game;
	(void)filename;
	return (0);
}

int	play_audio_file(t_game *game, const char *filename, float delayInSeconds)
{
	printf("play_audio_file: Audio is deactivated in this configuration. \
Run helldivers3d to play with audio. Attempted to play file %s\n",
		filename);
	(void)delayInSeconds;
	(void)game;
	return (0);
}
