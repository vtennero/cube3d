/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomizer_bonus01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:37:25 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:37:25 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

unsigned long long	xorshift64(unsigned long long *state)
{
	unsigned long long	x;

	x = *state;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	*state = x;
	return (x);
}

void	initialize_game_seed(t_game *game)
{
	game->random_seed = 12345678901234567ULL;
}

unsigned long long	next_random(t_game *game)
{
	game->random_seed = (game->random_seed \
	* 6364136223846793005ULL + 1442695040888963407ULL) & 0xFFFFFFFFFFFFFFFFULL;
	return (game->random_seed);
}

int	random_int(t_game *game, int max)
{
	return ((int)(next_random(game) % max));
}

float	random_float(t_game *game)
{
	unsigned int	rand_int;

	rand_int = (unsigned int)(next_random(game) & 0xFFFFFFFF);
	return ((float)rand_int / (float)0x100000000);
}
