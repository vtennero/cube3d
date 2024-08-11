/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:35:22 by toto              #+#    #+#             */
/*   Updated: 2024/08/11 18:03:00 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void handle_key_esc(t_game *game)
{
    if (game->key_state[K_ESC] == 1)
		cleanup(game);
}

void handle_cross_key(t_game *game)
{
	cleanup(game);
}
