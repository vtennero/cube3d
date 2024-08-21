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

int initgame(t_game **game)
{
    printf("initgame\n");
    create_game_struct(game);
    create_map(*game);
    create_player(*game);
    create_collectibles(*game);
    create_extraction(*game);
    create_enemies(*game);
    setup_game_mlx(*game);


    return (1);
}

int main()
{
    t_game *game;

    game = NULL;




    // if (map_is_valid)
    initgame(&game);

    return (0);
}