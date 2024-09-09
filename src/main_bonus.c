/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:28:29 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 14:28:29 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int main(int argc, char **argv)
{
    t_game *game;

    game = NULL;

    create_game_struct(&game, 1);
	if (argc>1 && parse_map(game,argv[1])!=-1)
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
