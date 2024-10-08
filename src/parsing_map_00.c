/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/07/13 12:42:15 by cliew             #+#    #+#             */
/*   Updated: 2024/08/27 15:17:58 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	parse_line_to_map_array(char *line, t_game *game, int *map_line)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (i % 2 == 0 && i <= game->cub_map_col_count)
		{
			game->cub_map_array[*map_line][j] = parse_char_to_int(line[i]);
			j++;
		}
		else if (i <= game->cub_map_col_count
			&& parse_char_to_int(line[i]) != 9)
			return (-1);
		i++;
	}
	fill_lagging_zero(i, j, game, map_line);
	(*map_line)++;
	return (1);
}

int	loop_thru_line_in_map_array(t_game *game)
{
	int		fd;
	int		line_count;
	int		map_line;
	char	*line;

	map_line = 0;
	line_count = 0;
	fd = open(game->cub_filepath, O_RDONLY);
	if (fd < 0)
		return (handle_error("Error\nCould not open file", -1));
	line = get_next_line(fd);
	while ((line != NULL))
	{
		if ((line_count >= game->cub_line_count - game->cub_map_row_count)
			&& (map_line <= game->cub_map_row_count))
		{
			if (parse_line_to_map_array(line, game, &map_line) == -1)
				return (free_and_return(line, -1));
		}
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	check_player_position_helper(t_game *game, int i, int j, int *player_found)
{
	if (game->cub_map_array[i][j] == 2 || game->cub_map_array[i][j] == 3
		|| game->cub_map_array[i][j] == 4 || game->cub_map_array[i][j] == 5)
	{
		if (*player_found == 0)
		{
			*player_found = 1;
			game->cub_player_x = i;
			game->cub_player_y = j;
			game->cub_player_o = game->cub_map_array[i][j];
		}
		else
			return (-1);
	}
	return (1);
}

int	check_player_postion_and_map_char(t_game *game)
{
	int	i;
	int	j;
	int	player_found;

	i = 0;
	j = 0;
	player_found = 0;
	while (i < game->cub_map_row_count)
	{
		while (j < (game->cub_map_col_count + 1) / 2)
		{
			if (check_player_position_helper(game, i, j, &player_found) == -1)
				return (-1);
			if (game->cub_map_array[i][j] == -1)
				return (-2);
			j++;
		}
		j = 0;
		i++;
	}
	if (player_found == 0)
		return (0);
	return (1);
}

int	parse_map_to_array(t_game *game)
{
	int	check_status;

	game->cub_map_array = initialize_array(game->cub_map_row_count * 2,
			(game->cub_map_col_count + 1));
	if (loop_thru_line_in_map_array(game) == -1)
		return (handle_error("Error\nInvalid chracter detected in map!\n",
				-1));
	check_status = check_player_postion_and_map_char(game);
	if (check_status != 1)
	{
		if (check_status == 0)
			ft_printf("Error\nNo player postion is detected!");
		if (check_status == -1)
			ft_printf("Error\n2 Player postion detected!");
		if (check_status == -2)
			ft_printf("Error\nInvalid character in map detected!");
		return (-1);
	}
	return (1);
}
