/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:55:21 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/22 17:16:21 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void testscript(t_game *game)
{
    printf("This is a test\n");
	(void)game;
}

void trigger_landing(t_game *game)
{
    game->extract[0].is_landing = 1;
    game->extract[0].is_activated = 0;
    printf("landing sequence initiated\n");
    // play this is pelican one mp3
    // stopAudioFile("audio/menu.mp3");
    
}

void init_script_manager(t_game *game) {
    game->script_manager = (t_script_manager){0};
}

void add_script(t_game *game, ScriptFunction func, int delay_seconds) {
    if (game->script_manager.script_count >= MAX_SCRIPTS) {
        printf("Error: Maximum number of scripts reached\n");
        return;
    }

    struct timeval now;
    gettimeofday(&now, NULL);

    t_script new_script = {
        .trigger_time = {
            .tv_sec = now.tv_sec + delay_seconds,
            .tv_usec = now.tv_usec
        },
        .func = func,
        .is_active = 1
    };

    game->script_manager.scripts[game->script_manager.script_count++] = new_script;
}

void update_scripts(t_game *game) {
    struct timeval now;
    gettimeofday(&now, NULL);

    for (int i = 0; i < game->script_manager.script_count; i++) {
        t_script *script = &game->script_manager.scripts[i];
        if (script->is_active && 
            (now.tv_sec > script->trigger_time.tv_sec || 
            (now.tv_sec == script->trigger_time.tv_sec && now.tv_usec >= script->trigger_time.tv_usec))) {
            script->func(game);
            script->is_active = 0;
        }
    }
}

