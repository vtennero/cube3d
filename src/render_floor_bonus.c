/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:41:48 by toto              #+#    #+#             */
/*   Updated: 2024/05/10 16:26:55 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_floor_texture_color(t_texture *texture, int x, int y)
{
	int	index;

	if (!texture || !texture->data)
	{
		printf("Error: Invalid texture in get_floor_texture_color\n");
		return (0);
	}
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	index = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
	if (index < 0 || index >= texture->tex_line_len * texture->height)
	{
		printf("Error: Texture index out of bounds: %d\n", index);
		return (0);
	}
	return (*(int *)(texture->data + index));
}

void	initialize_floor_texture_weights(t_game *game)
{
	float	weights[8];
	float	total_weight;
	int		i;

	weights[0] = 0.20;
	weights[1] = 0.20;
	weights[2] = 0.20;
	weights[3] = 0.20;
	weights[4] = 0.05;
	weights[5] = 0.05;
	weights[6] = 0.05;
	weights[7] = 0.05;
	game->num_floor_textures = MAX_FLOOR_TEXTURES;
	total_weight = 0;
	i = 0;
	while (i < game->num_floor_textures)
	{
		total_weight += weights[i];
		i++;
	}
	i = 0;
	while (i < game->num_floor_textures)
	{
		game->floor_texture_weights[i].weight = weights[i] / total_weight;
		game->floor_texture_weights[i].texture_index = i;
		i++;
	}
}

int	select_weighted_texture(t_game *game)
{
	double	random;
	double	cumulative;
	int		i;

	if (game->num_floor_textures <= 0)
	{
		printf("Error: No floor textures available\n");
		return (0);
	}
	random = (double)rand() / RAND_MAX;
	cumulative = 0;
	i = 0;
	while (i < game->num_floor_textures)
	{
		cumulative += game->floor_texture_weights[i].weight;
		if (random <= cumulative)
			return (i);
		i++;
	}
	return (0);
}
int	**allocate_floor_texture_map(t_game *game)
{
	int	**floor_texture_map;
	int	y;

	floor_texture_map = malloc(game->map->height * sizeof(int *));
	if (floor_texture_map == NULL)
	{
		printf("Failed to allocate memory for floor_texture_map\n");
		cleanup(game);
	}
	y = 0;
	while (y < game->map->height)
	{
		floor_texture_map[y] = malloc(game->map->width * sizeof(int));
		if (floor_texture_map[y] == NULL)
		{
			printf("Failed to allocate memory for floor_texture_map row %d\n", y);
			cleanup(game);
		}
		y++;
	}
	return (floor_texture_map);
}

void	fill_floor_texture_map(t_game *game)
{
	int	y;
	int	x;
	int	selected_texture;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			selected_texture = select_weighted_texture(game);
			game->floor_texture_map[y][x] = selected_texture;
			x++;
		}
		y++;
	}
}

void	initialize_floor_texture_map(t_game *game)
{
	game->floor_texture_map = allocate_floor_texture_map(game);
	fill_floor_texture_map(game);
}

int get_floor_texture_index(t_game *game, int cellX, int cellY)
{
	if (cellX >= 0 && cellX < game->map->width && cellY >= 0 && cellY < game->map->height)
	{
		return game->floor_texture_map[cellY][cellX];
	}
	return -1;
}

t_texture* get_floor_texture(t_game *game, int texture_index)
{
	if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
	{
		return &game->floortextures[texture_index];
	}
	return NULL;
}

int validate_game_state(t_game *game)
{
	if (!game || !game->player || !game->map || !game->floor_texture_map)
	{
		printf("Error: Invalid game state in render_floor\n");
		return 0;
	}
	return 1;
}

int calculate_floor_start(t_game *game)
{
	float pitch = game->player->pitch;
	int pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
	int horizon = DEFAULT_S_HEIGHT / 2;
	int floor_start = horizon - pitch_pixel_offset;
	return (floor_start < 0) ? 0 : (floor_start >= DEFAULT_S_HEIGHT ? DEFAULT_S_HEIGHT - 1 : floor_start);
}

void render_floor(t_game *game)
{
	if (!validate_game_state(game)) {
		return;
	}

	int floor_start = calculate_floor_start(game);
	t_floor_ray floor_ray;

	for (int y = floor_start; y < DEFAULT_S_HEIGHT; y++)
	{
		calculate_floor_ray_params(game, &floor_ray, y);
		render_floor_line(game, &floor_ray, y);
	}
}

void calculate_texture_coordinates(t_texture *texture, t_vector2d floor, float *tx, float *ty)
{
	t_vector2d frac;
	frac.x = floor.x - floorf(floor.x);
	frac.y = floor.y - floorf(floor.y);

	*tx = fmodf(frac.x * texture->width, texture->width);
	*ty = fmodf(frac.y * texture->height, texture->height);

	if (*tx < 0) *tx += texture->width;
	if (*ty < 0) *ty += texture->height;
}

int calculate_floor_pixel_color(t_game *game, t_vector2d floor)
{
	int cellX = (int)floor.x;
	int cellY = (int)floor.y;

	int texture_index = get_floor_texture_index(game, cellX, cellY);
	t_texture *current_texture = get_floor_texture(game, texture_index);

	if (current_texture && current_texture->data)
	{
		float tx, ty;
		calculate_texture_coordinates(current_texture, floor, &tx, &ty);
		return get_floor_texture_color(current_texture, (int)tx, (int)ty);
	}

	return 0x707070;
}

void render_floor_line(t_game *game, t_floor_ray *floor_ray, int y)
{
	for (int x = 0; x < DEFAULT_S_WIDTH; x++)
	{
		int color = calculate_floor_pixel_color(game, floor_ray->floor);
		img_pix_put(&game->img, x, y, color);

		floor_ray->floor.x += floor_ray->floorStep.x;
		floor_ray->floor.y += floor_ray->floorStep.y;
	}
}

void calculate_floor_ray_params(t_game *game, t_floor_ray *floor_ray, int y)
{
	float pitch = game->player->pitch;
	float player_height = game->player->height;
	int horizon = DEFAULT_S_HEIGHT / 2;
	int pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
	int p = y - horizon + pitch_pixel_offset;
	float posZ = 0.5f * DEFAULT_S_HEIGHT * (1.0f + player_height * 2);

	floor_ray->rayDir0.x = game->player->direction.x - game->player->plane.x;
	floor_ray->rayDir0.y = game->player->direction.y - game->player->plane.y;
	floor_ray->rayDir1.x = game->player->direction.x + game->player->plane.x;
	floor_ray->rayDir1.y = game->player->direction.y + game->player->plane.y;

	floor_ray->rowDistance = posZ / p;

	floor_ray->floorStep.x = floor_ray->rowDistance * (floor_ray->rayDir1.x - floor_ray->rayDir0.x) / DEFAULT_S_WIDTH;
	floor_ray->floorStep.y = floor_ray->rowDistance * (floor_ray->rayDir1.y - floor_ray->rayDir0.y) / DEFAULT_S_WIDTH;

	floor_ray->floor.x = game->player->position.x + floor_ray->rowDistance * floor_ray->rayDir0.x;
	floor_ray->floor.y = game->player->position.y + floor_ray->rowDistance * floor_ray->rayDir0.y;
}
