/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pelican_inside_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:57:28 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/01 16:23:44 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void render_pelican_inside(t_game *game)
{
    t_texture *pelican_texture = &game->pelican_inside[0];
    int x, y;
    int color;

    if (pelican_texture->img == NULL)
    {
        printf("Error: pelican_inside texture not loaded\n");
        return;
    }

	if (game->player->is_extracting)
	{
		for (y = 0; y < game->screen_height; y++)
		{
			for (x = 0; x < game->screen_width; x++)
			{
				int tex_x = x * pelican_texture->width / game->screen_width;
				int tex_y = y * pelican_texture->height / game->screen_height;

				color = get_texture_color(pelican_texture, tex_x, tex_y);

				if ((unsigned int)color != 0)
					img_pix_put(&game->img, x, y, color);
			}
		}
	}

}