/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting05.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:31:26 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:35:26 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_wall(t_game *game, int map_y, int map_x)
{
	if (game->map->data[map_y][map_x] == 1)
		return (1);
	else
		return (0);
}

int	is_space_to_wall_transition(t_game *game, t_ray *ray, \
int prev_map_x, int prev_map_y)
{
	if ((prev_map_x != ray->map_x || prev_map_y != ray->map_y)
		&& !is_wall(game, prev_map_y, prev_map_x)
		&& is_wall(game, ray->map_y, ray->map_x))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	adjust_ray_position(t_ray *ray, int *prev_map_x, int *prev_map_y)
{
	if (ray->side == 0)
	{
		ray->side_d_x -= ray->delta_d_x;
		ray->map_x = *prev_map_x;
	}
	else
	{
		ray->side_d_y -= ray->delta_d_y;
		ray->map_y = *prev_map_y;
	}
}

int	check_wall_hit(t_game *game, t_ray *ray, int *prev_map_x, int *prev_map_y)
{
	if (is_wall(game, ray->map_y, ray->map_x))
	{
		set_wall_face(ray);
		return (1);
	}
	else if (is_space_to_wall_transition(game, ray, *prev_map_x, *prev_map_y))
	{
		adjust_ray_position(ray, prev_map_x, prev_map_y);
		return (1);
	}
	*prev_map_x = ray->map_x;
	*prev_map_y = ray->map_y;
	return (0);
}

void	perform_dda(t_game *game, t_ray_node *ray)
{
	int	hit;
	int	step_count;
	int	prev_map_x;
	int	prev_map_y;

	hit = 0;
	step_count = 0;
	prev_map_x = ray->ray.map_x;
	prev_map_y = ray->ray.map_y;
	while (hit == 0 && step_count < 100)
	{
		if (is_out_of_bounds(game, &ray->ray))
		{
			hit = 1;
			break ;
		}
		if (fabs(ray->ray.side_d_x - ray->ray.side_d_y) < RAY_EPSILON)
			handle_epsilon_case(game, &ray->ray);
		else
			move_ray(&ray->ray);
		hit = check_wall_hit(game, &ray->ray, &prev_map_x, &prev_map_y);
		step_count++;
	}
}
