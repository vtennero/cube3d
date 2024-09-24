/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_movement00.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:59:54 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:31:15 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

void	handle_key_left(t_game *game)
{
	calculate_rotation(game, -PLAYER_R_ANGLE);
}

void	handle_key_right(t_game *game)
{
	calculate_rotation(game, PLAYER_R_ANGLE);
}
