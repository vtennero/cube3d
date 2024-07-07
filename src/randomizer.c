/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:54:31 by root              #+#    #+#             */
/*   Updated: 2024/07/07 18:24:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void initialize_game_seed(t_game *game)
{
    // You can set this to any arbitrary large number
    game->random_seed = 12345678901234567ULL;
    printf("initialize_game_seed completed\n");
}

unsigned long long next_random(t_game *game)
{
    game->random_seed = (game->random_seed * 6364136223846793005ULL + 1442695040888963407ULL) & 0xFFFFFFFFFFFFFFFFULL;
    return game->random_seed;
}

int random_int(t_game *game, int max)
{
    return (int)(next_random(game) % max);
}
