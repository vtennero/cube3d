/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ui_bonus01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:50:22 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:26:51 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_left_crosshair(t_game *game, t_vector2d center)
{
	t_vector2d	left_start;
	t_vector2d	left_end;

	left_start.x = center.x - CROSSHAIR_SIZE / 2;
	left_start.y = center.y - CROSSHAIR_THICKNESS / 2;
	left_end.x = center.x - CROSSHAIR_GAP / 2;
	left_end.y = center.y + CROSSHAIR_THICKNESS / 2;
	draw_crosshair_line(game, left_start, left_end);
}

void	draw_right_crosshair(t_game *game, t_vector2d center)
{
	t_vector2d	right_start;
	t_vector2d	right_end;

	right_start.x = center.x + CROSSHAIR_GAP / 2;
	right_start.y = center.y - CROSSHAIR_THICKNESS / 2;
	right_end.x = center.x + CROSSHAIR_SIZE / 2;
	right_end.y = center.y + CROSSHAIR_THICKNESS / 2;
	draw_crosshair_line(game, right_start, right_end);
}

void	draw_top_crosshair(t_game *game, t_vector2d center)
{
	t_vector2d	top_start;
	t_vector2d	top_end;

	top_start.x = center.x - CROSSHAIR_THICKNESS / 2;
	top_start.y = center.y - CROSSHAIR_SIZE / 2;
	top_end.x = center.x + CROSSHAIR_THICKNESS / 2;
	top_end.y = center.y - CROSSHAIR_GAP / 2;
	draw_crosshair_line(game, top_start, top_end);
}

void	draw_bottom_crosshair(t_game *game, t_vector2d center)
{
	t_vector2d	bottom_start;
	t_vector2d	bottom_end;

	bottom_start.x = center.x - CROSSHAIR_THICKNESS / 2;
	bottom_start.y = center.y + CROSSHAIR_GAP / 2;
	bottom_end.x = center.x + CROSSHAIR_THICKNESS / 2;
	bottom_end.y = center.y + CROSSHAIR_SIZE / 2;
	draw_crosshair_line(game, bottom_start, bottom_end);
}

void	render_crosshair(t_game *game)
{
	t_vector2d	center;

	center = game->crosshair;
	draw_left_crosshair(game, center);
	draw_right_crosshair(game, center);
	draw_top_crosshair(game, center);
	draw_bottom_crosshair(game, center);
	draw_dot(game, center);
}
