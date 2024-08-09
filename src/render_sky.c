/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sky.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:42:48 by root              #+#    #+#             */
/*   Updated: 2024/07/10 12:52:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void render_sky(t_game *game, char *sky_texture_path)
// {
//     static void *sky_texture = NULL;
//     static char *sky_data = NULL;
//     static int sky_width = 0, sky_height = 0;
//     static int bpp, line_len, endian;

//     // Load the sky texture only once
//     if (sky_texture == NULL)
//     {
//         sky_texture = mlx_xpm_file_to_image(game->mlx_ptr, sky_texture_path, 		&sky_width, &sky_height);
//         if (sky_texture == NULL)
//         {
//             fprintf(stderr, "Failed to load sky texture\n");
//             return ;
//         }
//         sky_data = mlx_get_data_addr(sky_texture, &bpp, &line_len, &endian);
//     }

//     // Calculate the angle of the player's direction
//     float angle = atan2(game->player->direction.y, 		game->player->direction.x);

//     // Adjust rotation speed (smaller value = slower rotation)
//     float rotation_speed = 0.25;
	// Adjust this value to change rotation speed

//     // Calculate the pixel offset in the texture
//     int texture_offset = (int)(fmodf(sky_width - angle / (2 * M_PI) 			* rotation_speed * sky_width, sky_width)); 

//     // Calculate pitch offset
//     int pitch_offset = (int)(game->player->pitch * game->screen_height);
//     int height_offset = (int)(game->player->height * game->screen_height);

//     // Determine the vertical range to render the sky
//     int sky_start = 0;
//     int sky_end = game->screen_height / 2 + pitch_offset + height_offset;

//     // Clamp sky_end to screen height
//     sky_end = (sky_end > game->screen_height) ? game->screen_height : sky_end;

//     for (int i = sky_start; i < sky_end; i++)
//     {
//         for (int j = 0; j < game->screen_width; j++)
//         {
//             // Calculate texture coordinates
//             int tx = (texture_offset + (j * sky_width / game->screen_width)) 	% sky_width;
//             int ty = (i - pitch_offset) * sky_height / (game->screen_height 		/ 2);

//             // Ensure tx and ty are within bounds
//             tx = (tx < 0) ? 0 : (tx >= sky_width) ? sky_width - 1 : tx;
//             ty = (ty < 0) ? 0 : (ty >= sky_height) ? sky_height - 1 : ty;

//             // Calculate the pixel position in the texture data
//             int pixel_pos = ty * line_len + tx * (bpp / 8);

//             // Ensure we're not reading out of bounds
//             if (pixel_pos >= 0 && pixel_pos < sky_height * line_len)
//             {
//                 int color = *((int *)(sky_data + pixel_pos));
//                 img_pix_put(&game->img, j, i, color);
//             }
//         }
//     }
// }

// v2

void	render_sky(t_game *game, char *sky_texture_path)
{
	static void *sky_texture = NULL;
	static char *sky_data = NULL;
	static int sky_width = 0, sky_height = 0;
	static int bpp, line_len, endian;

	// Load the sky texture only once
	if (sky_texture == NULL)
	{
		sky_texture = mlx_xpm_file_to_image(game->mlx_ptr, sky_texture_path,
				&sky_width, &sky_height);
		if (sky_texture == NULL)
		{
			fprintf(stderr, "Failed to load sky texture\n");
			return ;
		}
		sky_data = mlx_get_data_addr(sky_texture, &bpp, &line_len, &endian);
	}

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

	for (int i = sky_start; i < sky_end; i++)
	{
		for (int j = 0; j < game->screen_width; j++)
		{
			// Calculate texture coordinates
			// float tx_ratio = (angle + atan2((j - game->screen_width / 2), 						game->screen_width / 2)) / (2 * M_PI);
			float tx_ratio = (angle - atan2((j - game->screen_width / 2), game->screen_width / 2)) / (2 * M_PI);
			tx_ratio = fmodf(tx_ratio, 1.0f);
			if (tx_ratio < 0)
				tx_ratio += 1.0f;
			int tx = (int)(tx_ratio * sky_width);

			float ty_ratio = (float)(i - sky_start) / (sky_end - sky_start);
			int ty = (int)(ty_ratio * sky_height);

			// Ensure tx and ty are within bounds
			tx = (tx < 0) ? 0 : (tx >= sky_width) ? sky_width - 1 : tx;
			ty = (ty < 0) ? 0 : (ty >= sky_height) ? sky_height - 1 : ty;

			// Calculate the pixel position in the texture data
			int pixel_pos = ty * line_len + tx * (bpp / 8);

			// Ensure we're not reading out of bounds
			if (pixel_pos >= 0 && pixel_pos < sky_height * line_len)
			{
				int color = *((int *)(sky_data + pixel_pos));
				img_pix_put(&game->img, j, i, color);
			}
		}
	}
}

