/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:55:31 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/17 17:35:54 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int main(int argc, char **argv)
{
    t_game *game;

    game = NULL;

    create_game_struct(&game, 0);
	if (argc>1 && parse_map(game,argv[1]) != -1)
    	initgame(&game);
	else
	{
		free_texture_array(game->walltextures,MAX_WALL_TEXTURES,game);
    	free_texture_array(game->floortextures,MAX_FLOOR_TEXTURES,game);
		free_floor_texture_map(game);
		free_wall_texture_map_path(game);

		if (game->cub_map_array)
			free_array((game->cub_map_array),(game->cub_map_row_count)*2);
		if (game->map)
			free(game->map);

		if (game)
			free(game);
	

		printf("Error\n");
		printf("Map Parsing Failed\n");
	}
    return (0);
}
