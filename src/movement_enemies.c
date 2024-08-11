/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_enemies.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:23:26 by toto              #+#    #+#             */
/*   Updated: 2024/08/11 17:41:47 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define MOVEMENT_PROBABILITY 30 // Adjust this to change how often enemies move (0-100)
#define MOVEMENT_SPEED 0.05     // Adjust this to change how far enemies move each step

// Function to check if a position is within a wall
int is_wall(t_game *game, float x, float y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    
    if (map_x < 0 || map_x >= game->map->width || map_y < 0 || map_y >= game->map->height)
        return 1; // Treat out of bounds as a wall
    
    return game->map->data[map_y][map_x] == '1';
}

void relocate_enemy(t_game *game, t_enemy *enemy, int index)
{
    // Use the enemy's index to create a unique seed for this enemy
    unsigned long long enemy_seed = game->random_seed ^ (index * 1099511628211ULL);
    
    // Decide whether to move based on MOVEMENT_PROBABILITY
    if (xorshift64(&enemy_seed) % 100 >= MOVEMENT_PROBABILITY)
        return;

    float dx = 0, dy = 0;

    // Use momentum to influence movement direction
    if (enemy->momentum > 0)
    {
        dx = MOVEMENT_SPEED;
    }
    else if (enemy->momentum < 0)
    {
        dx = -MOVEMENT_SPEED;
    }
    else
    {
        // If no momentum, choose a random direction
        int direction = xorshift64(&enemy_seed) % 4;
        switch (direction)
        {
            case 0: dx = MOVEMENT_SPEED; break;
            case 1: dx = -MOVEMENT_SPEED; break;
            case 2: dy = MOVEMENT_SPEED; break;
            case 3: dy = -MOVEMENT_SPEED; break;
        }
    }

    // Check for collision and update position if no wall
    float new_x = enemy->position.x + dx;
    float new_y = enemy->position.y + dy;

    if (!is_wall(game, new_x, enemy->position.y))
	{
        enemy->position.x = new_x;
		// printf("enemy %d relocated at %f %f\n", index, new_x, enemy->position.y);

	}
    
    if (!is_wall(game, enemy->position.x, new_y))
	{
		// printf("enemy %d relocated at %f %f\n", index, enemy->position.x, new_y);
        enemy->position.y = new_y;
	}

    // Update momentum
    if (dx > 0) enemy->momentum = (enemy->momentum < 3) ? enemy->momentum + 1 : 3;
    else if (dx < 0) enemy->momentum = (enemy->momentum > -3) ? enemy->momentum - 1 : -3;
    else enemy->momentum = (enemy->momentum > 0) ? enemy->momentum - 1 : 
                           (enemy->momentum < 0) ? enemy->momentum + 1 : 0;
}

void relocate_enemies(t_game *game)
{
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].is_alive)
        {
            relocate_enemy(game, &game->enemies[i], i);
        }
    }
}