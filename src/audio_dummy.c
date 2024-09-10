/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_dummy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:39:22 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/01 14:45:11 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	initializeAudio(void)
{
	printf("non audio mode on\n");
	return (0);
}

void	cleanupAudio(void)
{
	printf("non audio mode on\n");
}

int	findAvailableSource(void)
{
	printf("non audio mode on\n");
	return (0);
}
int	stopAudioFile(const char *filename)
{
	printf("non audio mode on\n");
	(void)filename;
	return (0);
}

int	playAudioFileWithDelay(const char *filename, float delayInSeconds)
{
	printf("non audio mode on: play file %s\n", filename);
	(void)delayInSeconds;
	return (0);
}
