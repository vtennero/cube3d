/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement00.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:59:54 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 17:02:57 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_movement_left(t_game *game)
{
	if (game->key_state[K_LEFT] == 1)
	{
		handle_key_left(game);
	}
}

void	handle_movement_right(t_game *game)
{
	if (game->key_state[K_RIGHT] == 1)
	{
		handle_key_right(game);
	}
}

void	handle_movement_forward(t_game *game)
{
	if (game->key_state[K_W] == 1)
	{
		handle_key_w(game);
	}
}

void	handle_movement_backward(t_game *game)
{
	if (game->key_state[K_S] == 1)
	{
		handle_key_s(game);
	}
}

void	handle_movement_strafe_left(t_game *game)
{
	if (game->key_state[K_A] == 1)
	{
		handle_key_a(game);
	}
}

void	handle_movement_strafe_right(t_game *game)
{
	if (game->key_state[K_D] == 1)
	{
		handle_key_d(game);
	}
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode < KEY_MAX)
	{
		game->key_state[keycode] = 0;
		if (keycode != K_E)
			game->is_moving_fwd = 0;
	}
	return (0);
}

int	ft_key_press(int keycode, t_game *game)
{
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

static void	update_player_position(t_game *game, float newX, float newY)
{
	game->player->position.x = newX;
	game->player->position.y = newY;
}

void	handle_key_w(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player->position.x \
	+ game->player->direction.x * PLAYER_M_SPEED;
	new_y = game->player->position.y \
	+ game->player->direction.y * PLAYER_M_SPEED;
	if (!detect_collision(game, new_x, new_y) \
	&& game->player->is_extracting == 0)
		update_player_position(game, new_x, new_y);
	game->is_moving_fwd = 1;
}

void	handle_key_s(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player->position.x \
	- game->player->direction.x * PLAYER_M_SPEED;
	new_y = game->player->position.y \
	- game->player->direction.y * PLAYER_M_SPEED;
	if (!detect_collision(game, new_x, new_y) \
	&& game->player->is_extracting == 0)
		update_player_position(game, new_x, new_y);
	game->is_moving_fwd = 1;
}

void	handle_key_a(t_game *game)
{
	float	perp_x;
	float	perp_y;
	float	new_x;
	float	new_y;

	perp_x = game->player->direction.y;
	perp_y = -game->player->direction.x;
	new_x = game->player->position.x + perp_x * PLAYER_M_SPEED;
	new_y = game->player->position.y + perp_y * PLAYER_M_SPEED;
	if (!detect_collision(game, new_x, new_y) \
	&& game->player->is_extracting == 0)
		update_player_position(game, new_x, new_y);
}

void	handle_key_d(t_game *game)
{
	float	perp_x;
	float	perp_y;
	float	new_x;
	float	new_y;

	perp_x = -game->player->direction.y;
	perp_y = game->player->direction.x;
	new_x = game->player->position.x + perp_x * PLAYER_M_SPEED;
	new_y = game->player->position.y + perp_y * PLAYER_M_SPEED;
	if (!detect_collision(game, new_x, new_y) \
	&& game->player->is_extracting == 0)
		update_player_position(game, new_x, new_y);
}

void	handle_key_left(t_game *game)
{
	calculate_rotation(game, -PLAYER_R_ANGLE);
}

void	handle_key_right(t_game *game)
{
	calculate_rotation(game, PLAYER_R_ANGLE);
}
