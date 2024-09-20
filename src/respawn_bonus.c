/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   respawn_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:12:58 by vitenner          #+#    #+#             */
/*   Updated: 2024/08/27 17:33:45 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_respawn(t_game *game)
{
	if (game->player->is_dead)
	{
		game->game_sequence = 2;
		respawn_player(game);
	}
}
