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

void load_enemy_textures(t_game *game, const char *path_format, int num_textures)
{
	if (num_textures > NUM_ENEMY_TEXTURES) {
		fprintf(stderr, "Error: Trying to load more textures than allocated space.\n");
		exit(1);
	}

	for (int i = 0; i < num_textures; i++)
	{
		char path[256];
		sprintf(path, path_format, i);
		// sprintf(path, path_format, i + 1);  // This is correct, as it will generate 001 to 013

		game->enemy_textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->enemy_textures[i].width, &game->enemy_textures[i].height);
		if (game->enemy_textures[i].img == NULL)
		{
			fprintf(stderr, "Error: Could not load enemy texture: %s\n", path);
			exit(1);
		}
		game->enemy_textures[i].data = mlx_get_data_addr(game->enemy_textures[i].img, &game->enemy_textures[i].tex_bpp, &game->enemy_textures[i].tex_line_len, &game->enemy_textures[i].tex_endian);
		printf("Loaded enemy texture %03d\n", i + 1);  // Changed to print the actual file number
	}
}

void load_opening_textures(t_game *game, const char *path_format, int num_textures)
{
	if (num_textures > MAX_OPENING_TEXTURES) {
		fprintf(stderr, "Error: Trying to load more textures than allocated space.\n");
		exit(1);
	}

	for (int i = 0; i < num_textures; i++)
	{
		char path[256];
		sprintf(path, path_format, i);  // This is correct, as it will generate 001 to 013

		game->opening_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->opening_texture[i].width, &game->opening_texture[i].height);
		if (game->opening_texture[i].img == NULL)
		{
			fprintf(stderr, "Error: Could not load opening texture: %s\n", path);
			exit(1);
		}
		game->opening_texture[i].data = mlx_get_data_addr(game->opening_texture[i].img, &game->opening_texture[i].tex_bpp, &game->opening_texture[i].tex_line_len, &game->opening_texture[i].tex_endian);
	}
	printf("Loaded opening textures\n");  // Changed to print the actual file number

}

void load_land_textures(t_game *game, const char *path_format, int num_textures)
{
	if (num_textures > MAX_LAND_TEXTURES) {
		fprintf(stderr, "Error: Trying to load more textures than allocated space.\n");
		exit(1);
	}

	for (int i = 0; i < num_textures; i++)
	{
		char path[256];
		sprintf(path, path_format, i);  // This is correct, as it will generate 001 to 013

		game->land_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->land_texture[i].width, &game->land_texture[i].height);
		if (game->land_texture[i].img == NULL)
		{
			fprintf(stderr, "Error: Could not load opening texture: %s\n", path);
			exit(1);
		}
		game->land_texture[i].data = mlx_get_data_addr(game->land_texture[i].img, &game->land_texture[i].tex_bpp, &game->land_texture[i].tex_line_len, &game->land_texture[i].tex_endian);
	}
	printf("Loaded landing textures\n");  // Changed to print the actual file number

}

void load_outro_textures(t_game *game, const char *path_format, int num_textures)
{
	if (num_textures > MAX_OUTRO_TEXTURES) {
		fprintf(stderr, "Error: Trying to load more textures than allocated space.\n");
		exit(1);
	}

	for (int i = 0; i < num_textures; i++)
	{
		char path[256];
		sprintf(path, path_format, i);  // This is correct, as it will generate 001 to 013

		game->outro_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->outro_texture[i].width, &game->outro_texture[i].height);
		if (game->outro_texture[i].img == NULL)
		{
			fprintf(stderr, "Error: Could not load opening texture: %s\n", path);
			exit(1);
		}
		game->outro_texture[i].data = mlx_get_data_addr(game->outro_texture[i].img, &game->outro_texture[i].tex_bpp, &game->outro_texture[i].tex_line_len, &game->outro_texture[i].tex_endian);
	}
	printf("Loaded outro textures\n");  // Changed to print the actual file number

}

void load_collectible_texture(t_game *game, const char *texture_path)
{
	printf("Loading collectible texture: %s\n", texture_path);

	game->coll_texture[0].img = mlx_xpm_file_to_image(
		game->mlx_ptr,
		(char *)texture_path,
		&game->coll_texture[0].width,
		&game->coll_texture[0].height);

	if (!game->coll_texture[0].img)
	{
		fprintf(stderr, "Failed to load collectible texture: %s\n", texture_path);
		exit(EXIT_FAILURE);
	}

	game->coll_texture[0].data = mlx_get_data_addr(
		game->coll_texture[0].img,
		&game->coll_texture[0].tex_bpp,
		&game->coll_texture[0].tex_line_len,
		&game->coll_texture[0].tex_endian);

	printf("Loaded object texture: %s, bpp: %d, size: %dx%d\n",
		   texture_path, game->coll_texture[0].tex_bpp,
		   game->coll_texture[0].width, game->coll_texture[0].height);
}
