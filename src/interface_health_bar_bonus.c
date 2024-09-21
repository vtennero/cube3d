/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_health_bar_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+        +:+      */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+      +#+         */
/*                                                +#+#+#+#+#+  +#+            */
/*   Created: 2024/09/11 14:18:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 14:18:07 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calculate_health_bar_dimensions(t_game *game, t_health_bar *bar)
{
	bar->width = game->screen_width / 4;
	bar->height = HEALTH_BAR_HEIGHT;
	bar->pos.x = HEALTH_BAR_MARGIN;
	bar->pos.y = game->screen_height - HEALTH_BAR_HEIGHT - HEALTH_BAR_MARGIN;
}

void	draw_health_bar_topbottom(t_game *game, t_health_bar *bar)
{
	int color;

	color = 0xFFFFFF;
	for (int x = bar->pos.x; x < bar->pos.x + bar->width; x++)
	{
		for (int y = 0; y < HEALTH_BAR_BORDER; y++)
		{
			img_pix_put(&game->img, x, bar->pos.y + y, color);
			img_pix_put(&game->img, x, bar->pos.y + bar->height - 1 - y,
				color);
		}
	}
}

void	draw_health_bar_leftright(t_game *game, t_health_bar *bar)
{
	int color = 0xFFFFFF;

	for (int y = bar->pos.y; y < bar->pos.y + bar->height; y++)
	{
		for (int x = 0; x < HEALTH_BAR_BORDER; x++)
		{
			img_pix_put(&game->img, bar->pos.x + x, y, color);
			img_pix_put(&game->img, bar->pos.x + bar->width - 1 - x, y, color);
		}
	}
}

void	draw_health_bar_border(t_game *game, t_health_bar *bar)
{
	draw_health_bar_topbottom(game, bar);
	draw_health_bar_leftright(game, bar);
}

void	draw_health_bar_fill(t_game *game, t_health_bar *bar)
{
	int fill_width;
	int color = 0x00FF00;

	fill_width = (game->player->hp * (bar->width - 2 * HEALTH_BAR_BORDER))
		/ MAX_HEALTH;
	for (int y = bar->pos.y + HEALTH_BAR_BORDER; y < bar->pos.y + bar->height
		- HEALTH_BAR_BORDER; y++)
	{
		for (int x = bar->pos.x + HEALTH_BAR_BORDER; x < bar->pos.x
			+ HEALTH_BAR_BORDER + fill_width; x++)
		{
			img_pix_put(&game->img, x, y, color);
		}
	}
}

void	render_health_bar(t_game *game)
{
	t_health_bar bar;
	calculate_health_bar_dimensions(game, &bar);

	draw_health_bar_border(game, &bar);
	draw_health_bar_fill(game, &bar);
}
