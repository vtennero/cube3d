/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_bonus01.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:01:00 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 16:59:56 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	reset_game_start_time(t_game *game)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	game->opening_start_time = current_time;
}

long	get_elapsed_microseconds(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) * 1000000 \
	+ (end->tv_usec - start->tv_usec));
}

int	calculate_frame(long elapsed_microseconds, int max_textures)
{
	int	current_frame;

	current_frame = (int)(elapsed_microseconds / MICROSECONDS_PER_FRAME);
	if (current_frame < max_textures)
	{
		return (current_frame);
	}
	else
	{
		return (max_textures - 1);
	}
}

int	get_current_frame(struct timeval *start_time)
{
	struct timeval	current_time;
	long			elapsed_microseconds;

	gettimeofday(&current_time, NULL);
	elapsed_microseconds = get_elapsed_microseconds(start_time, &current_time);
	return (calculate_frame(elapsed_microseconds, T_N_INTRO1));
}
