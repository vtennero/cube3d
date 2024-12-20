/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_bonus00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:50:11 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 17:50:11 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_key_enter(t_game *game)
{
	game->key_state[K_ENTER] = 1;
	if (game->game_sequence == 0)
	{
		reset_game_start_time(game);
		stop_audio_file(game, "audio/menu02.mp3");
		play_audio_file(game, "audio/drop02.mp3", 0);
	}
	game->change_seq = 1;
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
