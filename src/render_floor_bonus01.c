/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_bonus01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:57:37 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 16:58:25 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calculate_total_weight(float *weights, int n_text, float *total_weight)
{
	int	i;

	*total_weight = 0;
	i = 0;
	while (i < n_text)
	{
		*total_weight += weights[i];
		i++;
	}
}

void	set_texture_weights(t_game *game, float *weights, float total_weight)
{
	int	i;

	i = 0;
	while (i < game->num_floor_textures)
	{
		game->floor_texture_weights[i].weight = weights[i] / total_weight;
		game->floor_texture_weights[i].texture_index = i;
		i++;
	}
}

void	initialize_floor_texture_weights(t_game *game)
{
	float	weights[8];
	float	total_weight;

	weights[0] = 0.20;
	weights[1] = 0.20;
	weights[2] = 0.20;
	weights[3] = 0.20;
	weights[4] = 0.05;
	weights[5] = 0.05;
	weights[6] = 0.05;
	weights[7] = 0.05;
	game->num_floor_textures = T_N_FLOOR;
	calculate_total_weight(weights, game->num_floor_textures, &total_weight);
	set_texture_weights(game, weights, total_weight);
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
			printf("Failed to allocate memory for floor_texture_map \
			row %d\n", y);
			cleanup(game);
		}
		y++;
	}
	return (floor_texture_map);
}
