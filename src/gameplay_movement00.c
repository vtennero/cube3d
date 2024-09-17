/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement00.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:59:54 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/17 15:17:33 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void handle_movement_left(t_game *game)
{
	if (game->key_state[K_LEFT] == 1)
	{
		handle_key_left(game);
	}
}

void handle_movement_right(t_game *game)
{
	if (game->key_state[K_RIGHT] == 1)
	{
		handle_key_right(game);
	}
}

void handle_movement_forward(t_game *game)
{
	if (game->key_state[K_W] == 1)
	{
		handle_key_w(game);
	}
}

void handle_movement_backward(t_game *game)
{
	if (game->key_state[K_S] == 1)
	{
		handle_key_s(game);
	}
}

void handle_movement_strafe_left(t_game *game)
{
	if (game->key_state[K_A] == 1)
	{
		handle_key_a(game);
	}
}

void handle_movement_strafe_right(t_game *game)
{
	if (game->key_state[K_D] == 1)
	{
		handle_key_d(game);
	}
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

int ft_key_press(int keycode, t_game *game)
{
	printf("ft_key_press %d\n", keycode);
		if (keycode == K_E && game->key_state[K_E] == 0 && game->bonus)
			handle_key_e(game);
		else if (keycode == K_ENTER && game->key_state[K_ENTER] == 0 && game->bonus)
			handle_key_enter(game);
		else if (keycode == K_1 && game->key_state[K_1] == 0 && game->bonus)
			handle_key_1(game);
		else if (keycode == K_2 && game->key_state[K_2] == 0 && game->bonus)
			handle_key_2(game);
		else if (keycode == K_3 && game->key_state[K_3] == 0 && game->bonus)
				handle_key_3(game);
		else
			game->key_state[keycode] = 1;
	return (0);
}

static void update_player_position(t_game *game, float newX, float newY)
{
	game->player->position.x = newX;
	game->player->position.y = newY;
}
void handle_key_w(t_game *game)
{
	float speed = 0.1;  // Speed of movement, adjust as necessary
	float newX = game->player->position.x + game->player->direction.x * speed;
	float newY = game->player->position.y + game->player->direction.y * speed;
	if (!detect_collision(game, newX, newY) && game->player->is_extracting == 0)
		update_player_position(game, newX, newY);
	game->is_moving_fwd = 1;
}

void handle_key_s(t_game *game)
{
	float speed = 0.1;  // Speed of movement, adjust as necessary
	float newX = game->player->position.x - game->player->direction.x * speed;
	float newY = game->player->position.y - game->player->direction.y * speed;
	if (!detect_collision(game, newX, newY) && game->player->is_extracting == 0)
		update_player_position(game, newX, newY);
	game->is_moving_fwd = 1;
}
void handle_key_a(t_game *game)
{

	float speed = 0.1; // Control the speed of strafing

	float perpX = game->player->direction.y; // Use positive y component of the direction
	float perpY = -game->player->direction.x; // Use negative x component of the direction

	float newX = game->player->position.x + perpX * speed;
	float newY = game->player->position.y + perpY * speed;

	if (!detect_collision(game, newX, newY)  && game->player->is_extracting == 0)
		update_player_position(game, newX, newY);
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

	if (!detect_collision(game, newX, newY)  && game->player->is_extracting == 0)
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
	float angle = -0.0872665; // -5 degrees in radians (counterclockwise)
	calculate_rotation(game, angle);
}

void handle_key_right(t_game *game)
{
	float angle = 0.0872665; // 5 degrees in radians (clockwise)
	calculate_rotation(game, angle);
}
