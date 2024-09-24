/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:29:57 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:30:22 by vitenner         ###   ########.fr       */
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
