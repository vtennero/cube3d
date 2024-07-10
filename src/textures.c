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

void load_gun_textures(t_game *game, char *path_format, int num_frames)
{
    game->gun_textures = malloc(sizeof(t_texture) * num_frames);
    game->num_gun_frames = num_frames;

    for (int i = 0; i < num_frames; i++)
    {
        char path[256];
        sprintf(path, path_format, i + 1);

        game->gun_textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->gun_textures[i].width, &game->gun_textures[i].height);
        if (game->gun_textures[i].img == NULL)
        {
            fprintf(stderr, "Error: Could not load gun texture: %s\n", path);
            exit(1);
        }
        game->gun_textures[i].data = mlx_get_data_addr(game->gun_textures[i].img, &game->gun_textures[i].tex_bpp, &game->gun_textures[i].tex_line_len, &game->gun_textures[i].tex_endian);
    }
}

void load_floor_texture(t_game *game, int index, char *path)
{
    game->floortextures[index].img = mlx_xpm_file_to_image(
        game->mlx_ptr,
        path,
        &game->floortextures[index].width,
        &game->floortextures[index].height);
    game->floortextures[index].data = mlx_get_data_addr(
        game->floortextures[index].img,
        &game->floortextures[index].tex_bpp,
        &game->floortextures[index].tex_line_len,
        &game->floortextures[index].tex_endian);
    printf("Loaded floor texture %d, bpp: %d, size: %dx%d\n",
           index, game->floortextures[index].tex_bpp,
           game->floortextures[index].width, game->floortextures[index].height);
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

void preload_textures(t_game *game)
{
    char *wall_texture_paths[] = {
        "textures/foilagewall01.xpm", // NORTH
        "textures/dmgwall07.xpm",     // EAST
        "textures/dmgwall01.xpm",     // SOUTH
        "textures/dmgwall06.xpm",     // WEST
    };

    printf("preload_textures START\n");

    // Load wall textures
    for (int i = NORTH; i <= WEST; i++)
    {
        game->walltextures[i].img = mlx_xpm_file_to_image(
            game->mlx_ptr,
            wall_texture_paths[i],
            &game->walltextures[i].width,
            &game->walltextures[i].height);

        if (!game->walltextures[i].img)
        {
            fprintf(stderr, "Failed to load wall texture: %s\n", wall_texture_paths[i]);
            exit(EXIT_FAILURE);
        }

        game->walltextures[i].data = mlx_get_data_addr(
            game->walltextures[i].img,
            &game->walltextures[i].tex_bpp,
            &game->walltextures[i].tex_line_len,
            &game->walltextures[i].tex_endian);

        printf("Loaded wall texture: %s, bpp: %d, size: %dx%d\n",
               wall_texture_paths[i], game->walltextures[i].tex_bpp,
               game->walltextures[i].width, game->walltextures[i].height);
    }

    // Load sky texture
    game->skytexture[0].img = mlx_xpm_file_to_image(
        game->mlx_ptr,
        "textures/sky02.xpm",
        &game->skytexture[0].width,
        &game->skytexture[0].height);

    if (!game->skytexture[0].img)
    {
        fprintf(stderr, "Failed to load sky texture\n");
        exit(EXIT_FAILURE);
    }

    game->skytexture[0].data = mlx_get_data_addr(
        game->skytexture[0].img,
        &game->skytexture[0].tex_bpp,
        &game->skytexture[0].tex_line_len,
        &game->skytexture[0].tex_endian);

    printf("Loaded sky texture, bpp: %d, size: %dx%d\n",
           game->skytexture[0].tex_bpp, game->skytexture[0].width, game->skytexture[0].height);

    // Load floor textures
    load_floor_textures(game);
    // load_gun_texture(game, "textures/gun/frame01.xpm");
    load_gun_textures(game, "textures/gun/frame%02d.xpm", 12);

    scale_gun_textures(game);

    printf("preload_textures END\n");
}