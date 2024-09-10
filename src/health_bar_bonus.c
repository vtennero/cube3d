/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bar_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:16:00 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/05 12:22:02 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define HEALTH_BAR_HEIGHT 20
#define HEALTH_BAR_MARGIN 10
#define HEALTH_BAR_BORDER 2

void	calculate_health_bar_dimensions(t_game *game, int *width, int *height,\
		int *start_x, int *start_y)
{
	*width = game->screen_width / 4; // 1/4 of the screen width
	*height = HEALTH_BAR_HEIGHT;
	*start_x = HEALTH_BAR_MARGIN;
	*start_y = game->screen_height - HEALTH_BAR_HEIGHT - HEALTH_BAR_MARGIN;
}

void	draw_health_bar_topbottom(t_game *game, int start_x, int start_y,\
		int width, int height)
{
	int	color;

	color = 0xFFFFFF;
	for (int x = start_x; x < start_x + width; x++)
	{
		for (int y = 0; y < HEALTH_BAR_BORDER; y++)
		{
			img_pix_put(&game->img, x, start_y + y, color);
			img_pix_put(&game->img, x, start_y + height - 1 - y, color);
		}
	}
}

void	draw_health_bar_leftright(t_game *game, int start_x, int start_y,
		int width, int height)
{
	int	color;

	color = 0xFFFFFF;
	for (int y = start_y; y < start_y + height; y++)
	{
		for (int x = 0; x < HEALTH_BAR_BORDER; x++)
		{
			img_pix_put(&game->img, start_x + x, y, color);
			img_pix_put(&game->img, start_x + width - 1 - x, y, color);
		}
	}
}

void	draw_health_bar_border(t_game *game, int start_x, int start_y,
		int width, int height)
{
	draw_health_bar_topbottom(game, start_x, start_y, width, height);
	draw_health_bar_leftright(game, start_x, start_y, width, height);
}

void	draw_health_bar_fill(t_game *game, int start_x, int start_y, int width,
		int height)
{
	int	fill_width;
	int	color;

	color = 0x00FF00;
	fill_width = (game->player->hp * (width - 2 * HEALTH_BAR_BORDER))
		/ MAX_HEALTH;
	for (int y = start_y + HEALTH_BAR_BORDER; y < start_y + height
		- HEALTH_BAR_BORDER; y++)
	{
		for (int x = start_x + HEALTH_BAR_BORDER; x < start_x
			+ HEALTH_BAR_BORDER + fill_width; x++)
		{
			img_pix_put(&game->img, x, y, color);
		}
	}
}

void	render_health_bar(t_game *game)
{
	int width, height, start_x, start_y;
	calculate_health_bar_dimensions(game, &width, &height, &start_x, &start_y);

	draw_health_bar_border(game, start_x, start_y, width, height);
	draw_health_bar_fill(game, start_x, start_y, width, height);
}