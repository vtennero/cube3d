/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_bonus02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:50:29 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:26:47 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	set_crosshair_position(t_game *game)
{
	float	center_x;
	float	center_y;

	center_x = (float)game->screen_width / 2.0f;
	center_y = (float)game->screen_height / 2.0f;
	game->crosshair.x = center_x;
	game->crosshair.y = center_y;
}

void	draw_crosshair_line(t_game *game, t_vector2d start, t_vector2d end)
{
	int	x;
	int	y;

	x = start.x;
	while (x <= end.x)
	{
		y = start.y;
		while (y <= end.y)
		{
			img_pix_put(&game->img, x, y, CROSSHAIR_COLOR);
			y++;
		}
		x++;
	}
}

void	draw_dot(t_game *game, t_vector2d center)
{
	int	x;
	int	y;

	y = center.y - DOT_RADIUS;
	while (y <= center.y + DOT_RADIUS)
	{
		x = center.x - DOT_RADIUS;
		while (x <= center.x + DOT_RADIUS)
		{
			if ((x - center.x) * (x - center.x) + (y - center.y) * (y
					- center.y) <= DOT_RADIUS * DOT_RADIUS)
			{
				img_pix_put(&game->img, x, y, CROSSHAIR_COLOR);
			}
			x++;
		}
		y++;
	}
}
