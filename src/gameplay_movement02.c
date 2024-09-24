/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:30:03 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:31:12 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_player_position(t_game *game, float new_x, float new_y)
{
	game->player->position.x = new_x;
	game->player->position.y = new_y;
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
