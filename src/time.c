/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:41:09 by toto              #+#    #+#             */
/*   Updated: 2024/08/23 14:48:45 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void    reset_game_start_time(t_game *game)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    game->opening_start_time = current_time;
}

long get_elapsed_microseconds(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) * 1000000 + (end->tv_usec - start->tv_usec);
}

int get_current_frame(struct timeval *start_time)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    long elapsed_microseconds = get_elapsed_microseconds(start_time, &current_time);
    int current_frame = (int)(elapsed_microseconds / MICROSECONDS_PER_FRAME);

    return (current_frame < MAX_OPENING_TEXTURES) ? current_frame : MAX_OPENING_TEXTURES - 1;
}

// int get_current_frame_outro(struct timeval *start_time)
// {
//     struct timeval current_time;
//     gettimeofday(&current_time, NULL);

//     long elapsed_microseconds = get_elapsed_microseconds(start_time, &current_time);
//     int current_frame = (int)(elapsed_microseconds / MICROSECONDS_PER_FRAME);

//     return (current_frame < MAX_OUTRO_TEXTURES) ? current_frame : MAX_OUTRO_TEXTURES - 1;
// }

int get_current_frame_outro(struct timeval *start_time)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    long elapsed_microseconds = get_elapsed_microseconds(start_time, &current_time);
    int current_frame = (int)(elapsed_microseconds / MICROSECONDS_PER_FRAME);

    return (current_frame < MAX_OUTRO_TEXTURES) ? current_frame : MAX_OUTRO_TEXTURES - 1;
}