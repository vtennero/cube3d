<<<<<<< HEAD:src/audio_dummy.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_dummy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:39:22 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/29 10:42:28 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int initializeAudio()
{
	printf("non audio mode on\n");
	return(0);
}

void cleanupAudio()
{
	printf("non audio mode on\n");
}


int findAvailableSource()
{
	printf("non audio mode on\n");
	return(0);
}
int stopAudioFile(const char* filename)
{

	printf("non audio mode on\n");
	(void)filename;
	return(0);
}

int playAudioFileWithDelay(const char* filename, float delayInSeconds)
{
	printf("non audio mode on: play file %s\n", filename);
	(void)delayInSeconds;
	return(0);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_non_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:39:22 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/27 11:45:35 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int initializeAudio()
{
	printf("non audio mode on\n");
	return(0);
}

void cleanupAudio()
{
	printf("non audio mode on\n");
}


int findAvailableSource()
{
	printf("non audio mode on\n");
	return(0);
}
int stopAudioFile(const char* filename)
{

	printf("non audio mode on\n");
	(void)filename;
	return(0);
}


int playAudioFileWithDelay(const char* filename, float delayInSeconds)
{
	printf("non audio mode on\n");
	(void)filename;
	(void)delayInSeconds;
	return(0);
}
>>>>>>> b3745960b840479a0ad853e0062fb51c570bc817:src/audio_non_bonus.c
