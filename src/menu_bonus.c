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
	game->key_state[K_ENTER] = 1;
	// printf("handle_key_enter: game->game_sequence = %d\n", game->game_sequence);
	if (game->game_sequence == 0)
	{
		reset_game_start_time(game);
		stopAudioFile("audio/menu02.mp3");
		playAudioFileWithDelay("audio/drop02.mp3", 0);
	}
	// if (game->game_sequence < 3)
		game->change_seq = 1;
		// game->game_sequence++;
}

void	render_menu(t_game *game)
{
	int	x;
	int	y;
	int	color;
	int	tex_x;
	int	tex_y;

	if (game->menu_texture[0].img == NULL)
	{
		printf("Error: Menu texture not loaded\n");
		return ;
	}
	y = 0;
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			tex_x = x * game->menu_texture[0].width / game->screen_width;
			tex_y = y * game->menu_texture[0].height / game->screen_height;
			color = get_texture_color(&game->menu_texture[0], tex_x, tex_y);
			img_pix_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

