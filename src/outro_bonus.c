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

int	get_current_frame_outro(struct timeval *start_time)
{
	struct timeval	current_time;
	long			elapsed_microseconds;

	gettimeofday(&current_time, NULL);
	elapsed_microseconds = get_elapsed_microseconds(start_time, &current_time);
	return (calculate_frame(elapsed_microseconds, MAX_OUTRO_TEXTURES));
}

void	render_pixel(t_game *game, t_texture *texture, t_vector2d screen)
{
	t_vector2d	tex;
	int			color;

	tex.x = screen.x * texture->width / game->screen_width;
	tex.y = screen.y * texture->height / game->screen_height;
	color = get_texture_color(texture, tex.x, tex.y);
	img_pix_put(&game->img, screen.x, screen.y, color);
}

void	render_texture(t_game *game, t_texture *texture)
{
	t_vector2d	screen;

	screen.y = 0;
	while (screen.y < game->screen_height)
	{
		screen.x = 0;
		while (screen.x < game->screen_width)
		{
			render_pixel(game, texture, screen);
			screen.x++;
		}
		screen.y++;
	}
}

void	render_outro(t_game *game)
{
	int			frame_to_render;
	t_texture	*outro_texture;

	frame_to_render = get_current_frame_outro(&game->opening_start_time);
	outro_texture = &game->outro_texture[frame_to_render];
	if (outro_texture->img == NULL)
		return ;
	render_texture(game, &game->outro_texture[frame_to_render]);
	game->current_frame = frame_to_render;
	if (frame_to_render == MAX_OUTRO_TEXTURES - 1)
		return ;
}
