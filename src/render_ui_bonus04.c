/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_bonus04.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:25:47 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:26:58 by vitenner         ###   ########.fr       */
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
	int	color;
	int	x;
	int	y;

	color = 0xFFFFFF;
	x = bar->pos.x;
	while (x < bar->pos.x + bar->width)
	{
		y = 0;
		while (y < HEALTH_BAR_BORDER)
		{
			img_pix_put(&game->img, x, bar->pos.y + y, color);
			img_pix_put(&game->img, x, bar->pos.y + bar->height - 1 - y, color);
			y++;
		}
		x++;
	}
}

void	draw_health_bar_leftright(t_game *game, t_health_bar *bar)
{
	int	color;
	int	y;
	int	x;

	color = 0xFFFFFF;
	y = bar->pos.y;
	while (y < bar->pos.y + bar->height)
	{
		x = 0;
		while (x < HEALTH_BAR_BORDER)
		{
			img_pix_put(&game->img, bar->pos.x + x, y, color);
			img_pix_put(&game->img, bar->pos.x + bar->width - 1 - x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_health_bar_border(t_game *game, t_health_bar *bar)
{
	draw_health_bar_topbottom(game, bar);
	draw_health_bar_leftright(game, bar);
}

void	draw_health_bar_fill(t_game *game, t_health_bar *bar)
{
	int	fill_width;
	int	color;
	int	y;
	int	x;

	color = 0x00FF00;
	fill_width = (game->player->hp * (bar->width - 2 * HEALTH_BAR_BORDER))
		/ MAX_HEALTH;
	y = bar->pos.y + HEALTH_BAR_BORDER;
	while (y < bar->pos.y + bar->height - HEALTH_BAR_BORDER)
	{
		x = bar->pos.x + HEALTH_BAR_BORDER;
		while (x < bar->pos.x + HEALTH_BAR_BORDER + fill_width)
		{
			img_pix_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}
