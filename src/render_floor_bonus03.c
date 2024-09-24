/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_bonus03.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:59:08 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:00:17 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	fill_floor_texture_map(t_game *game)
{
	int	y;
	int	x;
	int	selected_texture;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			selected_texture = select_weighted_texture(game);
			game->floor_texture_map[y][x] = selected_texture;
			x++;
		}
		y++;
	}
}

void	initialize_floor_texture_map(t_game *game)
{
	game->floor_texture_map = allocate_floor_texture_map(game);
	fill_floor_texture_map(game);
}
