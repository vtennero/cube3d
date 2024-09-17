/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sky_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:15:50 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:15:50 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void render_sky(t_game *game)
{
	// Calculate the angle of the player's direction
	float angle = atan2(game->player->direction.y, game->player->direction.x);

	// Calculate pitch offset
	int pitch_offset = (int)(game->player->pitch * game->screen_height);
	int height_offset = (int)(game->player->height * game->screen_height);

	// Determine the vertical range to render the sky
	int sky_start = 0;
	int sky_end = game->screen_height / 2 + pitch_offset + height_offset;

	// Clamp sky_end to screen height
	sky_end = (sky_end > game->screen_height) ? game->screen_height : sky_end;

	// Calculate texture reveal based on pitch
	float texture_reveal = (1.0f - game->player->pitch) / 2.0f;  // Map [-1, 1] to [1, 0]

	for (int i = sky_start; i < sky_end; i++)
	{
		for (int j = 0; j < game->screen_width; j++)
		{
			// Calculate texture coordinates
			float tx_ratio = (angle + atan2((j - game->screen_width / 2), game->screen_width / 2)) / (2 * M_PI);
			tx_ratio = fmodf(tx_ratio, 1.0f);
			if (tx_ratio < 0)
				tx_ratio += 1.0f;
			int tx = (int)(tx_ratio * game->sky_texture.width);

			// Calculate ty_ratio to reveal more of the top when looking up
			float screen_ratio = (float)(i - sky_start) / (sky_end - sky_start);
			float ty_ratio = texture_reveal + screen_ratio * (1.0f - texture_reveal);
			ty_ratio = fminf(fmaxf(ty_ratio, 0.0f), 1.0f);  // Clamp to [0, 1]
			int ty = (int)(ty_ratio * game->sky_texture.height);

			// Ensure tx and ty are within bounds
			tx = (tx < 0) ? 0 : (tx >= game->sky_texture.width) ? game->sky_texture.width - 1 : tx;
			ty = (ty < 0) ? 0 : (ty >= game->sky_texture.height) ? game->sky_texture.height - 1 : ty;

			// Calculate the pixel position in the texture data
			int pixel_pos = ty * game->sky_texture.tex_line_len + tx * (game->sky_texture.tex_bpp / 8);

			// Ensure we're not reading out of bounds
			if (pixel_pos >= 0 && pixel_pos < game->sky_texture.height * game->sky_texture.tex_line_len)
			{
				int color = *((int *)(game->sky_texture.data + pixel_pos));
				img_pix_put(&game->img, j, i, color);
			}
		}
	}
}
