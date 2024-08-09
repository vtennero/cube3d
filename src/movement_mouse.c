/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:56:04 by toto              #+#    #+#             */
/*   Updated: 2024/08/09 16:00:56 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// int handle_mouse_move(int x, int y, t_game *game)
// {
// 	(void)game;
//     printf("Mouse moved to position: (%d, %d)\n", x, y);
//     return (0);
// }

int handle_mouse_move(int x, int y, t_game *game)
{
    static int last_x = -1;
    static int last_y = -1;
    float angle;
    float oldDirX, oldDirY, oldPlaneX, oldPlaneY;

    if (last_x == -1 || last_y == -1)
    {
        last_x = x;
        last_y = y;
        return (0);
    }

    // Calculate the mouse movement
    int dx = x - last_x;
    int dy = y - last_y;
    
    // Adjust these values to control the rotation and pitch speed
    float rotation_speed = 0.01;
    float pitch_speed = 0.001;

    // Calculate the rotation angle based on mouse movement
    angle = -dx * rotation_speed;

    // Rotate only if there's significant horizontal mouse movement
    if (fabs(angle) > 0.001)
    {
        // Rotate direction vector
        oldDirX = game->player->direction.x;
        oldDirY = game->player->direction.y;
        game->player->direction.x = oldDirX * cos(angle) - oldDirY * sin(angle);
        game->player->direction.y = oldDirX * sin(angle) + oldDirY * cos(angle);

        // Rotate camera plane vector
        oldPlaneX = game->player->plane.x;
        oldPlaneY = game->player->plane.y;
        game->player->plane.x = oldPlaneX * cos(angle) - oldPlaneY * sin(angle);
        game->player->plane.y = oldPlaneX * sin(angle) + oldPlaneY * cos(angle);

        // printf("Mouse moved horizontally. New direction: x = %f, y = %f\n", game->player->direction.x, game->player->direction.y);
        // const char *direction = get_cardinal_direction(game->player->direction.x, game->player->direction.y);
        // printf("Facing direction: %s\n", direction);
    }

    // Adjust pitch based on vertical mouse movement
    float pitch_change = -dy * pitch_speed;
    if (fabs(pitch_change) > 0.001)
    {
        game->player->pitch += pitch_change;
        
        // Clamp pitch to prevent over-rotation
        if (game->player->pitch > 1.0) game->player->pitch = 1.0;
        if (game->player->pitch < -1.0) game->player->pitch = -1.0;

        // printf("Mouse moved vertically. New pitch: %f\n", game->player->pitch);
    }

    last_x = x;
    last_y = y;
    return (0);
}