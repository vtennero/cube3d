/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting07.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:31:38 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:36:15 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calc_side_dist_x(t_game *game, t_ray_node *ray)
{
	if (ray->ray.ray_dir_x == 0)
		ray->ray.delta_d_x = 1e30;
	else
		ray->ray.delta_d_x = fabs(1 / ray->ray.ray_dir_x);
	if (ray->ray.ray_dir_x < 0)
	{
		ray->ray.step_x = -1;
		ray->ray.side_d_x = (game->player->position.x - ray->ray.map_x) \
		* ray->ray.delta_d_x;
	}
	else
	{
		ray->ray.step_x = 1;
		ray->ray.side_d_x = (ray->ray.map_x + 1.0 - game->player->position.x) \
		* ray->ray.delta_d_x;
	}
}

void	calc_side_dist_y(t_game *game, t_ray_node *ray)
{
	if (ray->ray.ray_dir_y == 0)
		ray->ray.delta_d_y = 1e30;
	else
		ray->ray.delta_d_y = fabs(1 / ray->ray.ray_dir_y);
	if (ray->ray.ray_dir_y < 0)
	{
		ray->ray.step_y = -1;
		ray->ray.side_d_y = (game->player->position.y - ray->ray.map_y) \
		* ray->ray.delta_d_y;
	}
	else
	{
		ray->ray.step_y = 1;
		ray->ray.side_d_y = (ray->ray.map_y + 1.0 - game->player->position.y) \
		* ray->ray.delta_d_y;
	}
}

void	calc_side_dist(t_game *game, t_ray_node *ray)
{
	calc_side_dist_x(game, ray);
	calc_side_dist_y(game, ray);
}

void	calc_delta_dist(t_game *game, t_ray_node *ray)
{
	(void)game;
	if (ray->ray.ray_dir_x == 0)
		ray->ray.delta_d_x = 1e30;
	else
		ray->ray.delta_d_x = fabs(1 / ray->ray.ray_dir_x);
	if (ray->ray.ray_dir_y == 0)
		ray->ray.delta_d_y = 1e30;
	else
		ray->ray.delta_d_y = fabs(1 / ray->ray.ray_dir_y);
}
