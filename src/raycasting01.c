/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:30:59 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:33:27 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	run_raycasting_calculation_1(t_game *game, t_ray_node *current)
{
	calc_camera_x(game, current);
	calc_ray_dir_x(game, current);
	calc_ray_dir_y(game, current);
	calc_map_x(game, current);
	calc_map_y(game, current);
}

void	run_raycasting_calculation_2(t_game *game, t_ray_node *current)
{
	calc_side_dist(game, current);
	calc_delta_dist(game, current);
	perform_dda(game, current);
	calc_perp_wall_dist(game, current);
}

void	run_raycasting_calculation_3(t_game *game, t_ray_node *current)
{
	calc_wall_hit(game, current);
	calc_texture_x(game, current);
	calc_line_height(game, current);
	calc_draw_parameters(game, current);
}

void	run_raycasting_calculations(t_game *game, t_ray_node *current)
{
	run_raycasting_calculation_1(game, current);
	run_raycasting_calculation_2(game, current);
	run_raycasting_calculation_3(game, current);
}
