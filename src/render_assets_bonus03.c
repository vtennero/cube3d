/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus03.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:08:11 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:08:11 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_pelican_inside(t_game *game)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	if (game->pelican_inside[0].img == NULL || game->player->is_extracting == 0)
		return ;
	y = 0;
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			tex_x = x * game->pelican_inside[0].width / game->screen_width;
			tex_y = y * game->pelican_inside[0].height / game->screen_height;
			color = get_texture_color(&game->pelican_inside[0], tex_x, tex_y);
			if ((unsigned int)color != 0)
				img_pix_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}
