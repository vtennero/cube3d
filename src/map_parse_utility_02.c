/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/07/12 20:57:02 by cliew             #+#    #+#             */
/*   Updated: 2024/08/27 16:01:34 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_map(t_game *game, char *cub_filepath)
{
	game->cub_filepath = cub_filepath;
	if (read_cub_texture_and_analyze_map(game) == -1)
		return (-1);
	if (texture_error_handling(game) == -1)
		return (-1);
	parse_floor_sky_rgb(game);
	if (parse_map_to_array(game) == -1)
		return (-1);
	if (check_map_boundaries(game) == -1)
		return (-1);
	return (0);
}


int	print_2d_array(t_game *game, int **array_to_print)
{
	int x;
	int y;
	x = game->cub_map_row_count;
	y = ((game->cub_map_col_count + 1) / 2);

	printf("\n GAME MAP ARRAY \n _________________________________ \n");

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			printf("%d ", array_to_print[i][j]);
		}
		printf("\n");
	}
	return (1);
}