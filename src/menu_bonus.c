/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:15:38 by toto              #+#    #+#             */
/*   Updated: 2024/08/22 17:06:47 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void handle_key_enter(t_game *game)
{
    if (game->key_state[K_ENTER] == 1)
    {
        if (game->game_sequence == 0)
        {
            reset_game_start_time(game);
            stopAudioFile("audio/menu02.mp3");
            playAudioFileWithDelay("audio/drop02.mp3", 0);
        }
        if (game->game_sequence < 3)
            game->game_sequence++;
    }
}

void render_menu(t_game *game)
{
    t_texture *menu_texture = &game->menu_texture[0];
    int x, y;
    int color;

    if (menu_texture->img == NULL)
    {
        printf("Error: Menu texture not loaded\n");
        return;
    }

    // printf("Menu texture dimensions: %dx%d\n", menu_texture->width, menu_texture->height);  // Debug print
    // printf("game->screen_width game->screen_height %dx%d\n", game->screen_width, game->screen_height);  // Debug print

    for (y = 0; y < game->screen_height; y++)
    {
		// printf("y loop\n");
        for (x = 0; x < game->screen_width; x++)
        {
			// printf("x loop\n");
            int tex_x = x * menu_texture->width / game->screen_width;
            int tex_y = y * menu_texture->height / game->screen_height;
            color = get_texture_color(menu_texture, tex_x, tex_y);
            // if (x == 0 && y == 0)
            //     printf("First pixel color: 0x%X\n", color);  // Debug print
            img_pix_put(&game->img, x, y, color);
        }
    }
}