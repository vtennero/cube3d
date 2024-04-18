/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:02:02 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/17 14:31:02 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void set_texture(t_game *game, t_direction dir)
{
    if (!game) 
        return;
    if (dir < NORTH || dir > WEST)
        return;
    free(game->walltextures[dir].path);
    game->walltextures[dir].path = NULL;
    const char *texture_paths[] = {
        "bluestone.xpm",
        "eagle.xpm",
        "greystone.xpm",
        "wood.xpm"
    };
    game->walltextures[dir].path = ft_strdup(texture_paths[dir]);
}
