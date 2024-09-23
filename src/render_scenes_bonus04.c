/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scenes_bonus04.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:18:27 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:18:27 by vitenner         ###   ########.fr       */
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
