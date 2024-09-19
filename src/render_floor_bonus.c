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


int get_floor_texture_color(t_texture *texture, int x, int y)
{
	if (!texture || !texture->data)
	{
		printf("Error: Invalid texture in get_floor_texture_color\n");
		return 0;
	}

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
	{
		// printf("Error: Texture coordinates out of bounds: x=%d, y=%d, texture size=%dx%d\n",
		// x, y, texture->width, texture->height);
		return 0;
	}

	int index = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
	if (index < 0 || index >= texture->tex_line_len * texture->height)
	{
		// debug_texture(texture, x, y);
		printf("Error: Texture index out of bounds: %d\n", index);
		return 0;
	}

	return *(int *)(texture->data + index);
}

void initialize_floor_texture_weights(t_game *game)
{
	float weights[] = {0.20, 0.20, 0.20, 0.20, 0.05, 0.05, 0.05, 0.05};
	game->num_floor_textures = MAX_FLOOR_TEXTURES;

	float total_weight = 0;
	for (int i = 0; i < game->num_floor_textures; i++)
	{
		total_weight += weights[i];
	}

	for (int i = 0; i < game->num_floor_textures; i++)
	{
		game->floor_texture_weights[i].weight = weights[i] / total_weight;
		game->floor_texture_weights[i].texture_index = i;
	}
}

int select_weighted_texture(t_game *game)
{
	if (game->num_floor_textures <= 0)
	{
		printf("Error: No floor textures available\n");
		return 0;
	}

	double random = (double)rand() / RAND_MAX;
	double cumulative = 0;
	for (int i = 0; i < game->num_floor_textures; i++)
	{
		cumulative += game->floor_texture_weights[i].weight;
		if (random <= cumulative)
		{
			return i;
		}
	}
	return 0; // Fallback to first texture if something goes wrong
}

void initialize_floor_texture_map(t_game *game)
{

	if (game->floor_texture_map != NULL)
	{
		printf("floor_texture_map is already allocated. Freeing existing memory.\n");
		for (int y = 0; y < game->map->height; y++)
		{
			free(game->floor_texture_map[y]);
		}
		free(game->floor_texture_map);
	}

	game->floor_texture_map = malloc(game->map->height * sizeof(int *));
	if (game->floor_texture_map == NULL)
	{
		printf("Failed to allocate memory for floor_texture_map\n");
		exit(EXIT_FAILURE);
	}

	for (int y = 0; y < game->map->height; y++)
	{
		game->floor_texture_map[y] = malloc(game->map->width * sizeof(int));
		if (game->floor_texture_map[y] == NULL)
		{
			printf("Failed to allocate memory for floor_texture_map row %d\n", y);
			// Free previously allocated rows
			for (int i = 0; i < y; i++)
			{
				free(game->floor_texture_map[i]);
			}
			free(game->floor_texture_map);
			exit(EXIT_FAILURE);
		}

		for (int x = 0; x < game->map->width; x++)
		{
			int selected_texture = select_weighted_texture(game);
			game->floor_texture_map[y][x] = selected_texture;
			// printf("Assigned texture %d at position (%d, %d)\n", selected_texture, x, y);
		}
	}
}


// void render_floor_pixel(t_game *game, int x, int y, float floorX, float floorY)
// {
// 	int cellX = (int)floorX;
// 	int cellY = (int)floorY;

// 	if (cellX >= 0 && cellX < game->map->width && cellY >= 0 && cellY < game->map->height)
// 	{
// 		int texture_index = game->floor_texture_map[cellY][cellX];

// 		if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
// 		{
// 			t_texture *current_texture = &game->floortextures[texture_index];

// 			float fracX = floorX - cellX;
// 			float fracY = floorY - cellY;

// 			// Use fmodf to ensure we're always within texture bounds
// 			int tx = (int)(fmodf(fracX * current_texture->width, current_texture->width));
// 			int ty = (int)(fmodf(fracY * current_texture->height, current_texture->height));

// 			// Ensure tx and ty are always non-negative
// 			tx = (tx + current_texture->width) % current_texture->width;
// 			ty = (ty + current_texture->height) % current_texture->height;

// 			int color = get_floor_texture_color(current_texture, tx, ty);
// 			img_pix_put(&game->img, x, y, color);
// 		}
// 		else
// 		{
// 			img_pix_put(&game->img, x, y, 0xFF0000); // Red for invalid texture index
// 		}
// 	}
// 	else
// 	{
// 		img_pix_put(&game->img, x, y, 0x0000FF); // Blue for out-of-bounds
// 	}
// }

// void render_floor(t_game *game)
// {
// 	if (!game || !game->player || !game->map || !game->floor_texture_map)
// 	{
// 		printf("Error: Invalid game state in render_floor\n");
// 		return;
// 	}

// 	float pitch = game->player->pitch;
// 	int pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
// 	float player_height = game->player->height;  // Use player's height

// 	int horizon = DEFAULT_S_HEIGHT / 2;
// 	int floor_start = horizon - pitch_pixel_offset;
// 	floor_start = (floor_start < 0) ? 0 : (floor_start >= DEFAULT_S_HEIGHT ? DEFAULT_S_HEIGHT - 1 : floor_start);

// 	for (int y = floor_start; y < DEFAULT_S_HEIGHT; y++)
// 	{
// 		float rayDirX0 = game->player->direction.x - game->player->plane.x;
// 		float rayDirY0 = game->player->direction.y - game->player->plane.y;
// 		float rayDirX1 = game->player->direction.x + game->player->plane.x;
// 		float rayDirY1 = game->player->direction.y + game->player->plane.y;

// 		int p = y - horizon + pitch_pixel_offset;
// 		float posZ = 0.5f * DEFAULT_S_HEIGHT * (1.0f + player_height*2);  // Adjust for player height

// 		float rowDistance = posZ / p;

// 		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / DEFAULT_S_WIDTH;
// 		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / DEFAULT_S_WIDTH;

// 		float floorX = game->player->position.x + rowDistance * rayDirX0;
// 		float floorY = game->player->position.y + rowDistance * rayDirY0;

// 		for (int x = 0; x < DEFAULT_S_WIDTH; x++)
// 		{
// 			int cellX = (int)floorX;
// 			int cellY = (int)floorY;

// 			if (cellX >= 0 && cellX < game->map->width && cellY >= 0 && cellY < game->map->height)
// 			{
// 				int texture_index = game->floor_texture_map[cellY][cellX];

// 				if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
// 				{
// 					t_texture *current_texture = &game->floortextures[texture_index];

// 					if (current_texture && current_texture->data)
// 					{
// 						float fracX = floorX - floorf(floorX);
// 						float fracY = floorY - floorf(floorY);
// 						float tx = fracX * current_texture->width;
// 						float ty = fracY * current_texture->height;

// 						// Ensure tx and ty are always within texture bounds
// 						tx = fmodf(tx, current_texture->width);
// 						ty = fmodf(ty, current_texture->height);

// 						if (tx < 0) tx += current_texture->width;
// 						if (ty < 0) ty += current_texture->height;

// 						int color = get_floor_texture_color(current_texture, (int)tx, (int)ty);
// 						img_pix_put(&game->img, x, y, color);
// 					}
// 				}
// 			}
// 			floorX += floorStepX;
// 			floorY += floorStepY;
// 		}
// 	}
// }


// Calculation structures and functions

void calculate_floor_ray_params(t_game *game, t_floor_ray *floor_ray, int y)
{
    float pitch = game->player->pitch;
    float player_height = game->player->height;
    int horizon = DEFAULT_S_HEIGHT / 2;
    int pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
    int p = y - horizon + pitch_pixel_offset;
    float posZ = 0.5f * DEFAULT_S_HEIGHT * (1.0f + player_height * 2);

    floor_ray->rayDirX0 = game->player->direction.x - game->player->plane.x;
    floor_ray->rayDirY0 = game->player->direction.y - game->player->plane.y;
    floor_ray->rayDirX1 = game->player->direction.x + game->player->plane.x;
    floor_ray->rayDirY1 = game->player->direction.y + game->player->plane.y;

    floor_ray->rowDistance = posZ / p;

    floor_ray->floorStepX = floor_ray->rowDistance * (floor_ray->rayDirX1 - floor_ray->rayDirX0) / DEFAULT_S_WIDTH;
    floor_ray->floorStepY = floor_ray->rowDistance * (floor_ray->rayDirY1 - floor_ray->rayDirY0) / DEFAULT_S_WIDTH;

    floor_ray->floorX = game->player->position.x + floor_ray->rowDistance * floor_ray->rayDirX0;
    floor_ray->floorY = game->player->position.y + floor_ray->rowDistance * floor_ray->rayDirY0;
}

int get_floor_texture_index(t_game *game, int cellX, int cellY)
{
    if (cellX >= 0 && cellX < game->map->width && cellY >= 0 && cellY < game->map->height)
    {
        return game->floor_texture_map[cellY][cellX];
    }
    return -1;
}

// int calculate_floor_pixel_color(t_game *game, float floorX, float floorY)
// {
//     int cellX = (int)floorX;
//     int cellY = (int)floorY;

//     int texture_index = get_floor_texture_index(game, cellX, cellY);

//     if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
//     {
//         t_texture *current_texture = &game->floortextures[texture_index];

//         if (current_texture && current_texture->data)
//         {
//             float fracX = floorX - floorf(floorX);
//             float fracY = floorY - floorf(floorY);
//             float tx = fmodf(fracX * current_texture->width, current_texture->width);
//             float ty = fmodf(fracY * current_texture->height, current_texture->height);

//             if (tx < 0) tx += current_texture->width;
//             if (ty < 0) ty += current_texture->height;

//             return get_floor_texture_color(current_texture, (int)tx, (int)ty);
//         }
//     }
//     return 0x707070; // Blue for out-of-bounds or invalid texture
// }

t_texture* get_floor_texture(t_game *game, int texture_index)
{
    if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
    {
        return &game->floortextures[texture_index];
    }
    return NULL;
}

// Calculate texture coordinates
void calculate_texture_coordinates(t_texture *texture, float floorX, float floorY, float *tx, float *ty)
{
    float fracX = floorX - floorf(floorX);
    float fracY = floorY - floorf(floorY);

    *tx = fmodf(fracX * texture->width, texture->width);
    *ty = fmodf(fracY * texture->height, texture->height);

    if (*tx < 0) *tx += texture->width;
    if (*ty < 0) *ty += texture->height;
}

int calculate_floor_pixel_color(t_game *game, float floorX, float floorY)
{
    int cellX = (int)floorX;
    int cellY = (int)floorY;

    int texture_index = get_floor_texture_index(game, cellX, cellY);
    t_texture *current_texture = get_floor_texture(game, texture_index);

    if (current_texture && current_texture->data)
    {
        float tx, ty;
        calculate_texture_coordinates(current_texture, floorX, floorY, &tx, &ty);
        return get_floor_texture_color(current_texture, (int)tx, (int)ty);
    }

    return 0x707070; // Default color for out-of-bounds or invalid texture
}

void render_floor_line(t_game *game, t_floor_ray *floor_ray, int y)
{
    for (int x = 0; x < DEFAULT_S_WIDTH; x++)
    {
        int color = calculate_floor_pixel_color(game, floor_ray->floorX, floor_ray->floorY);
        img_pix_put(&game->img, x, y, color);

        floor_ray->floorX += floor_ray->floorStepX;
        floor_ray->floorY += floor_ray->floorStepY;
    }
}


// Validate game state
int validate_game_state(t_game *game)
{
    if (!game || !game->player || !game->map || !game->floor_texture_map)
    {
        printf("Error: Invalid game state in render_floor\n");
        return 0;
    }
    return 1;
}

// Calculate the starting y-coordinate for floor rendering
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

// Rendering function
// void render_floor(t_game *game)
// {
//     if (!game || !game->player || !game->map || !game->floor_texture_map)
//     {
//         printf("Error: Invalid game state in render_floor\n");
//         return;
//     }

//     float pitch = game->player->pitch;
//     int pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
//     // float player_height = game->player->height;

//     int horizon = DEFAULT_S_HEIGHT / 2;
//     int floor_start = horizon - pitch_pixel_offset;
//     floor_start = (floor_start < 0) ? 0 : (floor_start >= DEFAULT_S_HEIGHT ? DEFAULT_S_HEIGHT - 1 : floor_start);

//     t_floor_ray floor_ray;

//     for (int y = floor_start; y < DEFAULT_S_HEIGHT; y++)
//     {
//         calculate_floor_ray_params(game, &floor_ray, y);

//         for (int x = 0; x < DEFAULT_S_WIDTH; x++)
//         {
//             int color = calculate_floor_pixel_color(game, floor_ray.floorX, floor_ray.floorY);
//             img_pix_put(&game->img, x, y, color);

//             floor_ray.floorX += floor_ray.floorStepX;
//             floor_ray.floorY += floor_ray.floorStepY;
//         }
//     }
// }
