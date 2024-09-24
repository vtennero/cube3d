/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_srikes_bonus03.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:35:51 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:35:56 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	remove_napalm(t_game *game)
{
	game->strike[1].is_active = 0;
}

void	delay_napalm_hit(t_game *game)
{
	game->strike[1].is_active = 1;
}

void	napalm_bombs(t_game *game)
{
	play_random_eagle_call(game);
	add_script(game, delay_napalm_hit, 1);
}

void	napalm_inbound(t_game *game)
{
	game->strike[1].is_launching = 0;
	add_script(game, napalm_bombs, 0);
	play_audio_file(game, "audio/eagles00.mp3", 0);
}
