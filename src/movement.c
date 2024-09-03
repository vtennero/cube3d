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

void handle_space_shoot(t_game *game)
{
    if (game->key_state[K_SPACE] == 1)
    { 
        game->is_shooting = 1;
    }
}


int ft_key_press(int keycode, t_game *game)
{
    printf("ft_key_press %d\n", keycode);
    if (keycode < MAX_KEY_CODE)
    {
        if (keycode == K_E)
        {
            // Only set the state if it's not already set
            if (game->key_state[K_E] == 0)
            {
                game->key_state[K_E] = 1;
                handle_key_e(game);  // Call the handler immediately
            }
        }
        else if (keycode == K_ENTER)
        {
            if (game->key_state[K_ENTER] == 0)
            {
                game->key_state[K_ENTER] = 1;
                handle_key_enter(game);  // Call the handler immediately
            }
        }
        else if (keycode == K_2)
        {
            if (game->key_state[K_2] == 0)
            {
                game->key_state[K_2] = 1;
                handle_key_2(game);  // Call the handler immediately
            }
        }
        else
        {
            game->key_state[keycode] = 1;
        }
    }
    return (0);
}

int ft_key_release(int keycode, t_game *game)
{
    if (keycode < MAX_KEY_CODE)
    {
        game->key_state[keycode] = 0;
        if (keycode != K_E)  // Don't reset is_moving_fwd for E key
        {
            game->is_moving_fwd = 0;
        }
    }
    return (0);
}

