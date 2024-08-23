/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:29:27 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/15 17:45:08 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

const char *get_cardinal_direction(float x, float y)
{
    float angle = atan2(y, x); // Get angle in radians from x-axis
    if (angle < 0)
    {
        angle += 2 * M_PI; // Normalize angle to be between 0 and 2*pi
    }

    // Define angle thresholds for cardinal directions
    const float pi_8 = M_PI / 8; // Pi divided by 8 (22.5 degrees in radians)
    if (angle < pi_8 || angle > 15 * pi_8)
        return "East";
    else if (angle < 3 * pi_8)
        return "North-East";
    else if (angle < 5 * pi_8)
        return "North";
    else if (angle < 7 * pi_8)
        return "North-West";
    else if (angle < 9 * pi_8)
        return "West";
    else if (angle < 11 * pi_8)
        return "South-West";
    else if (angle < 13 * pi_8)
        return "South";
    else
        return "South-East";
}

int close_hook(t_game *game_state)
{
    ft_printf("Close button clicked, exiting...\n");
    // clear_mlx_resources(game_state);
    // clear_game_state(game_state);
    (void)game_state;
    exit(0);
    return (0);
}


int detect_collision(t_game *game, float newX, float newY)
{
    float buffer = 0.8; // Buffer distance to prevent entering into a wall
    
    // Calculate the direction vector
    float dirX = newX - game->player->position.x;
    float dirY = newY - game->player->position.y;
    
    // Normalize the direction vector
    float length = sqrt(dirX * dirX + dirY * dirY);
    if (length != 0) {
        dirX /= length;
        dirY /= length;
    }
    
    // Check multiple points along the movement path
    for (float t = 0; t <= 1; t += 0.1) {
        int mapX = (int)(game->player->position.x + dirX * (length * t + buffer));
        int mapY = (int)(game->player->position.y + dirY * (length * t + buffer));

        // Check if within map bounds and not a wall tile
        if (mapX < 0 || mapX >= game->map->width || 
            mapY < 0 || mapY >= game->map->height || 
            game->map->data[mapY][mapX] == TILE_WALL)
        {
            return 1; // Collision detected
        }
    }
    
    return 0; // No collision
}

// static int detect_collision(t_game *game, float newX, float newY)
// {
//     float buffer = 0.8; // Buffer distance to prevent entering into a wall
//     int mapX = (int)(newX + game->player->direction.x * buffer);
//     int mapY = (int)(newY + game->player->direction.y * buffer);

//     // Check if within map bounds and not a wall tile
//     if (mapX >= 0 && mapX < game->map->width && 
//         mapY >= 0 && mapY < game->map->height && 
//         game->map->data[mapY][mapX] != TILE_WALL)
//     {
//         return 0; // No collision
//     }
//     return 1; // Collision detected
// }

static void update_player_position(t_game *game, float newX, float newY)
{
    game->player->position.x = newX;
    game->player->position.y = newY;
    // printf("New player position: x = %f, y = %f\n", game->player->position.x, game->player->position.y);
}

// static void print_movement_direction(t_game *game)
// {
//     if (game->player->direction.y < 0 && fabs(game->player->direction.y) > fabs(game->player->direction.x)) {
//         printf("You are moving north\n");
//     }
// }

float calculate_dynamic_buffer(t_player *player, float base_speed)
{
    // Calculate buffer based on the dot product of direction and plane vectors
    float dir_mag = sqrt(player->direction.x * player->direction.x + player->direction.y * player->direction.y);
    float plane_mag = sqrt(player->plane.x * player->plane.x + player->plane.y * player->plane.y);
    float dot_product = player->direction.x * player->plane.x + player->direction.y * player->plane.y;

    float cosine_angle = dot_product / (dir_mag * plane_mag);
    float dynamic_buffer = base_speed * (1 - fabs(cosine_angle)); // Reduce buffer as angle approaches 90 degrees
    // printf("dynamic buffer %f\n", dynamic_buffer);
    return dynamic_buffer;
}

void handle_key_w(t_game *game)
{
    // printf("You just pressed W!\n");

    float speed = 0.1;  // Speed of movement, adjust as necessary
    float newX = game->player->position.x + game->player->direction.x * speed;
    float newY = game->player->position.y + game->player->direction.y * speed;

    if (!detect_collision(game, newX, newY))
    {
        update_player_position(game, newX, newY);
    }
    else
    {
        printf("Collision detected! Close to a wall.\n");
    }
    game->is_moving_fwd = 1;
    // update_gun_state(game);
    // print_game_map(game);
    // print_movement_direction(game);
    // game->is_moving_fwd = 0;
}

void handle_key_s(t_game *game)
{
    // printf("You just pressed S!\n");

    float speed = 0.1;  // Speed of movement, adjust as necessary
    float buffer = 0.8; // Buffer distance to prevent entering into a wall
    float newX = game->player->position.x - game->player->direction.x * (speed + buffer);
    float newY = game->player->position.y - game->player->direction.y * (speed + buffer);
    int mapX = (int)(newX);
    int mapY = (int)(newY);

    // Check collision with buffered coordinates
    if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL)
    {
        game->player->position.x = newX + game->player->direction.x * buffer; // Revert buffer
        game->player->position.y = newY + game->player->direction.y * buffer; // Revert buffer
        // printf("New player position: x = %f, y = %f\n", game->player->position.x, game->player->position.y);
    }
    else
    {
        printf("Collision/Out of Map movement\n");
    }
    game->is_moving_fwd = 1;
    // update_gun_state(game);
    // print_game_map(game);
}


void handle_key_up(t_game *game)
{
    // printf("You just pressed Up!\n");
    if (game->player->pitch < 1)
        game->player->pitch += 0.01;
    // printf("New pitch %f\n", game->player->pitch);
}

void handle_key_down(t_game *game)
{
    // printf("You just pressed Down!\n");
    if (game->player->pitch > -1)
        game->player->pitch -= 0.01;
    // printf("New pitch %f\n", game->player->pitch);
}

void handle_key_a(t_game *game)
{
    // printf("You just pressed A!\n");

    float speed = 0.1; // Control the speed of strafing

    // Calculate the left perpendicular vector relative to the player's direction
    float perpX = game->player->direction.y; // Use positive y component of the direction
    float perpY = -game->player->direction.x; // Use negative x component of the direction

    // Calculate the new position by moving left relative to the current facing direction
    float newX = game->player->position.x + perpX * speed;
    float newY = game->player->position.y + perpY * speed;

    if (!detect_collision(game, newX, newY))
    {
        update_player_position(game, newX, newY);
    }
    else
    {
        printf("Collision detected or Out of Map movement\n");
    }

    // print_movement_direction(game);
    // print_game_map(game);
}

void handle_key_d(t_game *game)
{
    // printf("You just pressed D!\n");

    float speed = 0.1;

    // Derive the perpendicular (right) direction vector
    float perpX = -game->player->direction.y; // Negative y component
    float perpY = game->player->direction.x;  // Positive x component

    // Calculate the new position by moving right to the direction the player is facing
    float newX = game->player->position.x + perpX * speed;
    float newY = game->player->position.y + perpY * speed;

    if (!detect_collision(game, newX, newY))
    {
        update_player_position(game, newX, newY);
    }
    else
    {
        printf("Collision/Out of Map movement\n");
    }

    // print_movement_direction(game);
    // print_game_map(game);
}

void handle_key_left(t_game *game)
{
    // printf("You just pressed Left!\n");

    float angle = -0.0872665; // -5 degrees in radians (counterclockwise)

    // Rotate direction vector
    float oldDirX = game->player->direction.x;
    float oldDirY = game->player->direction.y;
    game->player->direction.x = oldDirX * cos(angle) - oldDirY * sin(angle);
    game->player->direction.y = oldDirX * sin(angle) + oldDirY * cos(angle);

    // Rotate camera plane vector
    float oldPlaneX = game->player->plane.x;
    float oldPlaneY = game->player->plane.y;
    game->player->plane.x = oldPlaneX * cos(angle) - oldPlaneY * sin(angle);
    game->player->plane.y = oldPlaneX * sin(angle) + oldPlaneY * cos(angle);

    // printf("New direction.x = %f, New direction.y = %f\n", game->player->direction.x, game->player->direction.y);
    // const char *direction = get_cardinal_direction(game->player->direction.x, game->player->direction.y);
    // printf("Facing direction: %s\n", direction);

    // print_movement_direction(game);
}

void handle_key_right(t_game *game)
{
    // printf("You just pressed Right!\n");

    float angle = 0.0872665; // 5 degrees in radians (clockwise)

    // Rotate direction vector
    float oldDirX = game->player->direction.x;
    float oldDirY = game->player->direction.y;
    game->player->direction.x = oldDirX * cos(angle) - oldDirY * sin(angle);
    game->player->direction.y = oldDirX * sin(angle) + oldDirY * cos(angle);

    // Rotate camera plane vector
    float oldPlaneX = game->player->plane.x;
    float oldPlaneY = game->player->plane.y;
    game->player->plane.x = oldPlaneX * cos(angle) - oldPlaneY * sin(angle);
    game->player->plane.y = oldPlaneX * sin(angle) + oldPlaneY * cos(angle);

    // printf("New direction.x = %f, New direction.y = %f\n", game->player->direction.x, game->player->direction.y);
    // const char *direction = get_cardinal_direction(game->player->direction.x, game->player->direction.y);
    // printf("Facing direction: %s\n", direction);

    // print_movement_direction(game);
}

void handle_movement_dash(t_game *game)
{
    if (game->key_state[K_SHIFT] == 1)
    {
        printf("You just pressed Dash!\n");

        float speed = 0.3;  // Speed of movement, adjust as necessary
        float newX = game->player->position.x + game->player->direction.x * speed;
        float newY = game->player->position.y + game->player->direction.y * speed;

        if (!detect_collision(game, newX, newY))
        {
            game->player->position.x = newX;
            game->player->position.y = newY;
            // printf("New player position: x = %f, y = %f\n", game->player->position.x, game->player->position.y);
        }
        else
        {
            printf("Collision detected! Cannot dash.\n");
        }
        // print_game_map(game);
        game->is_moving_fwd = 1;

    }
}