/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_bonus00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/11 13:44:40 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 13:44:40 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	check_texture_loaded(t_texture *texture)
{
	if (texture->img == NULL)
	{
		printf("🚨 Error: land texture not loaded\n");
	}
}

void	render_frame(t_game *game, t_texture *opening_texture)
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
void	check_last_frame(t_game *game, int frame_to_render)
{
	if (frame_to_render == MAX_LAND_TEXTURES - 1)
	{
		game->game_sequence = 3;
		game->current_frame = 0;
		game->player->is_dead = 0;
		game->player->hp = MAX_HEALTH;
		play_land_voice(game);
	}
}

void	render_land(t_game *game)
{
	int frame_to_render;
	t_texture *land_texture;

	frame_to_render = get_current_frame(&game->opening_start_time);
	land_texture = &game->land_texture[frame_to_render];
	check_texture_loaded(land_texture);
	render_frame(game, land_texture);
	game->current_frame = frame_to_render;
	check_last_frame(game, frame_to_render);
}
