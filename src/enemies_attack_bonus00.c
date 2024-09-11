/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_attack_bonus00.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:03:32 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 14:03:32 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

int should_attempt_hit(unsigned long long *enemy_seed)
{
    unsigned long long random_value;

    *enemy_seed = xorshift64(enemy_seed);
    random_value = *enemy_seed % 1000000;
    return (random_value < HIT_PROBABILITY);
}

int is_close_enough(t_game *game, t_enemy *enemy)
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
