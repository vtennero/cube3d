/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/08/27 15:21:05 by cliew             #+#    #+#             */
/*   Updated: 2024/08/27 15:28:23 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_split_result(char **words)
{
	int	i;

	i = 0;
	if (words == NULL)
	{
		return ;
	}
	while (words[i] != NULL)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

void	free_array(int **array, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_floor_texture_map(t_game *game)
{
	int	y;

	y = 0;
	if (!game || !game->floor_texture_map || !game->map)
		return ;
	while (y < game->map->height)
	{
		if (game->floor_texture_map[y])
		{
			free(game->floor_texture_map[y]);
			game->floor_texture_map[y] = NULL;
		}
		y++;
	}
	free(game->floor_texture_map);
	game->floor_texture_map = NULL;
}

void	free_wall_texture_map_path(t_game *game)
{
	if (game->walltextures[0].path)
		free(game->walltextures[0].path);
	if (game->walltextures[1].path)
		free(game->walltextures[1].path);
	if (game->walltextures[2].path)
		free(game->walltextures[2].path);
	if (game->walltextures[3].path)
		free(game->walltextures[3].path);
	if (game->floor_rgb[0].path)
		free(game->floor_rgb[0].path);
	if (game->sky_rgb[0].path)
		free(game->sky_rgb[0].path);
}

void	clean_map(t_game *game)
{
	if (game->cub_map_array)
		free_array((game->cub_map_array),(game->cub_map_row_count)*2);
	if (game->map)
		free(game->map);
}
