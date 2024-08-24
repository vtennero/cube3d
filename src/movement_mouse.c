/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:56:04 by toto              #+#    #+#             */
/*   Updated: 2024/08/24 23:53:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void init_last_pos(int x, int y, int *last_x, int *last_y)
{
    if (*last_x == -1 || *last_y == -1)
    {
        *last_x = x;
        *last_y = y;
    }
}

void calc_mouse_delta(int x, int y, int *last_x, int *last_y, int *dx, int *dy)
{
    *dx = x - *last_x;
    *dy = y - *last_y;
    *last_x = x;
    *last_y = y;
}

float calc_rotation_angle(int dx, float speed)
{
    return dx * speed;
}

void rotate_vector(float *x, float *y, float angle)
{
    float old_x = *x;
    *x = old_x * cos(angle) - *y * sin(angle);
    *y = old_x * sin(angle) + *y * cos(angle);
}

void rotate_player(t_game *game, float angle)
{
    rotate_vector(&game->player->direction.x, &game->player->direction.y, angle);
    rotate_vector(&game->player->plane.x, &game->player->plane.y, angle);
}

void adjust_pitch(t_game *game, int dy, float speed)
{
    float change = -dy * speed;
    if (fabs(change) > 0.001)
    {
        game->player->pitch += change;
        game->player->pitch = fmax(-1.0, fmin(1.0, game->player->pitch));
    }
}


int handle_mouse_move(int x, int y, t_game *game)
{
    static int last_x = -1;
    static int last_y = -1;
    int dx, dy;
    float angle;
    float rot_speed = 0.01;
    float pitch_speed = 0.001;

    init_last_pos(x, y, &last_x, &last_y);
    calc_mouse_delta(x, y, &last_x, &last_y, &dx, &dy);
    
    angle = calc_rotation_angle(dx, rot_speed);
    if (fabs(angle) > 0.001)
    {
        rotate_player(game, angle);
    }

    adjust_pitch(game, dy, pitch_speed);


    return (0);
}



int handle_mouse_click(int button, int x, int y, void *param)
{
    t_game *game = (t_game *)param;
    if (button == 1)
    {
        printf("Shooting at position (%d, %d)\n", x, y);

        game->is_shooting = 1;
        int random_value = random_int(game, 6);
        play_gun_sound(game);

        // If the random value is 0 (25% chance), print the special text
        if (random_value == 0)
        {
            printf("Get some get some\n");
		    playAudioFileWithDelay("audio/getsome.mp3", 0);
            // play audio
        }
    }
    else if (button == 3)
    {
        printf("launching orbital strike at %f, %f\n", game->center_floor_coords.y, game->center_floor_coords.x);
        // add script launch strike
        game->strike->position.y = game->center_floor_coords.y;
        game->strike->position.x = game->center_floor_coords.x;
        game->strike->is_launching = 1;
    }
    return (0);
}

int handle_mouse_release(int button, int x, int y, void *param)
{
    t_game *game = (t_game *)param;

    (void)y;
    (void)x;

    if (button == 1)  // Left mouse button
    {
        game->is_shooting = 0;
    }

    return (0);
}