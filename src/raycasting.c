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

t_ray_node *addRay(t_ray_node **head)
{
	t_ray_node *newNode = ft_calloc(1, sizeof(t_ray_node));
	if (newNode == NULL)
	{
		printf("Error allocating memory for new node.\n");
		return NULL;
	}

	if (*head == NULL)
	{
		newNode->next = NULL;
		*head = newNode;
	}
	else
	{
		newNode->next = *head;
		*head = newNode;
	}
	return newNode;
}

t_vector2d calculate_floor_coordinates(t_game *game, t_ray_node *center_ray)
{
	t_vector2d floor_coords;
	float rayDirX = center_ray->ray.rayDirX;
	float rayDirY = center_ray->ray.rayDirY;
	float pitch = game->player->pitch;
	float player_height = game->player->height;

	int p = calculate_center_pixel_position(pitch);
	float rowDistance = calculate_floor_distance(p, player_height);
	floor_coords = calculate_raw_floor_coordinates(game, rayDirX, rayDirY, rowDistance);
	floor_coords = clamp_coordinates_to_map(floor_coords, game->map);

	return floor_coords;
}

int calculate_center_pixel_position(float pitch)
{
	int screen_center_y = DEFAULT_S_HEIGHT / 2;
	int pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
	return screen_center_y - (DEFAULT_S_HEIGHT / 2) + pitch_pixel_offset;
}

float calculate_floor_distance(int p, float player_height)
{
	float posZ = 0.5f * DEFAULT_S_HEIGHT * (1.0f + player_height * 2);
	float rowDistance = posZ / p;

	if (rowDistance < 0 || !isfinite(rowDistance))
		rowDistance = MAX_DISTANCE;
	return rowDistance;
}

t_vector2d calculate_raw_floor_coordinates(t_game *game, float rayDirX, float rayDirY, float rowDistance)
{
	t_vector2d floor_coords;
	floor_coords.x = game->player->position.x + rowDistance * rayDirX;
	floor_coords.y = game->player->position.y + rowDistance * rayDirY;
	return floor_coords;
}

t_vector2d clamp_coordinates_to_map(t_vector2d coords, t_map *map)
{
	coords.x = fmax(0, fmin(coords.x, map->width - 1));
	coords.y = fmax(0, fmin(coords.y, map->height - 1));
	return coords;
}
void calculate_and_print_center_ray(t_game *game, t_ray_node *center_ray)
{
	t_vector2d floor_coords = calculate_floor_coordinates(game, center_ray);

	if (center_ray->ray.hit)
	{
		float wallDist = center_ray->ray.perpWallDist;
		floor_coords.x = game->player->position.x + center_ray->ray.rayDirX * wallDist;
		floor_coords.y = game->player->position.y + center_ray->ray.rayDirY * wallDist;
	}
	game->center_floor_coords = floor_coords;
	if (center_ray->ray.hit)
	{
		printf("Wall distance: %.2f\n", center_ray->ray.perpWallDist);
	}
}
t_vector2d get_center_tile_coords(t_game *game)
{
	t_vector2d tile_coords;
	tile_coords.x = floor(game->center_floor_coords.x);
	tile_coords.y = floor(game->center_floor_coords.y);
	return tile_coords;
}


t_ray_node *calculate_rays(t_game *game, t_ray_node *list)
{
	int x;
	t_ray_node *current;
	t_ray_node *center_ray = NULL;

	current = list;
	x = 0;
	while (x < game->screen_width)
	{
		current = addRay(&list);
		if (current != NULL)
		{
			current->ray.x = x;
			run_raycasting_calculation_1(game, current);
			run_raycasting_calculation_2(game, current);
			run_raycasting_calculation_3(game, current);
			if (x == game->screen_width / 2)
				center_ray = current;
		}
		x++;
	}
	if (center_ray != NULL)
		calculate_and_print_center_ray(game, center_ray);
	return (list);
}

void run_raycasting_calculation_1(t_game *game, t_ray_node *current)
{
	calc_camera_x(game, current);
	calc_ray_dir_x(game, current);
	calc_ray_dir_y(game, current);
	calc_map_x(game, current);
	calc_map_y(game, current);
}

void run_raycasting_calculation_2(t_game *game, t_ray_node *current)
{
	calc_side_dist(game, current);
	calc_delta_dist(game, current);
	perform_dda(game, current);
	calc_perp_wall_dist(game, current);
}

void run_raycasting_calculation_3(t_game *game, t_ray_node *current)
{
	calc_wall_hit(game, current);
	calc_texture_x(game, current);
	calc_line_height(game, current);
	calc_draw_parameters(game, current);
}
