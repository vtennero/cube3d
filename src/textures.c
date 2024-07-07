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

// void preload_textures(t_game *game)
// {

//     char *texture_paths[] = {
//         "textures/foilagewall01.xpm", // NORTH
//         "textures/dmgwall07.xpm",     // EAST
//         "textures/dmgwall01.xpm",     // SOUTH
//         "textures/dmgwall06.xpm",     // WEST
//         "textures/sky02.xpm",
//         "textures/floor/main01.xpm",
//         "textures/floor/main01.xpm",
//         "textures/floor/main01.xpm",
//         "textures/floor/main01.xpm",
//         "textures/floor/main01.xpm",
//         "textures/floor/main01.xpm",
//         "textures/floor/main01.xpm",
//         "textures/floor/main01.xpm",
//         // "textures/floor/main02.xpm",
//         // "textures/floor/main03.xpm",
//         // "textures/floor/main04.xpm",
//         // "textures/floor/metal01.xpm",
//         // "textures/floor/metal02.xpm",
//         // "textures/floor/sand01.xpm",
//         // "textures/floor/sand02.xpm"
//     };

//     printf("preload_textures START\n");
//     for (int i = NORTH; i <= WEST; i++)
//     {
//         printf("preload_textures for (int i = NORTH; i <= WEST; i++)\n");
//         game->walltextures[i].img = mlx_xpm_file_to_image(
//             game->mlx_ptr,
//             texture_paths[i],
//             &game->walltextures[i].width,
//             &game->walltextures[i].height);

//         if (!game->walltextures[i].img)
//         {
//             fprintf(stderr, "Failed to load texture: %s\n", texture_paths[i]);
//             exit(EXIT_FAILURE);
//         }
//         else
//         {
//             game->walltextures[i].data = mlx_get_data_addr(
//                 game->walltextures[i].img,
//                 &game->walltextures[i].tex_bpp,
//                 &game->walltextures[i].tex_line_len,
//                 &game->walltextures[i].tex_endian);
//             printf("Loaded texture: %s, bpp: %d, size: %dx%d\n", texture_paths[i], game->walltextures[i].tex_bpp, game->walltextures[i].width, game->walltextures[i].height);
//         }
//     }
//     // Load the sky texture directly into the array
//     game->skytexture[0].img = mlx_xpm_file_to_image(
//         game->mlx_ptr,
//         texture_paths[4],
//         &game->skytexture[0].width,
//         &game->skytexture[0].height);
//     game->skytexture[0].data = mlx_get_data_addr(
//         game->skytexture[0].img,
//         &game->skytexture[0].tex_bpp,
//         &game->skytexture[0].tex_line_len,
//         &game->skytexture[0].tex_endian);
//     printf("Loaded sky texture, bpp: %d, size: %dx%d\n", game->skytexture[0].tex_bpp, game->skytexture[0].width, game->skytexture[0].height);

//     // Load the floor texture
//     for (int i = 0; i < MAX_FLOOR_TEXTURES; i++)
//     {
//         load_floor_texture(game, i, texture_paths[i + 5]);
//     }

//     printf("preload_textures END\n");
// }

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

    printf("preload_textures END\n");
}