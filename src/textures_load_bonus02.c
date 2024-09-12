/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures03_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:13:29 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 17:14:05 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int load_pelican_inside_texture(t_game *game, char *path)
{
    ft_printf("Loading ship texture\t\t\t[#");
    t_texture *texture = &game->pelican_inside[0];
    texture->path = path;
    texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->width, &texture->height);
    if (!texture->img)
        return (0);
    texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp, &texture->tex_line_len, &texture->tex_endian);
    printf("#############################] 100.0%%\n");
    return (1);
}

int load_supplies_texture(t_game *game, char *path)
{
    printf("Loading supplies texture\t\t[#");
    t_texture *texture = &game->supplies_texture[0];
    texture->path = path;
    texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->width, &texture->height);
    if (!texture->img)
        return (0);
    texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp, &texture->tex_line_len, &texture->tex_endian);
    printf("#############################] 100.0%%\n");
    return (1);
}

void load_strike_textures(t_game *game)
{
    const char *path_format = "textures/strike/%02d.xpm";
    int num_textures = NUM_AIRSTRIKE_FRAMES;

    for (int i = 0; i < num_textures; i++)
    {
        char path[256];
        sprintf(path, path_format, i);

        game->airstrike_textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->airstrike_textures[i].width, &game->airstrike_textures[i].height);
        game->airstrike_textures[i].data = mlx_get_data_addr(game->airstrike_textures[i].img, &game->airstrike_textures[i].tex_bpp, &game->airstrike_textures[i].tex_line_len, &game->airstrike_textures[i].tex_endian);

        update_progress_bar(i + 1, num_textures, "Loading strike textures");
    }
}

void load_napalm_textures(t_game *game)
{
    const char *path_format = "textures/strike/napalm%02d.xpm";
    int num_textures = NUM_NAPALM_FRAMES;

    for (int i = 0; i < num_textures; i++)
    {
        char path[256];
        sprintf(path, path_format, i);

        game->napalm_textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->napalm_textures[i].width, &game->napalm_textures[i].height);
        game->napalm_textures[i].data = mlx_get_data_addr(game->napalm_textures[i].img, &game->napalm_textures[i].tex_bpp, &game->napalm_textures[i].tex_line_len, &game->napalm_textures[i].tex_endian);

        update_progress_bar(i + 1, num_textures, "Loading napalm textures");
    }
}

void load_shooting_textures(t_game *game)
{
    for (int i = 0; i < MAX_SHOOTING_TEXTURES; i++)
    {
        char path[] = "textures/gun/shooting/frame00.xpm";
        path[27] = '0' + i / 10;
        path[28] = '0' + i % 10;

        game->shooting_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->shooting_texture[i].width, &game->shooting_texture[i].height);
        game->shooting_texture[i].data = mlx_get_data_addr(game->shooting_texture[i].img, &game->shooting_texture[i].tex_bpp, &game->shooting_texture[i].tex_line_len, &game->shooting_texture[i].tex_endian);

        update_progress_bar(i + 1, MAX_SHOOTING_TEXTURES, "Loading shooting textures");
    }
}

