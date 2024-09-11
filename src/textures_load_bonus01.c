/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures02_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:13:26 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 17:12:31 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void load_gun_textures(t_game *game)
{
    game->gun_textures = malloc(sizeof(t_texture) * MAX_GUN_TEXTURES);
    char path[] = "textures/gun/frame00.xpm";
    char *digits = &path[18];
    int frame = 1;

    // printf("Starting to load gun textures\n");

    while (frame <= MAX_GUN_TEXTURES)
    {
        digits[0] = '0' + (frame / 10);
        digits[1] = '0' + (frame % 10);

        // printf("Attempting to load: %s\n", path);

        game->gun_textures[frame - 1].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->gun_textures[frame - 1].width, &game->gun_textures[frame - 1].height);
        if (game->gun_textures[frame - 1].img == NULL)
        {
            printf("Failed to load: %s\n", path);
            game->num_gun_frames = frame - 1;
            break;
        }
        else
        // {
            // printf("Successfully loaded: %s\n", path);
        // }

        game->gun_textures[frame - 1].data = mlx_get_data_addr(game->gun_textures[frame - 1].img, &game->gun_textures[frame - 1].tex_bpp, &game->gun_textures[frame - 1].tex_line_len, &game->gun_textures[frame - 1].tex_endian);
        frame++;
    }

    if (frame > MAX_GUN_TEXTURES)
        game->num_gun_frames = MAX_GUN_TEXTURES;

    printf("Total gun textures loaded: %d\n", game->num_gun_frames);

    if (game->num_gun_frames == 0)
    {
        fprintf(stderr, "Error: No gun textures loaded\n");
        // exit(1);
    }
}

int load_extract_textures(t_game *game)
{
	static char *file_names[] = {
		"textures/extract/extract00.xpm",
		"textures/extract/extract01.xpm",
		"textures/extract/extract02.xpm",
		"textures/extract/extract03.xpm"
	};
	const int num_textures = sizeof(file_names) / sizeof(file_names[0]);

	for (int i = 0; i < num_textures; i++)
	{
		t_texture *texture = &game->extract_texture[i];

		texture->path = file_names[i];
		texture->img = mlx_xpm_file_to_image(game->mlx_ptr, texture->path, &texture->width, &texture->height);
		if (!texture->img)
			return (0);
		texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp, &texture->tex_line_len, &texture->tex_endian);
	}

	return (1);
}

void load_floor_textures(t_game *game)
{
	char *floor_texture_paths[] = {
		"textures/floor/main01.xpm",
		"textures/floor/main02.xpm",
		"textures/floor/main03.xpm",
		"textures/floor/main04.xpm",
		"textures/floor/metal01.xpm",
		"textures/floor/metal02.xpm",
		"textures/floor/sand01.xpm",
		"textures/floor/sand02.xpm"};

	for (int i = 0; i < MAX_FLOOR_TEXTURES; i++)
	{
		game->floortextures[i].img = mlx_xpm_file_to_image(
			game->mlx_ptr,
			floor_texture_paths[i],
			&game->floortextures[i].width,
			&game->floortextures[i].height);

		if (!game->floortextures[i].img)
		{
			fprintf(stderr, "Failed to load floor texture: %s\n", floor_texture_paths[i]);
			exit(EXIT_FAILURE);
		}

		game->floortextures[i].data = mlx_get_data_addr(
			game->floortextures[i].img,
			&game->floortextures[i].tex_bpp,
			&game->floortextures[i].tex_line_len,
			&game->floortextures[i].tex_endian);

		printf("Loaded floor texture %d: %s, bpp: %d, size: %dx%d\n",
			   i, floor_texture_paths[i], game->floortextures[i].tex_bpp,
			   game->floortextures[i].width, game->floortextures[i].height);
	}
}

int load_extract_texture(t_game *game, char *path)
{
	t_texture *texture = &game->extract_texture[0];
	texture->path = path;
	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->width, &texture->height);
	if (!texture->img)
		return (0);
	texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp, &texture->tex_line_len, &texture->tex_endian);
	return (1);
}

int load_menu_texture(t_game *game, char *path)
{
	t_texture *texture = &game->menu_texture[0];
	texture->path = path;
	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->width, &texture->height);
	if (!texture->img)
		return (0);
	texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp, &texture->tex_line_len, &texture->tex_endian);
	return (1);
}
