/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:31:06 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:34:11 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_vector2d	calculate_floor_coordinates(t_game *game, t_ray_node *center_ray)
{
	t_vector2d	floor_coords;
	t_vector2d	ray_dir;
	float		player_height;
	int			p;
	float		row_distance;

	ray_dir.x = center_ray->ray.ray_dir_x;
	ray_dir.y = center_ray->ray.ray_dir_y;
	player_height = game->player->height;
	p = calculate_center_pixel_position(game->player->pitch);
	row_distance = calculate_floor_distance(p, player_height);
	floor_coords = calculate_raw_floor_coordinates(game, ray_dir, row_distance);
	floor_coords = clamp_coordinates_to_map(floor_coords, game->map);
	return (floor_coords);
}

void	calculate_and_print_center_ray(t_game *game, t_ray_node *center_ray)
{
	t_vector2d	floor_coords;
	float		wall_dist;

	floor_coords = calculate_floor_coordinates(game, center_ray);
	if (center_ray->ray.hit)
	{
		wall_dist = center_ray->ray.perpwalldist;
		floor_coords.x = game->player->position.x \
		+ center_ray->ray.ray_dir_x * wall_dist;
		floor_coords.y = game->player->position.y \
		+ center_ray->ray.ray_dir_y * wall_dist;
	}
	game->center_floor_coords = floor_coords;
}
