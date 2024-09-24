/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:11:09 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:03:44 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	setup_bonus_assets(t_game *game)
{
	initialize_game_seed(game);
	initialize_floor_texture_weights(game);
	initialize_floor_texture_map(game);
	initialize_audio(game);
}

void	setup_bonus_scripts(t_game *game)
{
	play_audio_file(game, "audio/menu.mp3", 2);
	add_script(game, menu_background, 5);
	add_script(game, menu_background_voice, 10);
}

void	setup_bonus_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse_move, game);
	mlx_mouse_hook(game->win_ptr, handle_mouse_click, game);
	mlx_hook(game->win_ptr, 5, 1L << 3, handle_mouse_release, game);
}

void	setup_bonus_features(t_game *game)
{
	if (game->bonus)
	{
		setup_bonus_assets(game);
		setup_bonus_scripts(game);
		setup_bonus_hooks(game);
	}
}

int	bonus_game_loop(t_game *game)
{
	if (game->game_sequence == 0)
		bonus_game_loop_0(game);
	else if (game->game_sequence == 1)
		bonus_game_loop_1(game);
	else if (game->game_sequence == 2)
		bonus_game_loop_2(game);
	else if (game->game_sequence == 3)
		bonus_game_loop_3(game);
	else if (game->game_sequence == 4)
		bonus_game_loop_4(game);
	else
		printf("game_sequence error %d\n", \
		game->game_sequence);
	return (0);
}
