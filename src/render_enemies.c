/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:44:50 by toto              #+#    #+#             */
/*   Updated: 2024/08/22 23:19:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

#define NUM_ENEMY_FRAMES 14  // 0-13 included
#define ANIMATION_STEP_INTERVAL 5  // Change frame every 5 game ticks
#define JUMP_INTERVAL 75  // Consider a jump every 75 animation steps

int get_next_frame(t_enemy *enemy)
{
    enemy->frame_count++;
    
    // Only consider changing frame every ANIMATION_STEP_INTERVAL
    if (enemy->frame_count % ANIMATION_STEP_INTERVAL != 0)
        return enemy->current_frame;

    // Periodic jump logic
    enemy->animation_steps++;
    if (enemy->animation_steps >= JUMP_INTERVAL && (rand() % 100) < 10)
    {
        int jump = (rand() % 6) + 5;  // Jump 5-10 frames
        if (rand() % 2 == 0) jump = -jump;  // 50% chance to jump backwards
        enemy->current_frame = (enemy->current_frame + jump + NUM_ENEMY_FRAMES) % NUM_ENEMY_FRAMES;
        enemy->momentum = 0;
        enemy->animation_steps = 0;
        return enemy->current_frame;
    }

    // Normal frame transition logic
    int roll = rand() % 100;
    if (roll < 70)
    {
        // 70% chance to stay on the current frame
        if (enemy->momentum > 0) enemy->momentum--;
        else if (enemy->momentum < 0) enemy->momentum++;
        return enemy->current_frame;
    }

    // 30% chance to move based on momentum
    int direction = (enemy->momentum > 0) ? 1 : (enemy->momentum < 0) ? -1 : (rand() % 2 == 0) ? 1 : -1;
    int momentum_strength = abs(enemy->momentum);
    
    int move_chance;
    if (momentum_strength >= 2) move_chance = 80;
    else if (momentum_strength == 1) move_chance = 65;
    else move_chance = 50;

    if ((rand() % 100) < move_chance)
    {
        enemy->current_frame = (enemy->current_frame + direction + NUM_ENEMY_FRAMES) % NUM_ENEMY_FRAMES;
        enemy->momentum += direction;
        enemy->momentum = (enemy->momentum > 3) ? 3 : (enemy->momentum < -3) ? -3 : enemy->momentum;
    }
    else
    {
        enemy->current_frame = (enemy->current_frame - direction + NUM_ENEMY_FRAMES) % NUM_ENEMY_FRAMES;
        enemy->momentum -= direction;
        enemy->momentum = (enemy->momentum > 3) ? 3 : (enemy->momentum < -3) ? -3 : enemy->momentum;
    }

    return enemy->current_frame;
}

void render_enemy(t_game *game, t_enemy *enemy)
{
    int current_frame = get_next_frame(enemy);
    // printf("current_frame %d\n", current_frame);
    t_texture *enemy_texture = &game->enemy_textures[current_frame];

    float spriteX, spriteY;
    calculate_sprite_position(game, enemy->position.x, enemy->position.y, &spriteX, &spriteY);

    float transformX, transformY;
    transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

    int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

    int spriteHeight, drawStartY, drawEndY;
    calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

    int spriteWidth, drawStartX, drawEndX;
    calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

    for (int stripe = drawStartX; stripe < drawEndX; stripe++)
    {
        if (is_sprite_in_front(transformY, stripe, game->screen_width))
        {
            draw_sprite_stripe(game, enemy_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
        }
    }
}

void render_enemies(t_game *game)
{
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].is_alive)
        {
            render_enemy(game, &game->enemies[i]);
        }
    }
}

void check_enemy_at_center(t_game *game)
{
    float centerX = game->screen_width / 2.0f;
    float centerY = game->screen_height / 2.0f;
    
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (!game->enemies[i].is_alive)
            continue;

        float spriteX, spriteY;
        calculate_sprite_position(game, game->enemies[i].position.x, game->enemies[i].position.y, &spriteX, &spriteY);

        float transformX, transformY;
        transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

        int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

        int spriteHeight, drawStartY, drawEndY;
        calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

        int spriteWidth, drawStartX, drawEndX;
        calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

        // Check if the center of the screen is within the enemy's sprite boundaries
        if (centerX >= drawStartX && centerX < drawEndX && 
            centerY >= drawStartY && centerY < drawEndY && game->enemies[i].is_alive )
        {
            // printf("Aiming at enemy %d\n", i);
            if (game->is_shooting)
            {
                game->enemies[i].is_alive = 0;
                play_bug_death(game);
            }
            return;  // Exit the function after finding the first enemy at the center
        }
    }

    // If no enemy is found at the center
    // printf("No enemy at the center of the screen\n");
}

int randomize_dead_enemy_positions(t_game *game)
{
    // printf("Randomizing positions of defeated enemies\n");
    int i, x, y;
    int enemies_repositioned = 0;
    
    for (i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].is_alive == 0)
        {
            do {
                x = random_int(game, game->map->width);
                y = random_int(game, game->map->height);
            } while (game->map->data[y][x] == 1); // Keep trying until we find a non-wall position
            
            game->enemies[i].position.x = (float)x + 0.5f; // Center in the tile
            game->enemies[i].position.y = (float)y + 0.5f; // Center in the tile
            game->enemies[i].is_alive = 1; // Revive the enemy
            game->enemies[i].frame_count = 0; // Reset animation frame
            game->enemies[i].current_frame = 0; // Reset current frame
            game->enemies[i].momentum = 0; // Reset momentum
            game->enemies[i].animation_steps = 0; // Reset animation steps
            enemies_repositioned++;
        }
    }
    
    // printf("%d defeated enemies repositioned and revived\n", enemies_repositioned);
    return (enemies_repositioned);
}