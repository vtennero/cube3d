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
	int	is_surrounded;
int	**filled_map;
	is_surrounded = 1;
int x;
int y;

	x = game->cub_player_x;
	y = game->cub_player_y;
	filled_map=initialize_array(game->cub_map_row_count , (game->cub_map_col_count + 1)/2); 
	is_surrounded = floodfill(game, filled_map, x, y);
	free_array(filled_map,game->cub_map_row_count);
	if (!is_surrounded)
	{
		ft_printf("Error\nMap isn't surrounded by wall\n");
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
