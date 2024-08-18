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

#define MOVEMENT_PROBABILITY 999500 // Adjust this to change how often enemies move (0-100)
#define MOVEMENT_SPEED 0.05     // Adjust this to change how far enemies move each step

void print_enemy_direction(int index, float dx, float dy)
{
    const char *direction;
    
    if (dx == 0 && dy == 0)
        direction = "? Nope";
    else if (dx > 0 && dy == 0)
        direction = "East";
    else if (dx < 0 && dy == 0)
        direction = "West";
    else if (dx == 0 && dy > 0)
        direction = "South";
    else if (dx == 0 && dy < 0)
        direction = "North";
    else if (dx > 0 && dy > 0)
        direction = "Southeast";
    else if (dx > 0 && dy < 0)
        direction = "Northeast";
    else if (dx < 0 && dy > 0)
        direction = "Southwest";
    else // dx < 0 && dy < 0
        direction = "Northwest";

    printf("Enemy %d is moving %s\n", index, direction);
}

// Function to check if a position is within a wall
int is_wall(t_game *game, float x, float y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    
    if (map_x < 0 || map_x >= game->map->width || map_y < 0 || map_y >= game->map->height)
        return 1; // Treat out of bounds as a wall
    
    return game->map->data[map_y][map_x] == '1';
}

#define STOP_DISTANCE 2.0f  // Adjust this value to change how close enemies get to the player




static int should_move(unsigned long long *enemy_seed)
{
    return xorshift64(enemy_seed) % 1000000 < MOVEMENT_PROBABILITY;
}

static void calculate_direction(t_game *game, t_enemy *enemy, float *dx, float *dy)
{
    float player_x = game->player->position.x;
    float player_y = game->player->position.y;
    
    float vector_x = player_x - enemy->position.x;
    float vector_y = player_y - enemy->position.y;
    
    float distance_to_player = sqrt(vector_x * vector_x + vector_y * vector_y);
    
    if (distance_to_player > STOP_DISTANCE) {
        vector_x /= distance_to_player;
        vector_y /= distance_to_player;

        *dx = vector_x * MOVEMENT_SPEED;
        *dy = vector_y * MOVEMENT_SPEED;
    }
    else {
        *dx = 0;
        *dy = 0;
    }
}

static int check_wall_collision(t_game *game, t_enemy *enemy, float dx, float dy)
{
    float speed = sqrt(dx*dx + dy*dy);  // Calculate the speed of movement
    float direction_x = dx / speed;     // Normalize direction
    float direction_y = dy / speed;

    float newX = enemy->position.x + dx;
    float newY = enemy->position.y + dy;

    // Use STOP_DISTANCE as the buffer
    int mapX = (int)(newX + direction_x * STOP_DISTANCE);
    int mapY = (int)(newY + direction_y * STOP_DISTANCE);

    // Check if the new position is within map bounds and not a wall
    if (mapX >= 0 && mapX < game->map->width && 
        mapY >= 0 && mapY < game->map->height && 
        game->map->data[mapY][mapX] != TILE_WALL)
    {
        return 0;  // Not a wall, can move
    }

    return 1;  // Wall detected, can't move
}

static void update_position(t_enemy *enemy, float dx, float dy)
{
    enemy->position.x += dx;
    enemy->position.y += dy;
}

static void update_momentum(t_enemy *enemy, float dx)
{
    if (dx > 0) enemy->momentum = (enemy->momentum < 3) ? enemy->momentum + 1 : 3;
    else if (dx < 0) enemy->momentum = (enemy->momentum > -3) ? enemy->momentum - 1 : -3;
    else enemy->momentum = (enemy->momentum > 0) ? enemy->momentum - 1 : 
                           (enemy->momentum < 0) ? enemy->momentum + 1 : 0;
}


void relocate_enemy(t_game *game, t_enemy *enemy, int index)
{
    unsigned long long enemy_seed = game->random_seed ^ (index * 1099511628211ULL);
    
    if (!should_move(&enemy_seed))
        return;

    float dx = 0, dy = 0;
    calculate_direction(game, enemy, &dx, &dy);
    
if (!check_wall_collision(game, enemy, dx, dy))
{
    update_position(enemy, dx, dy);
}
else
{
    // If there's a wall, don't move
    dx = 0;
    dy = 0;
}

update_position(enemy, dx, dy);
    update_momentum(enemy, dx);
    // print_enemy_direction(index, dx, dy);
}

// void relocate_enemy(t_game *game, t_enemy *enemy, int index)
// {
//     // Use the enemy's index to create a unique seed for this enemy
//     unsigned long long enemy_seed = game->random_seed ^ (index * 1099511628211ULL);
    
//     // Decide whether to move based on MOVEMENT_PROBABILITY
//     if (xorshift64(&enemy_seed) % 1000000 >= MOVEMENT_PROBABILITY)
//         return;

//     float dx = 0, dy = 0;

//     // Calculate direction towards the player
//     float player_x = game->player->position.x;
//     float player_y = game->player->position.y;
    
//     // Calculate the vector from enemy to player
//     float vector_x = player_x - enemy->position.x;
//     float vector_y = player_y - enemy->position.y;
    
//     // Calculate the distance to the player
//     float distance_to_player = sqrt(vector_x * vector_x + vector_y * vector_y);
    
//     // Only move if the enemy is further than STOP_DISTANCE from the player
//     if (distance_to_player > STOP_DISTANCE) {
//         // Normalize the vector
//         vector_x /= distance_to_player;
//         vector_y /= distance_to_player;

//         // Set movement based on the normalized vector
//         dx = vector_x * MOVEMENT_SPEED;
//         dy = vector_y * MOVEMENT_SPEED;

//         // Update position
//         enemy->position.x += dx;
//         enemy->position.y += dy;

//         // Update momentum (optional, you might want to remove or modify this part)
//         if (dx > 0) enemy->momentum = (enemy->momentum < 3) ? enemy->momentum + 1 : 3;
//         else if (dx < 0) enemy->momentum = (enemy->momentum > -3) ? enemy->momentum - 1 : -3;
//         else enemy->momentum = (enemy->momentum > 0) ? enemy->momentum - 1 : 
//                                (enemy->momentum < 0) ? enemy->momentum + 1 : 0;

//         print_enemy_direction(index, dx, dy);
//     }
//     else {
//         // Enemy is within STOP_DISTANCE of the player, so it doesn't move
//         print_enemy_direction(index, 0, 0);
//     }
// }
// void relocate_enemy(t_game *game, t_enemy *enemy, int index)
// {
//     // Use the enemy's index to create a unique seed for this enemy
//     unsigned long long enemy_seed = game->random_seed ^ (index * 1099511628211ULL);
    
//     // Decide whether to move based on MOVEMENT_PROBABILITY
//     if (xorshift64(&enemy_seed) % 100 >= MOVEMENT_PROBABILITY)
//         return;

//     float dx = 0, dy = 0;

//     // Use momentum to influence movement direction
//     if (enemy->momentum > 0)
//     {
//         dx = MOVEMENT_SPEED;
//     }
//     else if (enemy->momentum < 0)
//     {
//         dx = -MOVEMENT_SPEED;
//     }
//     else
//     {
//         // If no momentum, choose a random direction
//         int direction = xorshift64(&enemy_seed) % 4;
//         switch (direction)
//         {
//             case 0: dx = MOVEMENT_SPEED; break;
//             case 1: dx = -MOVEMENT_SPEED; break;
//             case 2: dy = MOVEMENT_SPEED; break;
//             case 3: dy = -MOVEMENT_SPEED; break;
//         }
//     }

//     // Check for collision and update position if no wall
//     float new_x = enemy->position.x + dx;
//     float new_y = enemy->position.y + dy;

//     if (!is_wall(game, new_x, enemy->position.y))
// 	{
//         enemy->position.x = new_x;
// 		// printf("enemy %d relocated at %f %f\n", index, new_x, enemy->position.y);

// 	}
    
//     if (!is_wall(game, enemy->position.x, new_y))
// 	{
// 		// printf("enemy %d relocated at %f %f\n", index, enemy->position.x, new_y);
//         enemy->position.y = new_y;
// 	}

//     // Update momentum
//     if (dx > 0) enemy->momentum = (enemy->momentum < 3) ? enemy->momentum + 1 : 3;
//     else if (dx < 0) enemy->momentum = (enemy->momentum > -3) ? enemy->momentum - 1 : -3;
//     else enemy->momentum = (enemy->momentum > 0) ? enemy->momentum - 1 : 
//                            (enemy->momentum < 0) ? enemy->momentum + 1 : 0;

// print_enemy_direction(index, dx, dy);
// }

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