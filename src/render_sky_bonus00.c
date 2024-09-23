/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sky_bonus00.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:41:34 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/18 12:41:34 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_sky_pixel(t_game *game, t_vector2d pos, t_vector2d tex)
{
	int	pixel_pos;
	int	color;

	pixel_pos = tex.y * game->sky_texture.line_len + tex.x
		* (game->sky_texture.bpp / 8);
	if (pixel_pos >= 0 && pixel_pos < game->sky_texture.height
		* game->sky_texture.line_len)
	{
		color = *((int *)(game->sky_texture.data + pixel_pos));
		img_pix_put(&game->img, pos.x, pos.y, color);
	}
}

void	render_sky_line(t_sky_render *sky, int i)
{
	int			j;
	t_vector2d	pos;
	t_vector2d	tex;

	j = 0;
	while (j < sky->game->screen_width)
	{
		tex.x = calculate_tx(sky, j);
		tex.y = calculate_ty(sky, i);
		pos.x = j;
		pos.y = i;
		render_sky_pixel(sky->game, pos, tex);
		j++;
	}
}

void	render_sky(t_game *game)
{
	t_sky_render	sky;
	int				i;

	sky.game = game;
	sky.angle = calculate_angle(game);
	calculate_sky_range(&sky);
	sky.texture_reveal = calculate_texture_reveal(game);
	i = sky.sky_start;
	while (i < sky.sky_end)
	{
		render_sky_line(&sky, i);
		i++;
	}
}
