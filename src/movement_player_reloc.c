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

void handle_key_left(t_game *game)
{
    printf("You just pressed Left!\n");

    float angle = 0.0872665; // 5 degrees in radians

    // Rotate direction vector counterclockwise
    float oldDirX = game->player->direction.x;
    float oldDirY = game->player->direction.y;
    game->player->direction.x = oldDirX * cos(angle) - oldDirY * sin(angle);
    game->player->direction.y = oldDirX * sin(angle) + oldDirY * cos(angle);

    // Rotate camera plane vector counterclockwise
    float oldPlaneX = game->player->plane.x;
    float oldPlaneY = game->player->plane.y;
    game->player->plane.x = oldPlaneX * cos(angle) - oldPlaneY * sin(angle);
    game->player->plane.y = oldPlaneX * sin(angle) + oldPlaneY * cos(angle);

    printf("New direction.x = %f, New direction.y = %f\n", game->player->direction.x, game->player->direction.y);
    const char *direction = get_cardinal_direction(game->player->direction.x, game->player->direction.y);
    printf("Facing direction: %s\n", direction);
}

void handle_key_right(t_game *game)
{
    printf("You just pressed Right!\n");

    float angle = 0.0872665; // 5 degrees in radians

    // Rotate direction vector clockwise
    float oldDirX = game->player->direction.x;
    float oldDirY = game->player->direction.y;
    game->player->direction.x = oldDirX * cos(angle) + oldDirY * sin(angle);
    game->player->direction.y = -oldDirX * sin(angle) + oldDirY * cos(angle);

    // Rotate camera plane vector clockwise
    float oldPlaneX = game->player->plane.x;
    float oldPlaneY = game->player->plane.y;
    game->player->plane.x = oldPlaneX * cos(angle) + oldPlaneY * sin(angle);
    game->player->plane.y = -oldPlaneX * sin(angle) + oldPlaneY * cos(angle);

    printf("New direction.x = %f, New direction.y = %f\n", game->player->direction.x, game->player->direction.y);
    const char *direction = get_cardinal_direction(game->player->direction.x, game->player->direction.y);
    printf("Facing direction: %s\n", direction);
}

void handle_key_w(t_game *game)
{
    printf("You just pressed W!\n");

    float speed = 0.1;  // Speed of movement, adjust as necessary
    float buffer = 0.8; // Buffer distance to prevent entering into a wall
    float newX = game->player->position.x + game->player->direction.x * speed;
    float newY = game->player->position.y + game->player->direction.y * speed;

    // Check collision using the buffer for more predictive collision detection
    int mapX = (int)(newX + game->player->direction.x * buffer);
    int mapY = (int)(newY + game->player->direction.y * buffer);

    // Ensure within map bounds and not a wall tile
    if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL)
    {
        game->player->position.x = newX;
        game->player->position.y = newY;
        printf("New player position: x = %f, y = %f\n", game->player->position.x, game->player->position.y);
    }
    else
    {
        printf("Collision detected! Close to a wall.\n");
    }
    update_gun_frame(game);
    print_game_map(game);
}

// // Add this helper function for wall collision detection
// int is_wall(t_game *game, double x, double y)
// {
//     int mapX = (int)x;
//     int mapY = (int)y;

//     // Check map bounds
//     if (mapX < 0 || mapX >= game->map->width || mapY < 0 || mapY >= game->map->height)
//     {
//         return 1; // Treat out of bounds as a wall
//     }

//     // Check if the tile is a wall
//     return (game->map->data[mapY][mapX] == TILE_WALL);
// }

// void handle_key_w(t_game *game)
// {
//     printf("You just pressed W!\n");

//     double speed = 0.1; // Reduced speed for smoother movement
//     double newX = game->player->position.x + game->player->direction.x * speed;
//     double newY = game->player->position.y + game->player->direction.y * speed;

//     // Check collision for both X and Y separately
//     if (!is_wall(game, newX, game->player->position.y))
//     {
//         game->player->position.x = newX;
//     }
//     if (!is_wall(game, game->player->position.x, newY))
//     {
//         game->player->position.y = newY;
//     }

//     printf("New player position: x = %.4f, y = %.4f\n", game->player->position.x, game->player->position.y);
//     print_game_map(game);
// }

void handle_key_s(t_game *game)
{
    printf("You just pressed S!\n");

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
        printf("New player position: x = %f, y = %f\n", game->player->position.x, game->player->position.y);
    }
    else
    {
        printf("Collision/Out of Map movement\n");
    }
    update_gun_frame(game);
    print_game_map(game);
}

float calculate_dynamic_buffer(t_player *player, float base_speed)
{
    // Calculate buffer based on the dot product of direction and plane vectors
    float dir_mag = sqrt(player->direction.x * player->direction.x + player->direction.y * player->direction.y);
    float plane_mag = sqrt(player->plane.x * player->plane.x + player->plane.y * player->plane.y);
    float dot_product = player->direction.x * player->plane.x + player->direction.y * player->plane.y;

    float cosine_angle = dot_product / (dir_mag * plane_mag);
    float dynamic_buffer = base_speed * (1 - fabs(cosine_angle)); // Reduce buffer as angle approaches 90 degrees
    printf("dynamic buffer %f\n", dynamic_buffer);
    return dynamic_buffer;
}

// void handle_key_a(t_game *game)
// {
//     printf("You just pressed A!\n");

//     float speed = 0.1;

//     // Derive the perpendicular (left) direction vector manually
//     // Assuming player->direction.x and player->direction.y represent the facing direction
//     // Perpendicular vector to the left: (-dir.y, dir.x)
//     float perpX = -game->player->direction.y;  // Opposite of y component
//     float perpY = game->player->direction.x;   // Same as x component

//     // Calculate the new position by moving left to the direction the player is facing
//     float newX = game->player->position.x + perpX * speed;
//     float newY = game->player->position.y + perpY * speed;
//     int mapX = (int)(newX);
//     int mapY = (int)(newY);

//     // Check if the new position is within the map and not blocked by a wall
//     if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL) {
//         game->player->position.x = newX;
//         game->player->position.y = newY;
//         printf("New player position.x = %f\n", game->player->position.x);
//         printf("New player position.y = %f\n", game->player->position.y);
//     } else {
//         printf("Collision/Out of Map movement\n");
//     }
//     print_game_map(game);
// }

void handle_key_a(t_game *game)
{
    printf("You just pressed A!\n");

    float speed = 0.1; // Control the speed of strafing

    // Calculate the left perpendicular vector relative to the player's direction
    // This vector is perpendicular on the left side of the player's current direction
    float perpX = -game->player->direction.y; // Use negative y component of the direction
    float perpY = game->player->direction.x;  // Use x component of the direction

    // Calculate the new position by moving left relative to the current facing direction
    float newX = game->player->position.x + perpX * speed;
    float newY = game->player->position.y + perpY * speed;

    int mapX = (int)(newX);
    int mapY = (int)(newY);

    // Collision detection: Check if the new position is within map bounds and not blocked
    if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL)
    {
        game->player->position.x = newX;
        game->player->position.y = newY;
        printf("New player position.x = %f\n", game->player->position.x);
        printf("New player position.y = %f\n", game->player->position.y);
    }
    else
    {
        printf("Collision detected or Out of Map movement\n");
    }

    // Optionally add visual feedback or further debugging information if needed
    print_game_map(game); // Assuming this function prints the current game map for debugging
}

void handle_key_d(t_game *game)
{
    printf("You just pressed D!\n");

    float speed = 0.1;

    // Derive the perpendicular (right) direction vector manually
    // Assuming player->direction.x and player->direction.y represent the facing direction
    // Perpendicular vector to the right: (dir.y, -dir.x)
    float perpX = game->player->direction.y;  // Same as y component, opposite sign
    float perpY = -game->player->direction.x; // Opposite of x component

    // Calculate the new position by moving right to the direction the player is facing
    float newX = game->player->position.x + perpX * speed;
    float newY = game->player->position.y + perpY * speed;
    int mapX = (int)(newX);
    int mapY = (int)(newY);

    // Check if the new position is within the map and not blocked by a wall
    if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL)
    {
        game->player->position.x = newX;
        game->player->position.y = newY;
        printf("New player position.x = %f\n", game->player->position.x);
        printf("New player position.y = %f\n", game->player->position.y);
    }
    else
    {
        printf("Collision/Out of Map movement\n");
    }
    print_game_map(game);
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


void handle_key_up(t_game *game)
{
    printf("You just pressed Up!\n");
    if (game->player->pitch < 1)
        game->player->pitch += 0.01;
    printf("New pitch %f\n", game->player->pitch);
}

void handle_key_down(t_game *game)
{
    printf("You just pressed Down!\n");
    if (game->player->pitch > -1)
        game->player->pitch -= 0.01;
    printf("New pitch %f\n", game->player->pitch);
}