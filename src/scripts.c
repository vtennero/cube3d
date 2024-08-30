/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:55:21 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/27 12:16:16 by vitenner         ###   ########.fr       */
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
void trigger_prelanding(t_game *game)
{
    playAudioFileWithDelay("audio/eta.mp3", 0);
}
void extraction_available(t_game *game)
{
    playAudioFileWithDelay("audio/extractionready.mp3", 0);
}


void play_gun_sound(t_game *game) {
    playAudioFileWithDelay("audio/gun02.mp3", 0);
    // If we're still shooting, schedule the next sound
    if (game->is_shooting) {
        add_script(game, play_gun_sound, 0); // 0 second delay for continuous fire
    }
}

void    trigger_supply_take(t_game *game)
{
    game->player->taking_supplies = 1;
    // crazy mode 
	// game->player->direction.x = 0.2f;
}

void    cancel_supply_take(t_game *game)
{
    game->player->taking_supplies = 0;
    // crazy mode 
	// game->player->direction.x = -1.0f;

}

void    trigger_gunshots(t_game *game)
{
    if (game->is_shooting)
        add_script(game, play_gun_sound, 3);
}

// void    eagle_voice_post_strike(t_game *game)
// {
//     playAudioFileWithDelay("audio/eagle")
// }

void play_random_eagle_call(t_game *game)
{
    // Generate a random number between 0 and 5
    int random_call = random_int(game, 6);
    
    // Create the audio file name based on the random number
    char audio_file[] = "audio/eaglec00.mp3";
    audio_file[12] = '0' + random_call / 10;
    audio_file[13] = '0' + random_call % 10;
    
    // Play the selected audio file with no delay
    playAudioFileWithDelay(audio_file, 0);
}

void    eagle_bombs(t_game *game)
{
    // playAudioFileWithDelay("audio/eaglec00.mp3", 0);
    play_random_eagle_call(game);
    game->strike->is_active = 1;
    (void)game;
}

void    eagle_inbound(t_game *game)
{
    game->strike->is_launching = 0;

    // play audio, choose audio
    add_script(game, eagle_bombs, 1);
    playAudioFileWithDelay("audio/eagles00.mp3", 0);


    // eaglesgtrikes--
}

void init_script_manager(t_game *game) {
    game->script_manager = (t_script_manager){0};
}

// void add_script(t_game *game, ScriptFunction func, int delay_seconds) {
//     if (game->script_manager.script_count >= MAX_SCRIPTS) {
//         printf("Error: Maximum number of scripts reached\n");
//         return;
//     }

//     struct timeval now;
//     gettimeofday(&now, NULL);

//     t_script new_script = {
//         .trigger_time = {
//             .tv_sec = now.tv_sec + delay_seconds,
//             .tv_usec = now.tv_usec
//         },
//         .func = func,
//         .is_active = 1
//     };

//     game->script_manager.scripts[game->script_manager.script_count++] = new_script;
// }

// void update_scripts(t_game *game) {
//     struct timeval now;
//     gettimeofday(&now, NULL);

//     for (int i = 0; i < game->script_manager.script_count; i++) {
//         t_script *script = &game->script_manager.scripts[i];
//         if (script->is_active && 
//             (now.tv_sec > script->trigger_time.tv_sec || 
//             (now.tv_sec == script->trigger_time.tv_sec && now.tv_usec >= script->trigger_time.tv_usec))) {
//             script->func(game);
//             script->is_active = 0;
//         }
//     }
// }


void add_script(t_game *game, ScriptFunction func, int delay_seconds) {
    if (game->script_manager.active_script_count >= MAX_SCRIPTS) {
        printf("Error: Maximum number of active scripts reached\n");
        return;
    }

    struct timeval now;
    gettimeofday(&now, NULL);

    // Find an inactive slot or use the next available slot
    int slot = -1;
    for (int i = 0; i < game->script_manager.script_count; i++) {
        if (!game->script_manager.scripts[i].is_active) {
            slot = i;
            break;
        }
    }
    if (slot == -1) {
        slot = game->script_manager.script_count++;
    }

    t_script new_script = {
        .trigger_time = {
            .tv_sec = now.tv_sec + delay_seconds,
            .tv_usec = now.tv_usec
        },
        .func = func,
        .is_active = 1
    };

    game->script_manager.scripts[slot] = new_script;
    game->script_manager.active_script_count++;
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
            game->script_manager.active_script_count--;
        }
    }
}