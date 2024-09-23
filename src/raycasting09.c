/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting09.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:31:51 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:36:51 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_within_map_bounds(t_game *game, int x, int y)
{
	if (x >= 0 && x < game->map->width && y >= 0 && y < game->map->height)
		return (1);
	else
		return (0);
}

int	is_out_of_bounds(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= game->map->width \
	|| ray->map_y < 0 || ray->map_y >= game->map->height)
		return (1);
	else
		return (0);
}
void	update_ray_x(t_ray *ray)
{
	ray->side_d_x += ray->delta_d_x;
	ray->map_x += ray->step_x;
	ray->side = 0;
}

void	update_ray_y(t_ray *ray)
{
	ray->side_d_y += ray->delta_d_y;
	ray->map_y += ray->step_y;
	ray->side = 1;
}
