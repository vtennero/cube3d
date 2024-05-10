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

// void preload_textures(t_game *game) {


    
//     char *texture_paths[] = {
//         "textures/bluestone.xpm",   // NORTH
//         "textures/eagle.xpm",       // EAST
//         "textures/greystone.xpm",   // SOUTH
//         "textures/wood.xpm"         // WEST
//     };

//     printf("preload_textures START\n");
//     game->mlx_ptr = mlx_init();
//     game->win_ptr = mlx_new_window(game->mlx_ptr, game->screen_width, game->screen_height, "MLX Window");
//     for (int i = NORTH; i <= WEST; i++)
//     {
//         game->walltextures[i].img = mlx_xpm_file_to_image(
//             game->mlx_ptr, 
//             texture_paths[i], 
//             &game->walltextures[i].width, 
//             &game->walltextures[i].height
//         );

//         if (!game->walltextures[i].img) {
//             fprintf(stderr, "Failed to load texture: %s\n", texture_paths[i]);
//         } else {
//             fprintf(stdout, "Loaded texture: %s, size: %dx%d\n", texture_paths[i], game->walltextures[i].width, game->walltextures[i].height);
//         }
//     }
//     printf("preload_textures END\n");

// }

void preload_textures(t_game *game) {
    // char *texture_paths[] = {
    //     "textures/bluestone.xpm",   // NORTH
    //     "textures/eagle.xpm",       // EAST
    //     "textures/greystone.xpm",   // SOUTH
    //     "textures/wood.xpm",         // WEST
    //     "textures/sky02.xpm"
    // };

        char *texture_paths[] = {
        "textures/foilagewall01.xpm",   // NORTH
        "textures/dmgwall07.xpm",       // EAST
        "textures/dmgwall01.xpm",   // SOUTH
        "textures/dmgwall06.xpm",         // WEST
        "textures/sky02.xpm",
        "textures/floor/vertopal.com_half03.xpm"  
    };

    printf("preload_textures START\n");
    for (int i = NORTH; i <= WEST; i++)
    {
        printf("preload_textures for (int i = NORTH; i <= WEST; i++)\n");
        game->walltextures[i].img = mlx_xpm_file_to_image(
            game->mlx_ptr, 
            texture_paths[i], 
            &game->walltextures[i].width, 
            &game->walltextures[i].height
        );

        if (!game->walltextures[i].img) {
            fprintf(stderr, "Failed to load texture: %s\n", texture_paths[i]);
            exit(EXIT_FAILURE);
        } else {
            game->walltextures[i].data = mlx_get_data_addr(
                game->walltextures[i].img,
                &game->walltextures[i].tex_bpp,
                &game->walltextures[i].tex_line_len,
                &game->walltextures[i].tex_endian
            );
            printf("Loaded texture: %s, bpp: %d, size: %dx%d\n", texture_paths[i], game->walltextures[i].tex_bpp, game->walltextures[i].width, game->walltextures[i].height);
        }
    }
    // Load the sky texture directly into the array
    game->skytexture[0].img = mlx_xpm_file_to_image(
        game->mlx_ptr, 
        texture_paths[4], 
        &game->skytexture[0].width, 
        &game->skytexture[0].height
    );
    game->skytexture[0].data = mlx_get_data_addr(
        game->skytexture[0].img,
        &game->skytexture[0].tex_bpp,
        &game->skytexture[0].tex_line_len,
        &game->skytexture[0].tex_endian
    );
    printf("Loaded sky texture, bpp: %d, size: %dx%d\n", game->skytexture[0].tex_bpp, game->skytexture[0].width, game->skytexture[0].height);

        // Load the floor texture
    game->floortexture[0].img = mlx_xpm_file_to_image(
        game->mlx_ptr, 
        texture_paths[5], 
        &game->floortexture[0].width, 
        &game->floortexture[0].height
    );
    game->floortexture[0].data = mlx_get_data_addr(
        game->floortexture[0].img,
        &game->floortexture[0].tex_bpp,
        &game->floortexture[0].tex_line_len,
        &game->floortexture[0].tex_endian
    );
    printf("Loaded floor texture, bpp: %d, size: %dx%d\n", game->floortexture[0].tex_bpp, game->floortexture[0].width, game->floortexture[0].height);

    printf("preload_textures END\n");
}






// unused
void set_texture(t_game *game, t_direction dir)
{
    if (!game) 
        return;
    if (dir < NORTH || dir > WEST)
        return;
    free(game->walltextures[dir].path);
    game->walltextures[dir].path = NULL;
    const char *texture_paths[] = {
        "bluestone.xpm",
        "eagle.xpm",
        "greystone.xpm",
        "wood.xpm"
    };
    game->walltextures[dir].path = ft_strdup(texture_paths[dir]);
}
