/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_attack_bonus01.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:03:37 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 14:03:38 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float vector2d_distance_squared(t_vector2d a, t_vector2d b)
{
    t_vector2d diff;

    diff.x = a.x - b.x;
    diff.y = a.y - b.y;
    return (diff.x * diff.x + diff.y * diff.y);
}

void calculate_vector(t_game *game, int enemy_index, float *dx, float *dy)
{
    t_enemy *enemy;

    enemy = &game->enemies[enemy_index];
    *dx = game->player->position.x - enemy->position.x;
    *dy = game->player->position.y - enemy->position.y;
}

void normalize_vector(float *dx, float *dy)
{
    float length;

    length = sqrt(*dx * *dx + *dy * *dy);
    *dx /= length;
    *dy /= length;
}

float calculate_new_position_x(t_game *game, float dx, float bump_distance)
{
    return game->player->position.x + dx * bump_distance;
}

float calculate_new_position_y(t_game *game, float dy, float bump_distance)
{
    return game->player->position.y + dy * bump_distance;
}
