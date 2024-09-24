/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_bonus03.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:08:01 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:38:12 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	add_script_to_manager(t_game *game, t_script *new_script, int slot)
{
	game->script_manager.scripts[slot] = *new_script;
	game->script_manager.active_script_count++;
}

void	update_scripts(t_game *game)
{
	struct timeval	now;
	t_script		*script;
	int				i;

	gettimeofday(&now, NULL);
	i = 0;
	while (i < game->script_manager.script_count)
	{
		script = &game->script_manager.scripts[i];
		if (script->is_active \
		&& (now.tv_sec > script->trigger_time.tv_sec \
		|| (now.tv_sec == script->trigger_time.tv_sec \
		&& now.tv_usec >= script->trigger_time.tv_usec)))
		{
			script->func(game);
			script->is_active = 0;
			game->script_manager.active_script_count--;
		}
		i++;
	}
}
