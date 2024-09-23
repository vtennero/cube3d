/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:31:12 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:34:31 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_vector2d	calculate_raw_floor_coordinates(t_game *game, \
t_vector2d ray_dir, float rowdist)
{
	t_vector2d	floor_coords;

	floor_coords.x = game->player->position.x + rowdist * ray_dir.x;
	floor_coords.y = game->player->position.y + rowdist * ray_dir.y;
	return (floor_coords);
}

int	calculate_center_pixel_position(float pitch)
{
	int	screen_center_y;
	int	pitch_pixel_offset;

	screen_center_y = DEFAULT_S_HEIGHT / 2;
	pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
	return (screen_center_y - (DEFAULT_S_HEIGHT / 2) + pitch_pixel_offset);
}

float	calculate_floor_distance(int p, float player_height)
{
	float	pos_z;
	float	rowdist;

	pos_z = 0.5f * DEFAULT_S_HEIGHT * (1.0f + player_height * 2);
	rowdist = pos_z / p;
	if (rowdist < 0 || !isfinite(rowdist))
		rowdist = MAX_DISTANCE;
	return (rowdist);
}

t_vector2d	clamp_coordinates_to_map(t_vector2d coords, t_map *map)
{
	coords.x = fmax(0, fmin(coords.x, map->width - 1));
	coords.y = fmax(0, fmin(coords.y, map->height - 1));
	return (coords);
}

t_vector2d	get_center_tile_coords(t_game *game)
{
	t_vector2d	tile_coords;

	tile_coords.x = floor(game->center_floor_coords.x);
	tile_coords.y = floor(game->center_floor_coords.y);
	return (tile_coords);
}
