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

int ft_key_press(int keycode, t_game *game)
{
    printf("ft_key_press %d\n", keycode);
    if (keycode < MAX_KEY_CODE)
    {
        game->key_state[keycode] = 1;
    }
    return (0);
}

int ft_key_release(int keycode, t_game *game)
{
    if (keycode < MAX_KEY_CODE)
    {
        game->key_state[keycode] = 0;
    }
    return (0);
}

void handle_movement_left(t_game *game)
{
    if (game->key_state[K_LEFT] == 1)
    { // Check if left key is pressed
        handle_key_left(game);
    }
}

void handle_movement_right(t_game *game)
{
    if (game->key_state[K_RIGHT] == 1)
    { // Check if right key is pressed
        handle_key_right(game);
    }
}

void handle_movement_up(t_game *game)
{
    if (game->key_state[K_UP] == 1)
    {
        handle_key_up(game);
    }
}

void handle_movement_down(t_game *game)
{
    if (game->key_state[K_DOWN] == 1)
    {
        handle_key_down(game);
    }
}

void handle_movement_forward(t_game *game)
{
    if (game->key_state[K_W] == 1)
    { // Check if W key is pressed
        handle_key_w(game);
    }
}

void handle_movement_backward(t_game *game)
{
    if (game->key_state[K_S] == 1)
    { // Check if S key is pressed
        handle_key_s(game);
    }
}

void handle_movement_strafe_left(t_game *game)
{
    if (game->key_state[K_A] == 1)
    { // Check if A key is pressed
        handle_key_a(game);
    }
}

void handle_movement_strafe_right(t_game *game)
{
    if (game->key_state[K_D] == 1)
    { // Check if D key is pressed
        handle_key_d(game);
    }
}

void handle_movement_dash(t_game *game)
{
    if (game->key_state[K_SHIFT] == 1)
    { // Check if sfhit key is pressed
        printf("You just pressed Dasshhh!\n");

        float speed = 0.8;  // Speed of movement, adjust as necessary
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
        print_game_map(game);
    }
}