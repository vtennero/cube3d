/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_bonus02.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:01:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/20 17:04:13 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void init_script_manager(t_game *game) {
	game->script_manager = (t_script_manager){0};
}

void add_script(t_game *game, ScriptFunction func, int delay_seconds)
{
	if (is_script_limit_reached(game)) {
		printf("Error: Maximum number of active scripts reached\n");
		return;
	}

	struct timeval now;
	gettimeofday(&now, NULL);

	int slot = find_available_slot(game);
	t_script new_script = create_new_script(func, &now, delay_seconds);

	add_script_to_manager(game, &new_script, slot);
}

int is_script_limit_reached(t_game *game)
{
	return game->script_manager.active_script_count >= MAX_SCRIPTS;
}

int find_available_slot(t_game *game)
{
	for (int i = 0; i < game->script_manager.script_count; i++) {
		if (!game->script_manager.scripts[i].is_active) {
			return i;
		}
	}
	return game->script_manager.script_count++;
}

t_script create_new_script(ScriptFunction func, struct timeval *now, int delay_seconds)
{
	t_script new_script = {
		.trigger_time = {
			.tv_sec = now->tv_sec + delay_seconds,
			.tv_usec = now->tv_usec
		},
		.func = func,
		.is_active = 1
	};
	return new_script;
}

void add_script_to_manager(t_game *game, t_script *new_script, int slot)
{
	game->script_manager.scripts[slot] = *new_script;
	game->script_manager.active_script_count++;
}

void update_scripts(t_game *game)
{
	struct timeval now;
	gettimeofday(&now, NULL);

	for (int i = 0; i < game->script_manager.script_count; i++) {
		t_script *script = &game->script_manager.scripts[i];
		if (script->is_active &&
			(now.tv_sec > script->trigger_time.tv_sec ||
			(now.tv_sec == script->trigger_time.tv_sec && now.tv_usec >= script->trigger_time.tv_usec))) {
			script->func(game);
			script->is_active = 0;
			game->script_manager.active_script_count--;
		}
	}
}
