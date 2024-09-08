/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_boundaries.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/07/13 12:45:14 by cliew             #+#    #+#             */
/*   Updated: 2024/08/27 16:24:17 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_char_to_int(char chars)
{
	if (chars == 48)
		return (0);
	if (chars == 49)
		return (1);
	if (ft_isspace(chars))
		return (9);
	if (chars == 'N')
		return (2);
	if (chars == 'E')
		return (3);
	if (chars == 'S')
		return (4);
	if (chars == 'W')
		return (5);
	return (-1);
}

int	check_map_boundaries(t_game *game)
{
	int	x;
	int	y;
	int	**filled_map;
	int	is_surrounded;

	x = game->cub_player_x;
	y = game->cub_player_y;
	filled_map = initialize_array(game->cub_map_row_count * 2,
			(game->cub_map_col_count + 1) / 2);
	game->filled_map = filled_map;
	is_surrounded = floodfill_iterative(game, x, y);
	freeArray(filled_map, game->cub_map_row_count * 2);
	if (!is_surrounded)
	{
		printf("Map isn't surrounded by wall");
		return (-1);
	}
	return (0);
}

int	rgb_to_hex_int(int red, int green, int blue)
{
	if (red < 0)
		red = 0;
	else if (red > 255)
		red = 255;
	if (green < 0)
		green = 0;
	else if (green > 255)
		green = 255;
	if (blue < 0)
		blue = 0;
	else if (blue > 255)
		blue = 255;
	return ((red << 16) | (green << 8) | blue);
}

int	parse_floor_sky_rgb(t_game *game)
{
	char	**f_split;
	char	**s_split;

	f_split = ft_split(game->floor_rgb[0].path, ',');
	game->floor_rgb[0].red = ft_atoi(f_split[0]);
	game->floor_rgb[0].green = ft_atoi(f_split[1]);
	game->floor_rgb[0].blue = ft_atoi(f_split[2]);
	game->floor_rgb[0].hex_color = rgb_to_hex_int(game->floor_rgb[0].red,
			game->floor_rgb[0].green, game->floor_rgb[0].blue);
	s_split = ft_split(game->sky_rgb[0].path, ',');
	game->sky_rgb[0].red = ft_atoi(s_split[0]);
	game->sky_rgb[0].green = ft_atoi(s_split[1]);
	game->sky_rgb[0].blue = ft_atoi(s_split[2]);
	game->sky_rgb[0].hex_color = rgb_to_hex_int(game->sky_rgb[0].red,
			game->sky_rgb[0].green, game->sky_rgb[0].blue);
	free_split_result(f_split);
	free_split_result(s_split);
	return (1);
}

int	floodfill_iterative(t_game *game, int start_i, int start_j)
{
	int	is_surrounded;

	if (start_i < 0 || start_i >= game->cub_map_row_count || start_j < 0
		|| start_j >= ((game->cub_map_col_count + 1) / 2))
	{
		printf("Invalid starting position: i=%d, j=%d\n", start_i, start_j);
		return (0);
	}
	initialize_stack(game, start_i, start_j);
	is_surrounded = fill_and_process_stack(game);
	free(game->stack);
	return (is_surrounded);
}
