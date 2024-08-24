/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_boundaries.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:45:14 by cliew             #+#    #+#             */
/*   Updated: 2024/08/24 14:38:40 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
	int parse_char_to_int(char chars)
	{
		if (chars==48)
			return 0;
		if (chars==49)
			return 1;
		if (chars==32)
			return 9;
		if (chars=='N')
			return 2;
		if (chars=='E')
			return 3;
		if (chars=='S')
			return 4;
		if (chars=='W')
			return 5;
		return -1;
	}

	int	floodfill(t_game *game, int **filled_map, int i, int j)
{
	int	is_surrounded;
	// printf("i is %d and j is %d",i,j);
	if (i < 0 || i >= game->cub_map_row_count || j < 0 || j >= ((game->cub_map_col_count+1)/2))
		return (0);
	if (game->cub_map_array[i][j] == 1|| filled_map[i][j] == 1)
		return (1);
	else
		filled_map[i][j] = 1;
	// print_2d_array(game,filled_map);

	is_surrounded = 1;
	is_surrounded &= floodfill(game, filled_map, i - 1, j);
	is_surrounded &= floodfill(game, filled_map, i + 1, j);
	is_surrounded &= floodfill(game, filled_map, i, j - 1);
	is_surrounded &= floodfill(game, filled_map, i, j + 1);
	return (is_surrounded);
}


int			check_map_boundaries(t_game *game)
{
	int		x;
	int		y;
	int	**filled_map;
	int	is_surrounded;

	x = game->cub_player_x;
	y = game->cub_player_y;
	filled_map=initializeArray(game->cub_map_row_count, (game->cub_map_col_count + 1) / 2); 
	// print_2d_array(game,filled_map);
	is_surrounded = floodfill(game, filled_map, x, y);
	if (!is_surrounded)
	{
		printf("Map isn't surrounded by wall");
		return -1;
	}

	// free_ptrarr((void**)filled_map);
	// if (!is_surrounded)
	// 	return (put_and_return_err("Map isn't surrounded by wall"));
	return (0);
}