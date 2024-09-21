/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:13:31 by cliew             #+#    #+#             */
/*   Updated: 2024/09/21 17:13:31 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	create_game_struct(&game, 1);
	if (argc > 1 && parse_map(game, argv[1]) != -1)
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
