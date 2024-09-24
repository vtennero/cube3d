/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utility00.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:07:37 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:08:01 by vitenner         ###   ########.fr       */
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
	int	x;
	int	y;
	int	i;
	int	j;

	x = game->cub_map_row_count;
	y = ((game->cub_map_col_count + 1) / 2);
	ft_printf("\n GAME MAP ARRAY \n _________________________________ \n");
	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			printf("%d ", array_to_print[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (1);
}
