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

void preload_textures(t_game *game) {


    
    char *texture_paths[] = {
        "textures/bluestone.xpm",   // NORTH
        "textures/eagle.xpm",       // EAST
        "textures/greystone.xpm",   // SOUTH
        "textures/wood.xpm"         // WEST
    };

    printf("preload_textures START\n");
    game->mlx_ptr = mlx_init();
    game->win_ptr = mlx_new_window(game->mlx_ptr, game->screen_width, game->screen_height, "MLX Window");
    for (int i = NORTH; i <= WEST; i++)
    {
        game->walltextures[i].img = mlx_xpm_file_to_image(
            game->mlx_ptr, 
            texture_paths[i], 
            &game->walltextures[i].width, 
            &game->walltextures[i].height
        );

        if (!game->walltextures[i].img) {
            fprintf(stderr, "Failed to load texture: %s\n", texture_paths[i]);
        } else {
            fprintf(stdout, "Loaded texture: %s, size: %dx%d\n", texture_paths[i], game->walltextures[i].width, game->walltextures[i].height);
        }
    }
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
