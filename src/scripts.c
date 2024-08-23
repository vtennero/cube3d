/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:55:21 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/23 18:36:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void    get_hit(t_game *game)
{
    if (game->player->hp)
        game->player->hp--;
    game->player->is_hit = 0;
}

void    menu_background(t_game *game)
{
    if (game->game_sequence == 0)
        playAudioFileWithDelay("audio/menu02.mp3", 2);
}

void    menu_background_voice(t_game *game)
{
    if (game->game_sequence == 0)
        playAudioFileWithDelay("audio/menu03.mp3", 2);
}

void    sample_acquired(t_game *game)
{
    playAudioFileWithDelay("audio/raresampleacquired.mp3", 2);
    (void)game;
}

void trigger_extract_victory(t_game *game)
{
    playAudioFileWithDelay("audio/extract05.mp3", 0);
    (void)game;
}

void trigger_extract_music(t_game *game)
{
    playAudioFileWithDelay("audio/extractmusic00.mp3", 0);
    (void)game;
}

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
    playAudioFileWithDelay("audio/pelican00.mp3", 0);

    // play this is pelican one mp3
    // stopAudioFile("audio/menu.mp3");
    
}

// sucks
// void play_gun_sound(t_game *game)
// {
//     // stopAudioFile("audio/gun01.mp3");
//     playAudioFileWithDelay("audio/gun01.mp3", 0);
//     (void)game;
// }

void play_gun_sound(t_game *game) {
    playAudioFileWithDelay("audio/gun01.mp3", 0);
    // If we're still shooting, schedule the next sound
    if (game->is_shooting) {
        add_script(game, play_gun_sound, 1); // 0 second delay for continuous fire
    }
}

void    trigger_gunshots(t_game *game)
{
    if (game->is_shooting)
        add_script(game, play_gun_sound, 3);
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

