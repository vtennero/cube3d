#include "cube3d.h"
#include <time.h>

#define STOP_DISTANCE 2.0f  // Adjust this value to change how close enemies get to the player
#define HIT_PROBABILITY 5000 // Increased to 20% chance (was 100000)

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
            add_script(game, get_hit, 0);
            game->player->is_hit = 1;
            printf("You got hit by enemy %d; new hp: %d\n", index, game->player->hp);
            int random_value = random_int(game, 6);
            if (random_value == 0 && game->player->hp <= 0.25 * MAX_HEALTH)
            {
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