/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:15:36 by toto              #+#    #+#             */
/*   Updated: 2024/08/19 14:01:28 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void render_opening(t_game *game)
// {
//     t_texture *opening_texture = &game->opening_texture[game->current_frame];
//     int x, y;
//     int color;

//     if (opening_texture->img == NULL)
//     {
//         printf("Error: Opening texture not loaded\n");
//         return;
//     }

//     for (y = 0; y < game->screen_height; y++)
//     {
//         for (x = 0; x < game->screen_width; x++)
//         {
//             int tex_x = x * opening_texture->width / game->screen_width;
//             int tex_y = y * opening_texture->height / game->screen_height;
//             color = get_texture_color(opening_texture, tex_x, tex_y);
//             img_pix_put(&game->img, x, y, color);
//         }
//     }

//     if (should_increment_frame(&frame_start_time))
//         game->current_frame++;

//     // If we've reached the last frame, change game sequence
//     if (game->current_frame >= MAX_OPENING_TEXTURES)
//     {
//         game->game_sequence = 2;
//         game->current_frame = 0;  // Reset frame counter for potential future use
//     }
// }

// void render_opening(t_game *game)
// {
//     int frame_to_render = get_current_frame(&game->opening_start_time);
// 	printf("render opening frame to render %d\n", frame_to_render);
//     t_texture *opening_texture = &game->opening_texture[frame_to_render];

//     if (opening_texture->img == NULL)
//     {
//         printf("Error: Opening texture not loaded\n");
//         return;
//     }

//     // Render the frame
//     for (int y = 0; y < game->screen_height; y++)
//     {
// 		// printf("rendering frame\n");
//         for (int x = 0; x < game->screen_width; x++)
//         {
//             int tex_x = x * opening_texture->width / game->screen_width;
//             int tex_y = y * opening_texture->height / game->screen_height;
//             int color = get_texture_color(opening_texture, tex_x, tex_y);
//             img_pix_put(&game->img, x, y, color);
//         }
//     }

//     // Update game state
//     game->current_frame = frame_to_render;

//     // Check if we've reached the last frame
//     if (frame_to_render == MAX_OPENING_TEXTURES - 1)
//     {
// 		// if (game->loop_count == 5)
// 		// {
// 			game->game_sequence = 2;
// 			game->current_frame = 0;
// 		// }
// 		// else
// 		// {
// 		// 	game->loop_count++;
// 		// 	// add frame number here to reset at 130
// 		// }

//     }
// }


#define FIRST_LOOP_START 0
#define SECOND_LOOP_START 135
#define SECOND_LOOP_REPETITIONS 40

// #define MAX_OPENING_TEXTURES 141



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


// void render_opening(t_game *game)
// {
//     static int current_loop = 0;
//     int frame_to_render;

//     if (current_loop == 0)
//     {
//         // First loop: 0 to MAX_OPENING_TEXTURES
//         frame_to_render = get_current_frame(&game->opening_start_time);
        
//         if (frame_to_render >= MAX_OPENING_TEXTURES - 1)
//         {
//             // First loop complete, start second loop
//             current_loop = 1;
//             reset_game_start_time(game);
//             frame_to_render = SECOND_LOOP_START;
//         }
//     }
//     else
//     {
//         // Second loop: 130 to MAX_OPENING_TEXTURES
//         int elapsed_frames = get_current_frame(&game->opening_start_time);
//         frame_to_render = SECOND_LOOP_START + elapsed_frames;
        
//         if (frame_to_render >= MAX_OPENING_TEXTURES - 1)
//         {
//             // Both loops complete, move to next game sequence
//             game->game_sequence = 2;
//             current_loop = 0;
//             return;
//         }
//     }

//     // Render the frame
//     print_frame_info(frame_to_render);
//     t_texture *opening_texture = &game->opening_texture[frame_to_render];
//     check_texture_loaded(opening_texture);
//     render_frame(game, opening_texture);
    
//     // Update current frame
//     game->current_frame = frame_to_render;
// }

void render_opening(t_game *game)
{
    static int current_loop = 0;
    static int second_loop_count = 0;
    int frame_to_render;

    if (current_loop == 0)
    {
        // First loop: 0 to MAX_OPENING_TEXTURES
        frame_to_render = get_current_frame(&game->opening_start_time);
        
		// if (frame_to_render == 5)
            // playAudioFileWithDelay("audio/drop01.mp3", 3);
		// if (frame_to_render == 30)
            // playAudioFileWithDelay("audio/drop03.mp3", 10);
        if (frame_to_render >= MAX_OPENING_TEXTURES - 1)
        {
            // First loop complete, start second loop
            current_loop = 1;
            second_loop_count = 0;
            reset_game_start_time(game);
            frame_to_render = SECOND_LOOP_START;
        }
    }
    else
    {
        // Second loop: 130 to MAX_OPENING_TEXTURES
        int elapsed_frames = get_current_frame(&game->opening_start_time);
        frame_to_render = SECOND_LOOP_START + elapsed_frames;
        
        if (frame_to_render >= MAX_OPENING_TEXTURES - 1)
        {
            // One iteration of second loop complete
            second_loop_count++;
            if (second_loop_count >= SECOND_LOOP_REPETITIONS)
            {
                // All repetitions complete, move to next game sequence
                game->game_sequence = 2;
                current_loop = 0;
                second_loop_count = 0;
                return;
            }
            else
            {
                // Start next repetition of second loop
                reset_game_start_time(game);
                frame_to_render = SECOND_LOOP_START;
            }
        }
    }

    // Render the frame
    print_frame_info(frame_to_render);
    t_texture *opening_texture = &game->opening_texture[frame_to_render];
    check_texture_loaded(opening_texture);
    render_frame(game, opening_texture);
    
    // Update current frame
    game->current_frame = frame_to_render;
}
