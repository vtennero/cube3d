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

int	free_and_return(char *line, int ret)
{
	free(line);
	return (ret);
}

int	freesplit_and_return(char	**words,int ret)
{
	free_split_result(words);
	return (ret);
}

int	check_map_error(int *map_start, int word_count, char **words)
{
	if (*map_start == 0 && (word_count != 2 || ((ft_strcmp(words[0], "NO") != 0)
				&& (ft_strcmp(words[0], "EA") != 0) && (ft_strcmp(words[0],
						"SO") != 0) && (ft_strcmp(words[0], "WE") != 0)
				&& (ft_strcmp(words[0], "F") != 0) && (ft_strcmp(words[0],
						"C") != 0))))
	{
		if ((ft_strcmp(words[0], "F") == 0) || (ft_strcmp(words[0], "C") == 0))
			ft_printf("Error\nRGB value must be 3 values between 0 and 255, "
						"separated by comma (e.g. 0,125,255)\n");
		else
			ft_printf("Error\nInvalid characters in texture parsing\n");
		return (-1);
	}
	return (1);
}