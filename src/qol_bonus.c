/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qol_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:34:44 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/13 14:35:03 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void clear_previous_output(int last_printed_length)
{
    printf("\r");
    for (int i = 0; i < last_printed_length; i++)
        printf(" ");
    printf("\r");
}

int print_task_name(const char *task_name)
{
    int task_name_length = strlen(task_name);
    if (task_name_length > MAX_TASK_NAME_LENGTH)
        task_name_length = MAX_TASK_NAME_LENGTH;
    return printf("%-*.*s", TOTAL_PREFIX_LENGTH, task_name_length, task_name);
}

int print_progress_bar(int bar_width)
{
    int printed_length = printf("[");
    for (int i = 0; i < PROGRESS_BAR_WIDTH; i++)
    {
        if (i < bar_width)
            printed_length += printf("#");
        else
            printed_length += printf(" ");
    }
    printed_length += printf("]");
    return printed_length;
}

void update_progress_bar(t_game *game, int current, int total, const char *task_name)
{
    float progress = (float)current / total;
    int bar_width = (int)(progress * PROGRESS_BAR_WIDTH);
    int printed_length = 0;

    clear_previous_output(game->loading);

    printed_length += print_task_name(task_name);
    printed_length += print_progress_bar(bar_width);
    printed_length += printf(" %.1f%%", progress * 100.0f);

    if (current == total)
        printf("\n");

    game->loading = printed_length;
}
