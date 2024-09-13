/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outro_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:10:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/10 11:10:39 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_outro(t_game *game)
{
	int			frame_to_render;
	t_texture	*outro_texture;
	t_vector2d	screen;
	t_vector2d	tex;
	int			color;

	frame_to_render = get_current_frame_outro(&game->opening_start_time);
	outro_texture = &game->outro_texture[frame_to_render];
	if (outro_texture->img == NULL)
	{
		printf("Error: outro texture not loaded\n");
		return ;
	}
	screen.y = 0;
	while (screen.y < game->screen_height)
	{
		screen.x = 0;
		while (screen.x < game->screen_width)
		{
			tex.x = screen.x * outro_texture->width / game->screen_width;
			tex.y = screen.y * outro_texture->height / game->screen_height;
			color = get_texture_color(outro_texture, tex.x, tex.y);
			img_pix_put(&game->img, screen.x, screen.y, color);
			screen.x++;
		}
		screen.y++;
	}
	game->current_frame = frame_to_render;
	if (frame_to_render == MAX_OUTRO_TEXTURES - 1)
		return ;
}
