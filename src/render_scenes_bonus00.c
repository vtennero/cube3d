/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scenes_bonus00.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:57:42 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 17:57:42 by vitenner         ###   ########.fr       */
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
	int	y;
	int	x;
	int	tex_x;
	int	tex_y;
	int	color;

	y = 0;
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			tex_x = x * opening_texture->width / game->screen_width;
			tex_y = y * opening_texture->height / game->screen_height;
			color = get_texture_color(opening_texture, tex_x, tex_y);
			img_pix_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	check_last_frame(t_game *game, int frame_to_render)
{
	if (frame_to_render == T_N_INTRO2 - 1)
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
	int			frame_to_render;
	t_texture	*land_texture;

	frame_to_render = get_current_frame(&game->opening_start_time);
	land_texture = &game->t_intro2[frame_to_render];
	check_texture_loaded(land_texture);
	render_frame(game, land_texture);
	game->current_frame = frame_to_render;
	check_last_frame(game, frame_to_render);
}
