/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 11:48:37 by cliew             #+#    #+#             */
/*   Updated: 2024/09/08 11:48:37 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	get_directions(t_game *game)
{
	game->directions[0][0] = -1;
	game->directions[0][1] = 0;
	game->directions[1][0] = 1;
	game->directions[1][1] = 0;
	game->directions[2][0] = 0;
	game->directions[2][1] = -1;
	game->directions[3][0] = 0;
	game->directions[3][1] = 1;
}

int	is_valid_position(t_game *game, int x, int y)
{
	return (x >= 0 && x < game->cub_map_row_count && y >= 0
		&& y < ((game->cub_map_col_count + 1) / 2)
		&& game->cub_map_array[x][y] == 0 && game->filled_map[x][y] == 0);
}

void	initialize_stack(t_game *game, int start_i, int start_j)
{
	game->stack = (t_point *)malloc((size_t)(game->cub_map_row_count
				* game->cub_map_col_count) * sizeof(t_point));
	if (game->stack == NULL)
	{
		fprintf(stderr, "Memory allocation failed for stack\n");
		exit(EXIT_FAILURE);
	}
	game->stack_size = 0;
	game->stack[game->stack_size++] = (t_point){start_i, start_j};
}

void	process_position(t_game *game, t_point current)
{
	int	x;
	int	y;
	int	d;
	int	new_x;
	int	new_y;

	x = current.x;
	y = current.y;
	d = 0;
	get_directions(game);
	game->filled_map[x][y] = 1;
	while (d < 4)
	{
		new_x = x + game->directions[d][0];
		new_y = y + game->directions[d][1];
		if (is_valid_position(game, new_x, new_y))
		{
			game->stack[game->stack_size++] = (t_point){new_x, new_y};
		}
		d++;
	}
}

int	fill_and_process_stack(t_game *game)
{
	int		is_surrounded;
	t_point	current;

	is_surrounded = 1;
	while (game->stack_size > 0)
	{
		game->stack_size--;
		current = game->stack[game->stack_size];
		if (!is_valid_position(game, current.x, current.y))
		{
			continue ;
		}
		process_position(game, current);
	}
	return (is_surrounded);
}
