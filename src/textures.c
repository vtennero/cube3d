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

void load_enemy_textures(t_game *game, const char *path_format, int num_textures)
{
    if (num_textures > NUM_ENEMY_TEXTURES) {
        fprintf(stderr, "Error: Trying to load more textures than allocated space.\n");
        exit(1);
    }

    for (int i = 0; i < num_textures; i++)
    {
        char path[256];
        sprintf(path, path_format, i + 1);  // This is correct, as it will generate 001 to 013

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
        game->opening_texture[i].data = mlx_get_data_addr(game->opening_texture[i].img, &game->opening_texture[i].tex_bpp, &game->opening_texture[i].tex_line_len, &game->enemy_textures[i].tex_endian);
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
        game->land_texture[i].data = mlx_get_data_addr(game->land_texture[i].img, &game->land_texture[i].tex_bpp, &game->land_texture[i].tex_line_len, &game->enemy_textures[i].tex_endian);
    }
    printf("Loaded opening textures\n");  // Changed to print the actual file number

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

// void load_single_texture(t_game *game, const char *texture_path, int index)
// {
//     printf("Loading object texture %d: %s\n", index, texture_path);

//     game->obj_texture[index].img = mlx_xpm_file_to_image(
//         game->mlx_ptr,
//         (char *)texture_path,
//         &game->obj_texture[index].width,
//         &game->obj_texture[index].height);

//     if (!game->obj_texture[index].img)
//     {
//         fprintf(stderr, "Failed to load object texture %d: %s\n", index, texture_path);
//         exit(EXIT_FAILURE);
//     }

//     game->obj_texture[index].data = mlx_get_data_addr(
//         game->obj_texture[index].img,
//         &game->obj_texture[index].tex_bpp,
//         &game->obj_texture[index].tex_line_len,
//         &game->obj_texture[index].tex_endian);

//     printf("Loaded object texture %d: %s, bpp: %d, size: %dx%d\n",
//            index, texture_path, game->obj_texture[index].tex_bpp,
//            game->obj_texture[index].width, game->obj_texture[index].height);
// }

// void load_obj_textures(t_game *game)
// {
//     char *texture_paths[] = {
//         "textures/enemies/stalker01.xpm",
//         "textures/enemies/stalker02.xpm",
//         "textures/enemies/stalker03.xpm",
//     };
    
//     for (int i = 0; i < 3; i++)
//     {
//         load_single_texture(game, texture_paths[i], i);
//     }
// }

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

// void load_floor_texture(t_game *game, int index, char *path)
// {
//     game->floortextures[index].img = mlx_xpm_file_to_image(
//         game->mlx_ptr,
//         path,
//         &game->floortextures[index].width,
//         &game->floortextures[index].height);
//     game->floortextures[index].data = mlx_get_data_addr(
//         game->floortextures[index].img,
//         &game->floortextures[index].tex_bpp,
//         &game->floortextures[index].tex_line_len,
//         &game->floortextures[index].tex_endian);
//     printf("Loaded floor texture %d, bpp: %d, size: %dx%d\n",
//            index, game->floortextures[index].tex_bpp,
//            game->floortextures[index].width, game->floortextures[index].height);
// }

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

    load_floor_textures(game);
    load_collectible_texture(game, "textures/collectibles/collectible01.xpm");
    // load_obj_textures(game);
    // load_obj_texture(game, "textures/collectibles/collectible01.xpm");
    load_gun_textures(game, "textures/gun/frame%02d.xpm", 12);
    load_enemy_textures(game, "textures/enemies/%03d.xpm", NUM_ENEMY_TEXTURES);
    load_menu_texture(game, "textures/menu/menu.xpm");
    load_opening_textures(game, "textures/jump/xpm/jump%03d.xpm", MAX_OPENING_TEXTURES);
    load_land_textures(game, "textures/land/land%03d.xpm", MAX_LAND_TEXTURES);
    load_extract_texture(game, "textures/extract/extract.xpm");

    scale_gun_textures(game);

    printf("preload_textures END\n");
}