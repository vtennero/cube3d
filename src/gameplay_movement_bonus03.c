/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement_bonus03.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:07:34 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 16:10:42 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void handle_movement_dash(t_game *game)
{
	if (game->key_state[K_SHIFT] == 1)
	{
		printf("You just pressed Dash!\n");

		float speed = 0.3;  // Speed of movement, adjust as necessary
		float newX = game->player->position.x + game->player->direction.x * speed;
		float newY = game->player->position.y + game->player->direction.y * speed;

		if (!detect_collision(game, newX, newY) && game->player->is_extracting == 0)
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
