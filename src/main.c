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
		if (game)
			free(game);
		printf("Error\n");
		printf("Map Parsing Failed\n");
	}
    return (0);
}
