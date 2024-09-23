/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:49:22 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/17 12:27:19 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_ray_node	*add_ray(t_ray_node **head)
{
	t_ray_node	*new;

	new = ft_calloc(1, sizeof(t_ray_node));
	if (new == NULL)
	{
		printf("Error allocating memory for new node.\n");
		return (NULL);
	}
	if (*head == NULL)
	{
		new->next = NULL;
		*head = new;
	}
	else
	{
		new->next = *head;
		*head = new;
	}
	return (new);
}

t_vector2d	calculate_raw_floor_coordinates(t_game *game, \
t_vector2d ray_dir, float rowdist)
{
	t_vector2d	floor_coords;

	floor_coords.x = game->player->position.x + rowdist * ray_dir.x;
	floor_coords.y = game->player->position.y + rowdist * ray_dir.y;
	return (floor_coords);
}

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

t_vector2d	get_center_tile_coords(t_game *game)
{
	t_vector2d	tile_coords;

	tile_coords.x = floor(game->center_floor_coords.x);
	tile_coords.y = floor(game->center_floor_coords.y);
	return (tile_coords);
}

t_ray_node	*calculate_rays(t_game *game, t_ray_node *list)
{
	int			x;
	t_ray_node	*current;
	t_ray_node	*center_ray;

	current = list;
	center_ray = NULL;
	x = 0;
	while (x < game->screen_width)
	{
		current = add_ray(&list);
		if (current != NULL)
		{
			current->ray.x = x;
			run_raycasting_calculations(game, current);
			if (x == game->screen_width / 2)
				center_ray = current;
		}
		x++;
	}
	if (center_ray != NULL)
	{
		calculate_and_print_center_ray(game, center_ray);
	}
	return (list);
}

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
