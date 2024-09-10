/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sky.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:16:02 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:16:09 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void render_sky_rgb(t_game *game, int color)
{
	// Check for NULL pointers
	if (game == NULL ) {
		fprintf(stderr, "Error: game  is NULL.\n");
		return;
	}

	if ( game->player == NULL) {
		fprintf(stderr, "Error: game->player is NULL.\n");
		return;
	}

	// Check for valid screen height
	if (game->screen_height <= 0) {
		fprintf(stderr, "Error: screen_height must be positive.\n");
		return;
	}

	// Check for valid pitch value
	if (isnan(game->player->pitch) || isinf(game->player->pitch)) {
		fprintf(stderr, "Error: player->pitch is invalid.\n");
		return;
	}

	// Calculate pitch offset and height offset
	int pitch_offset = (int)(game->player->pitch * game->screen_height);
	int height_offset = (int)(game->player->height * game->screen_height);

	// Determine the vertical range to render the sky
	int sky_start = 0;
	int wall_top = (game->screen_height / 2) - height_offset; // Top of the wall on the screen
	int sky_end = wall_top + pitch_offset + (game->screen_height / 5) ;

	// Clamp sky_end to screen height
	sky_end = (sky_end > game->screen_height) ? game->screen_height : sky_end;

	// Paint the sky with the provided color
	for (int i = sky_start; i < sky_end; i++)
	{
		for (int j = 0; j < game->screen_width; j++)
		{
			img_pix_put(&game->img, j, i, color);
		}
	}
}
