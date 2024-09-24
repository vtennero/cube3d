/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_bonus02.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:01:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:38:13 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_script_manager(t_game *game)
{
	game->script_manager = (t_script_manager){0};
}

void	add_script(t_game *game, script_func func, int delay_seconds)
{
	struct timeval	now;
	int				slot;
	t_script		new_script;

	if (is_script_limit_reached(game))
	{
		printf("Error: Maximum number of active scripts reached\n");
		return ;
	}
	gettimeofday(&now, NULL);
	slot = find_available_slot(game);
	new_script = create_new_script(func, &now, delay_seconds);
	add_script_to_manager(game, &new_script, slot);
}

int	is_script_limit_reached(t_game *game)
{
	return (game->script_manager.active_script_count >= MAX_SCRIPTS);
}

int	find_available_slot(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->script_manager.script_count)
	{
		if (!game->script_manager.scripts[i].is_active)
			return (i);
		i++;
	}
	return (game->script_manager.script_count++);
}

t_script	create_new_script(script_func func, \
struct timeval *now, int delay_seconds)
{
	t_script	new_script;

	new_script.trigger_time.tv_sec = now->tv_sec + delay_seconds;
	new_script.trigger_time.tv_usec = now->tv_usec;
	new_script.func = func;
	new_script.is_active = 1;
	return (new_script);
}
