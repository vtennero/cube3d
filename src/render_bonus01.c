/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:01:53 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:02:01 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	run_dmg_script(t_game *game)
{
	script_strike_player(game);
	script_napalm_enemies(game, 1, 6);
	script_napalm_player(game, 1, 6);
	player_burning(game);
	player_need_stims(game);
	script_barrage_enemies(game);
	script_barrage_player(game);
	script_die(game);
	script_strike_enemies(game, 0, 5);
}

void	run_collectible_script(t_game *game)
{
	script_found_sth(game);
	script_found_supplies(game);
	script_take_supplies(game);
}

void	run_game_end_scripts(t_game *game)
{
	script_board(game);
	script_takeoff(game);
}

void	run_misc_enemies_scripts(t_game *game)
{
	game->num_enemies = calculate_enemy_count(game);
	relocate_enemies(game);
	enemies_hit(game);
	update_scripts(game);
	check_enemy_at_center(game);
	randomize_dead_enemy_positions(game);
	update_gun_state(game);
}
