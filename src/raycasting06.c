/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting06.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:31:31 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:36:53 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_corner_case(t_game *game, t_ray *ray, int next_x, int next_y)
{
	if (game->map->data[next_x][ray->map_y] == 1
		&& game->map->data[ray->map_x][next_y] == 1)
		update_ray_x(ray);
	else if (game->map->data[next_x][ray->map_y] == 1)
		update_ray_y(ray);
	else
	{
		update_ray_x(ray);
	}
}

void	handle_epsilon_case(t_game *game, t_ray *ray)
{
	int	next_x;
	int	next_y;

	next_x = ray->map_x + ray->step_x;
	next_y = ray->map_y + ray->step_y;
	if (is_within_map_bounds(game, next_x, next_y))
	{
		handle_corner_case(game, ray, next_x, next_y);
	}
}

void	move_ray(t_ray *ray)
{
	if (ray->side_d_x < ray->side_d_y)
	{
		ray->side_d_x += ray->delta_d_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_d_y += ray->delta_d_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	set_wall_face(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->wall_face = EAST;
		else
			ray->wall_face = WEST;
	}
	else
	{
		if (ray->step_y > 0)
			ray->wall_face = SOUTH;
		else
			ray->wall_face = NORTH;
	}
}
