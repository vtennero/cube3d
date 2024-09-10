/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_hit_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:23:14 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/10 10:23:14 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int apply_bump(t_game *game, float newX, float newY)
{
    if (!detect_collision(game, newX, newY))
    {
        game->player->position.x = newX;
        game->player->position.y = newY;
        return 1;
    }
    return 0;
}

void apply_reduced_bump(t_game *game, float dx, float dy, float *bump_distance)
{
    float new_x;
    float new_y;
    float min_bump;

    min_bump = 0.1f;
    while (*bump_distance > min_bump)
    {
        *bump_distance *= 0.5f;
        new_x = calculate_new_position_x(game, dx, *bump_distance);
        new_y = calculate_new_position_y(game, dy, *bump_distance);
        if (apply_bump(game, new_x, new_y))
            break;
    }
}

void bump_player(t_game *game, int enemy_index)
{
    float dx;
    float dy;
    float bump_distance;
    float new_x;
    float new_y;

    bump_distance = 0.5f;
    calculate_vector(game, enemy_index, &dx, &dy);
    normalize_vector(&dx, &dy);
    new_x = calculate_new_position_x(game, dx, bump_distance);
    new_y = calculate_new_position_y(game, dy, bump_distance);
    if (!apply_bump(game, new_x, new_y))
    {
        apply_reduced_bump(game, dx, dy, &bump_distance);
    }
}


void render_hit(t_game *game)
{
    int x;
    int y;
    int solid_red;

    solid_red = 0xFF0000;
    if (game->player->is_hit)
    {
        y = 0;
        while (y < game->screen_height)
        {
            x = 0;
            while (x < game->screen_width)
            {
                if ((x + y) % 3 == 0)
                {
                    img_pix_put(&game->img, x, y, solid_red);
                }
                x++;
            }
            y++;
        }
    }
}


static int should_attempt_hit(unsigned long long *enemy_seed)
{
    unsigned long long random_value;

    *enemy_seed = xorshift64(enemy_seed);
    random_value = *enemy_seed % 1000000;
    return (random_value < HIT_PROBABILITY);
}


static float vector2d_distance_squared(t_vector2d a, t_vector2d b)
{
    t_vector2d diff;

    diff.x = a.x - b.x;
    diff.y = a.y - b.y;
    return (diff.x * diff.x + diff.y * diff.y);
}


static int is_close_enough(t_game *game, t_enemy *enemy)
{
    t_vector2d player_pos;
    t_vector2d enemy_pos;
    float distance_squared;

    player_pos = game->player->position;
    enemy_pos = enemy->position;
    distance_squared = vector2d_distance_squared(player_pos, enemy_pos);
    return (distance_squared <= STOP_DISTANCE * STOP_DISTANCE);
}



void enemy_hit_attempt(t_game *game, t_enemy *enemy, int index)
{
    unsigned long long enemy_seed;

    enemy_seed = game->random_seed ^ (index * 1099511628211ULL);
    if (should_attempt_hit(&enemy_seed))
    {
        if (is_close_enough(game, enemy))
        {
            game->player->is_hit = 1;
            add_script(game, get_hit, 1);
            printf("You got hit by enemy %d; new hp: %d\n", index, game->player->hp);
            bump_player(game, index);
        }
    }
    game->random_seed = xorshift64(&game->random_seed);
}



void enemies_hit(t_game *game)
{
    int i;

    i = 0;
    while (i < game->num_enemies)
    {
        if (game->enemies[i].is_alive && game->player->is_extracting == 0
            && game->player->is_dead == 0)
        {
            enemy_hit_attempt(game, &game->enemies[i], i);
        }
        i++;
    }
}