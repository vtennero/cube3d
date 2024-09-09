/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures04_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:13:32 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:17:55 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void scale_gun_textures(t_game *game)
{
    double scale_height = game->screen_height * 0.55;
    double scale_width = game->screen_width * 0.6;

    for (int i = 0; i < game->num_gun_frames; i++)
    {
        t_texture *gun_texture = &game->gun_textures[i];

        gun_texture->height = (int)scale_height;
        gun_texture->width = (int)(gun_texture->width * (scale_height / gun_texture->height));

        if (gun_texture->width > scale_width)
        {
            gun_texture->width = (int)scale_width;
            gun_texture->height = (int)(gun_texture->height * (scale_width / gun_texture->width));
        }
    }
}

void scale_shooting_textures(t_game *game)
{
    double scale_height = game->screen_height * 0.55;
    double scale_width = game->screen_width * 0.6;

    for (int i = 0; i < game->num_gun_frames; i++)
    {
        t_texture *gun_texture = &game->shooting_texture[i];

        gun_texture->height = (int)scale_height;
        gun_texture->width = (int)(gun_texture->width * (scale_height / gun_texture->height));

        if (gun_texture->width > scale_width)
        {
            gun_texture->width = (int)scale_width;
            gun_texture->height = (int)(gun_texture->height * (scale_width / gun_texture->width));
        }
    }
}
