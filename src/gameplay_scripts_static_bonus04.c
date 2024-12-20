/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_static_bonus04.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:46:31 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:48:58 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	script_skip_enter(t_game *game)
{
	if (game->change_seq == 1 && game->game_sequence < 3)
	{
		game->game_sequence++;
		game->change_seq = 0;
	}
}
