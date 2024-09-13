/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures01_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:11:30 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:13:52 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void load_outro_textures(t_game *game)
{
	char path[] = "textures/outro/outro000.xpm";
	int first_digit, second_digit, third_digit;

	get_last_three_digit_indexes(path, &first_digit, &second_digit, &third_digit);

	for (int i = 0; i < MAX_OUTRO_TEXTURES; i++)
	{
		path[first_digit] = '0' + (i / 100);       // Replace the first digit
		path[second_digit] = '0' + ((i / 10) % 10); // Replace the second digit
		path[third_digit] = '0' + (i % 10);        // Replace the third digit

		game->outro_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->outro_texture[i].width, &game->outro_texture[i].height);
		if (game->outro_texture[i].img == NULL)
		{
			fprintf(stderr, "\nError: Could not load outro texture: %s\n", path);
			exit(1);
		}
		game->outro_texture[i].data = mlx_get_data_addr(game->outro_texture[i].img, &game->outro_texture[i].tex_bpp, &game->outro_texture[i].tex_line_len, &game->outro_texture[i].tex_endian);

		update_progress_bar(game, i + 1, MAX_OUTRO_TEXTURES, "Loading outro textures");
	}
}
void load_enemy_textures(t_game *game, const char *path_format, int num_textures)
{
	if (num_textures > NUM_ENEMY_TEXTURES) {
		exit(1);
	}

	for (int i = 0; i < num_textures; i++)
	{
		update_progress_bar(game, i + 1, num_textures, "Loading enemy textures");

		char path[256];
		sprintf(path, path_format, i);

		game->enemy_textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->enemy_textures[i].width, &game->enemy_textures[i].height);
		if (game->enemy_textures[i].img == NULL)
		{
			exit(1);
		}
		game->enemy_textures[i].data = mlx_get_data_addr(game->enemy_textures[i].img, &game->enemy_textures[i].tex_bpp, &game->enemy_textures[i].tex_line_len, &game->enemy_textures[i].tex_endian);
	}
}

void load_opening_textures(t_game *game, const char *path_format, int num_textures)
{
	if (num_textures > MAX_OPENING_TEXTURES) {
		exit(1);
	}

	for (int i = 0; i < num_textures; i++)
	{
		update_progress_bar(game, i + 1, num_textures, "Loading opening textures");

		char path[256];
		sprintf(path, path_format, i);

		game->opening_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->opening_texture[i].width, &game->opening_texture[i].height);
		if (game->opening_texture[i].img == NULL)
		{
			exit(1);
		}
		game->opening_texture[i].data = mlx_get_data_addr(game->opening_texture[i].img, &game->opening_texture[i].tex_bpp, &game->opening_texture[i].tex_line_len, &game->opening_texture[i].tex_endian);
	}
}

void load_land_textures(t_game *game, const char *path_format, int num_textures)
{
	if (num_textures > MAX_LAND_TEXTURES) {
		exit(1);
	}

	for (int i = 0; i < num_textures; i++)
	{
		update_progress_bar(game, i + 1, num_textures, "Loading land textures");

		char path[256];
		sprintf(path, path_format, i);

		game->land_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->land_texture[i].width, &game->land_texture[i].height);
		if (game->land_texture[i].img == NULL)
		{
			exit(1);
		}
		game->land_texture[i].data = mlx_get_data_addr(game->land_texture[i].img, &game->land_texture[i].tex_bpp, &game->land_texture[i].tex_line_len, &game->land_texture[i].tex_endian);
	}
}

void load_collectible_texture(t_game *game, const char *texture_path)
{
	update_progress_bar(game, 0, 1, "Loading collectible texture");

	game->coll_texture[0].img = mlx_xpm_file_to_image(
			game->mlx_ptr,
			(char *)texture_path,
			&game->coll_texture[0].width,
			&game->coll_texture[0].height);

	if (!game->coll_texture[0].img)
	{
		exit(EXIT_FAILURE);
	}

	game->coll_texture[0].data = mlx_get_data_addr(
			game->coll_texture[0].img,
			&game->coll_texture[0].tex_bpp,
			&game->coll_texture[0].tex_line_len,
			&game->coll_texture[0].tex_endian);

	update_progress_bar(game, 1, 1, "Loading collectible texture");
}

