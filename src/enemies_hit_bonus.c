#include "cube3d.h"
#include <time.h>

#define STOP_DISTANCE 2.0f  // Adjust this value to change how close enemies get to the player
#define HIT_PROBABILITY 5000 // Increased to 20% chance (was 100000)


void render_hit(t_game *game)
{
    int x, y;
    int base_color = 0xFF0000;  // Red color
    
    for (y = 0; y < game->screen_height; y++)
    {
        for (x = 0; x < game->screen_width; x++)
        {
            // Create a "fake" transparency effect
            int transparency = (x * y) % 256;
            int color = base_color | (transparency << 24);
            
            // Apply a subtle variation based on screen position
            color = color * (0.8 + 0.2 * sin((float)x / game->screen_width * M_PI) * 
                                   sin((float)y / game->screen_height * M_PI));
            
            img_pix_put(&game->img, x, y, color);
        }
    }
}

// Function to check if an enemy should attempt to hit
static int should_attempt_hit(unsigned long long *enemy_seed)
{
    *enemy_seed = xorshift64(enemy_seed); // Update the seed
    unsigned long long random_value = *enemy_seed % 1000000;
    // printf("Random value: %llu, HIT_PROBABILITY: %d\n", random_value, HIT_PROBABILITY);
    return random_value < HIT_PROBABILITY;
}

// Function to check if the enemy is close enough to hit the player
static int is_close_enough(t_game *game, t_enemy *enemy)
{
    float player_x = game->player->position.x;
    float player_y = game->player->position.y;
    
    float vector_x = player_x - enemy->position.x;
    float vector_y = player_y - enemy->position.y;
    
    float distance_to_player = sqrt(vector_x * vector_x + vector_y * vector_y);
    // printf("Distance to player: %f, STOP_DISTANCE: %f\n", distance_to_player, STOP_DISTANCE);
    return distance_to_player <= STOP_DISTANCE;
}

// Function to handle a single enemy's hit attempt
void enemy_hit_attempt(t_game *game, t_enemy *enemy, int index)
{
    static unsigned long long base_seed = 0;
    if (base_seed == 0) {
        base_seed = (unsigned long long)time(NULL);
    }
    unsigned long long enemy_seed = base_seed ^ (index * 1099511628211ULL);
    
    // printf("Enemy %d attempting to hit...\n", index);
    if (should_attempt_hit(&enemy_seed))
    {
        // printf("Hit attempt passed probability check\n");
        if (is_close_enough(game, enemy))
        {
            if (game->player->hp)
                game->player->hp--;
            printf("You got hit by enemy %d; new hp: %d\n", index, game->player->hp);
            
        }
        else
        {
            // printf("Enemy %d is not close enough to hit\n", index);
        }
    }
    else
    {
        // printf("Hit attempt failed probability check\n");
    }
    
    // Update the base seed for the next frame
    base_seed = xorshift64(&base_seed);
}

// Main function to handle all enemies' hit attempts
void enemies_hit(t_game *game)
{
    // printf("Checking hits for %d enemies\n", game->num_enemies);
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].is_alive)
        {
            enemy_hit_attempt(game, &game->enemies[i], i);
        }
        else
        {
            // printf("Enemy %d is not alive, skipping\n", i);
        }
    }
}