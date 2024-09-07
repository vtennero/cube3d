#include "cube3d.h"
#include <time.h>

#define STOP_DISTANCE 2.0f  // Adjust this value to change how close enemies get to the player
#define HIT_PROBABILITY 5000 // Increased to 20% chance (was 100000)

void bump_player(t_game *game, int enemy_index)
{
    t_enemy *enemy = &game->enemies[enemy_index];
    
    // Calculate vector from enemy to player
    float dx = game->player->position.x - enemy->position.x;
    float dy = game->player->position.y - enemy->position.y;
    
    // Normalize the vector
    float length = sqrt(dx * dx + dy * dy);
    dx /= length;
    dy /= length;
    
    // Apply bump (adjust BUMP_DISTANCE to change the intensity of the bump)
    float BUMP_DISTANCE = 0.5f;
    float newX = game->player->position.x + dx * BUMP_DISTANCE;
    float newY = game->player->position.y + dy * BUMP_DISTANCE;
    
    // Check for collision before applying the bump
    if (!detect_collision(game, newX, newY))
    {
        // No collision, apply the bump
        game->player->position.x = newX;
        game->player->position.y = newY;
    }
    else
    {
        // Collision detected, try smaller bumps until no collision or minimum distance reached
        float min_bump = 0.1f;  // Minimum bump distance to try
        while (BUMP_DISTANCE > min_bump)
        {
            BUMP_DISTANCE *= 0.5f;  // Reduce bump distance by half
            newX = game->player->position.x + dx * BUMP_DISTANCE;
            newY = game->player->position.y + dy * BUMP_DISTANCE;
            
            if (!detect_collision(game, newX, newY))
            {
                // No collision with reduced bump, apply it
                game->player->position.x = newX;
                game->player->position.y = newY;
                break;
            }
        }
        // If we couldn't find a valid bump, the player position remains unchanged
    }
}

void render_hit(t_game *game)
{
    int x, y;
    int solid_red = 0xFF0000;  // Solid red color
    
    if (game->player->is_hit)
    {
        for (y = 0; y < game->screen_height; y++)
    {
        for (x = 0; x < game->screen_width; x++)
        {
            // Decide whether to render this pixel based on a pattern
            if ((x + y) % 3 == 0)  // This creates a diagonal pattern
            {
                img_pix_put(&game->img, x, y, solid_red);
            }
            // Pixels where (x + y) % 3 != 0 are left untouched,
            // creating the illusion of transparency
        }
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
            game->player->is_hit = 1;
            add_script(game, get_hit, 1);
            printf("You got hit by enemy %d; new hp: %d\n", index, game->player->hp);
            bump_player(game, index);

            int random_value = random_int(game, 3);
            if (random_value == 0 && game->player->hp <= 0.25 * MAX_HEALTH)
            {
                stopAudioFile("audio/stims00.mp3");
                playAudioFileWithDelay("audio/stims00.mp3", 0);
            }
            
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
        if (game->enemies[i].is_alive && game->player->is_extracting == 0 && game->player->is_dead == 0)
        {
            enemy_hit_attempt(game, &game->enemies[i], i);
        }
        else
        {
            // printf("Enemy %d is not alive, skipping\n", i);
        }
    }
}