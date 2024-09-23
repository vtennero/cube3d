/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement_bonus00.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:08:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 15:08:07 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	dash_player(t_game *game, float speed)
{
	float	new_x;
	float	new_y;

	new_x = game->player->position.x + game->player->direction.x * speed;
	new_y = game->player->position.y + game->player->direction.y * speed;
	if (!detect_collision(game, new_x, new_y) && \
	game->player->is_extracting == 0)
	{
		game->player->position.x = new_x;
		game->player->position.y = new_y;
	}
}

void	handle_movement_dash(t_game *game)
{
	if (game->key_state[K_SHIFT] == 1)
	{
		dash_player(game, 0.3);
		game->is_moving_fwd = 1;
	}
}
