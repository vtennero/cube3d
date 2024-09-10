/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:15:36 by toto              #+#    #+#             */
/*   Updated: 2024/08/21 11:49:18 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


#define FIRST_LOOP_START 0
#define SECOND_LOOP_START 135
#define SECOND_LOOP_REPETITIONS 40


// Helper functions remain the same
void print_frame_info(int frame_to_render)
{
    printf("render opening frame to render %d\n", frame_to_render);
}

void check_texture_loaded(t_texture *opening_texture)
{
    if (opening_texture->img == NULL)
    {
        printf("Error: Opening texture not loaded\n");
        exit(1);  // or handle the error appropriately
    }
}

void render_frame(t_game *game, t_texture *opening_texture)
{
    for (int y = 0; y < game->screen_height; y++)
    {
        for (int x = 0; x < game->screen_width; x++)
        {
            int tex_x = x * opening_texture->width / game->screen_width;
            int tex_y = y * opening_texture->height / game->screen_height;
            int color = get_texture_color(opening_texture, tex_x, tex_y);
            img_pix_put(&game->img, x, y, color);
        }
    }
}

void render_opening(t_game *game)
{
    static int current_loop = 0;
    static int second_loop_count = 0;
    static int randomized_frames[MAX_OPENING_TEXTURES - SECOND_LOOP_START];
    static int randomized_frames_initialized = 0;
    int frame_to_render;

    if (current_loop == 0)
    {
        // First loop: 0 to MAX_OPENING_TEXTURES
        frame_to_render = get_current_frame(&game->opening_start_time);
        
        if (frame_to_render == 5)
            playAudioFileWithDelay("audio/drop01.mp3", 3);
        if (frame_to_render == 30)
            playAudioFileWithDelay("audio/drop03.mp3", 10);
        if (frame_to_render >= MAX_OPENING_TEXTURES - 1)
        {
            // First loop complete, start second loop
            current_loop = 1;
            second_loop_count = 0;
            reset_game_start_time(game);
            
            // Initialize randomized frames array if not done already
            if (!randomized_frames_initialized)
            {
                for (int i = 0; i < MAX_OPENING_TEXTURES - SECOND_LOOP_START; i++)
                {
                    randomized_frames[i] = SECOND_LOOP_START + i;
                }
                
                // Fisher-Yates shuffle
                for (int i = MAX_OPENING_TEXTURES - SECOND_LOOP_START - 1; i > 0; i--)
                {
                    int j = random_int(game, i + 1);
                    int temp = randomized_frames[i];
                    randomized_frames[i] = randomized_frames[j];
                    randomized_frames[j] = temp;
                }
                
                randomized_frames_initialized = 1;
            }
            
            frame_to_render = randomized_frames[0];
        }
    }
    else
    {
        // Second loop: randomized frames from SECOND_LOOP_START to MAX_OPENING_TEXTURES
        int elapsed_frames = get_current_frame(&game->opening_start_time);
        frame_to_render = randomized_frames[elapsed_frames % (MAX_OPENING_TEXTURES - SECOND_LOOP_START)];
        
        if (elapsed_frames >= MAX_OPENING_TEXTURES - SECOND_LOOP_START)
        {
            // One iteration of second loop complete
            second_loop_count++;
            if (second_loop_count >= SECOND_LOOP_REPETITIONS)
            {
                // All repetitions complete, move to next game sequence
                game->game_sequence = 2;
                current_loop = 0;
                second_loop_count = 0;
                randomized_frames_initialized = 0; // Reset for next time
                return;
            }
            else
            {
                // Start next repetition of second loop
                reset_game_start_time(game);
            }
        }
    }

    // Render the frame
    // print_frame_info(frame_to_render);
    t_texture *opening_texture = &game->opening_texture[frame_to_render];
    check_texture_loaded(opening_texture);
    render_frame(game, opening_texture);
    
    // Update current frame
    game->current_frame = frame_to_render;
}
