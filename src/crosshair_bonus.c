/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:05:46 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 12:12:50 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define CROSSHAIR_SIZE 40
#define CROSSHAIR_THICKNESS 1
#define CROSSHAIR_GAP 20
#define DOT_RADIUS 2

// Counter-Strike style green color
#define CROSSHAIR_COLOR 0x00FF00  // Bright green

void calculate_crosshair_position(t_game *game, int *center_x, int *center_y)
{
    *center_x = game->screen_width / 2;
    *center_y = game->screen_height / 2;
}

void draw_crosshair_line(t_game *game, int start_x, int start_y, int end_x, int end_y)
{
    for (int x = start_x; x <= end_x; x++)
    {
        for (int y = start_y; y <= end_y; y++)
        {
            img_pix_put(&game->img, x, y, CROSSHAIR_COLOR);
        }
    }
}

void draw_dot(t_game *game, int center_x, int center_y)
{
    for (int y = center_y - DOT_RADIUS; y <= center_y + DOT_RADIUS; y++)
    {
        for (int x = center_x - DOT_RADIUS; x <= center_x + DOT_RADIUS; x++)
        {
            if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) <= DOT_RADIUS * DOT_RADIUS)
            {
                img_pix_put(&game->img, x, y, CROSSHAIR_COLOR);
            }
        }
    }
}

void render_crosshair(t_game *game)
{
    int center_x, center_y;
    calculate_crosshair_position(game, &center_x, &center_y);
    
    // Draw horizontal lines
    draw_crosshair_line(game, 
        center_x - CROSSHAIR_SIZE / 2, center_y - CROSSHAIR_THICKNESS / 2,
        center_x - CROSSHAIR_GAP / 2, center_y + CROSSHAIR_THICKNESS / 2);
    
    draw_crosshair_line(game,
        center_x + CROSSHAIR_GAP / 2, center_y - CROSSHAIR_THICKNESS / 2,
        center_x + CROSSHAIR_SIZE / 2, center_y + CROSSHAIR_THICKNESS / 2);
    
    // Draw vertical lines
    draw_crosshair_line(game,
        center_x - CROSSHAIR_THICKNESS / 2, center_y - CROSSHAIR_SIZE / 2,
        center_x + CROSSHAIR_THICKNESS / 2, center_y - CROSSHAIR_GAP / 2);
    
    draw_crosshair_line(game,
        center_x - CROSSHAIR_THICKNESS / 2, center_y + CROSSHAIR_GAP / 2,
        center_x + CROSSHAIR_THICKNESS / 2, center_y + CROSSHAIR_SIZE / 2);

    // Draw the center dot
    draw_dot(game, center_x, center_y);
}