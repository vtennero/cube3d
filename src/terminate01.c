/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:35:22 by toto              #+#    #+#             */
/*   Updated: 2024/08/27 15:57:08 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void handle_key_esc(t_game *game)
{
    if (game->key_state[K_ESC] == 1)
		cleanup(game);
}

int close_hook(t_game *game)
{
    ft_printf("Close button clicked, exiting...\n");
    cleanup(game);
    return (0);
}
