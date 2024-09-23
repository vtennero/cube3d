/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting08.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:31:43 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:36:29 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calc_camera_x(t_game *game, t_ray_node *ray)
{
	ray->ray.camera_x = 2 * ray->ray.x / (double)(game->screen_width) - 1;
}

void	calc_ray_dir_x(t_game *game, t_ray_node *ray)
{
	ray->ray.ray_dir_x = game->player->direction.x + game->player->plane.x * \
	ray->ray.camera_x;
}

void	calc_ray_dir_y(t_game *game, t_ray_node *ray)
{
	ray->ray.ray_dir_y = game->player->direction.y + game->player->plane.y * \
	ray->ray.camera_x;
}

void	calc_map_x(t_game *game, t_ray_node *ray)
{
	ray->ray.map_x = (int)game->player->position.x;
}

void	calc_map_y(t_game *game, t_ray_node *ray)
{
	ray->ray.map_y = (int)game->player->position.y;
}
