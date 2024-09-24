/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:03:08 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:04:44 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	bonus_game_loop_0(t_game *game)
{
	script_skip_enter(game);
	update_scripts(game);
	handle_key_esc(game);
	render_menu(game);
	mlx_put_image_to_window(game->mlx_ptr, \
	game->win_ptr, game->img.mlx_img, 0, 0);
	return (0);
}

int	bonus_game_loop_1(t_game *game)
{
	script_skip_enter(game);
	handle_key_esc(game);
	render_opening(game);
	mlx_put_image_to_window(game->mlx_ptr, \
	game->win_ptr, game->img.mlx_img, 0, 0);
	return (0);
}

int	bonus_game_loop_2(t_game *game)
{
	script_skip_enter(game);
	handle_key_esc(game);
	render_land(game);
	mlx_put_image_to_window(game->mlx_ptr, \
	game->win_ptr, game->img.mlx_img, 0, 0);
	return (0);
}

int	bonus_game_loop_3(t_game *game)
{
	game->ray_list = calculate_rays(game, game->ray_list);
	run_dmg_script(game);
	run_collectible_script(game);
	run_game_end_scripts(game);
	run_misc_enemies_scripts(game);
	run_keystroke_handlers(game);
	run_bonus_rendering(game);
	mlx_put_image_to_window(game->mlx_ptr, \
	game->win_ptr, game->img.mlx_img, 0, 0);
	clean_rays(game);
	return (0);
}

int	bonus_game_loop_4(t_game *game)
{
	handle_key_esc(game);
	render_outro(game);
	update_scripts(game);
	mlx_put_image_to_window(game->mlx_ptr, \
	game->win_ptr, game->img.mlx_img, 0, 0);
	return (0);
}
