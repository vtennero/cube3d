/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_scripts_strikes_bonus00.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:45:33 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:36:47 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_key_1(t_game *game)
{
	game->key_state[K_1] = 1;
	if (game->strike[0].is_launching == 0 && game->strike[0].is_active \
		== 0 && game->game_sequence == 3)
	{
		printf("launching eagle strike at %f, %f\n", \
		game->center_floor_coords.y, game->center_floor_coords.x);
		game->strike[0].position.y = game->center_floor_coords.y;
		game->strike[0].position.x = game->center_floor_coords.x;
		game->strike[0].is_launching = 1;
		play_random_strike_sound(game);
		add_script(game, eagle_inbound, 3);
	}
}

void	handle_key_2(t_game *game)
{
	game->key_state[K_2] = 1;
	if (game->strike[1].is_launching == 0 && game->strike[1].is_active \
		== 0 && game->game_sequence == 3)
	{
		printf("launching napalm strike at %f, %f\n", \
		game->center_floor_coords.y, game->center_floor_coords.x);
		game->strike[1].position.y = game->center_floor_coords.y;
		game->strike[1].position.x = game->center_floor_coords.x;
		game->strike[1].is_launching = 1;
		play_random_strike_sound(game);
		add_script(game, napalm_inbound, 3);
		add_script(game, remove_napalm, 15);
	}
}

void	handle_key_3(t_game *game)
{
	game->key_state[K_3] = 1;
	if (game->strike[2].is_launching == 0
		&& game->strike[2].is_active == 0
		&& game->game_sequence == 3)
	{
		printf("Launching barrage %f, %f\n",
			game->center_floor_coords.y, game->center_floor_coords.x);
		game->strike[2].position.y = game->center_floor_coords.y;
		game->strike[2].position.x = game->center_floor_coords.x;
		game->strike[2].base_position.y = game->center_floor_coords.y;
		game->strike[2].base_position.x = game->center_floor_coords.x;
		game->strike[2].is_launching = 1;
		play_audio_file(game, "audio/orbitalcall.mp3", 0);
		add_script(game, barrage_inbound, BARRAGE_CALL_IN_TIME);
		add_script(game, stop_barrage, BARRAGE_DURATION);
	}
}
