/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utility01.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:07:45 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:07:45 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	free_and_return(char *line, int ret)
{
	free(line);
	return (ret);
}

int	freesplit_and_return(char **words, int ret)
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

void	fill_lagging_zero(int i, int j, t_game *game, int *map_line)
{
	while (i <= game->cub_map_col_count)
	{
		if (i % 2 == 0)
		{
			game->cub_map_array[*map_line][j] = 9;
			j++;
		}
		i++;
	}
}
