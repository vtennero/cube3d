/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qol_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:34:44 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 16:29:33 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	increment_and_update(t_game *game, \
int *current_task, int total_tasks, const char *task_name)
{
	(*current_task)++;
	upd_prog_bar(game, *current_task, total_tasks, task_name);
}

void	clear_previous_output(int last_printed_length)
{
	int	i;

	printf("\r");
	i = 0;
	while (i < last_printed_length)
	{
		printf(" ");
		i++;
	}
	printf("\r");
}

int	print_task_name(const char *task_name)
{
	int	task_name_length;

	task_name_length = ft_strlen(task_name);
	if (task_name_length > MAX_TASK_NAME_LENGTH)
		task_name_length = MAX_TASK_NAME_LENGTH;
	return (printf("%-*.*s", TOTAL_PREFIX_LENGTH, task_name_length, task_name));
}

int	print_progress_bar(int bar_width)
{
	int	printed_length;
	int	i;

	printed_length = printf("[");
	i = 0;
	while (i < PROGRESS_BAR_WIDTH)
	{
		if (i < bar_width)
			printed_length += printf("#");
		else
			printed_length += printf(" ");
		i++;
	}
	printed_length += printf("]");
	return (printed_length);
}

void	upd_prog_bar(t_game *game, \
int current, int total, const char *task_name)
{
	float	progress;
	int		bar_width;
	int		printed_length;

	progress = (float)current / total;
	bar_width = (int)(progress * PROGRESS_BAR_WIDTH);
	printed_length = 0;
	clear_previous_output(game->loading);
	printed_length += print_task_name(task_name);
	printed_length += print_progress_bar(bar_width);
	printed_length += printf(" %.1f%%", progress * 100.0f);
	if (current == total)
		printf("\n");
	game->loading = printed_length;
}
