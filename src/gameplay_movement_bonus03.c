/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement_bonus03.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:07:34 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:41:09 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_movement_up(t_game *game)
{
	if (game->key_state[K_UP] == 1)
	{
		handle_key_up(game);
	}
}

void	handle_movement_down(t_game *game)
{
	if (game->key_state[K_DOWN] == 1)
	{
		handle_key_down(game);
	}
}

void	handle_key_up(t_game *game)
{
	if (game->player->pitch < 1 && game->bonus && !game->player->is_extracting)
		game->player->pitch += 0.01;
}

void	handle_key_down(t_game *game)
{
	if (game->player->pitch > -1 && game->bonus
		&& !game->player->is_extracting)
		game->player->pitch -= 0.01;
}

void	init_last_pos(int x, int y, int *last_x, int *last_y)
{
	if (*last_x == -1 || *last_y == -1)
	{
		*last_x = x;
		*last_y = y;
	}
}
