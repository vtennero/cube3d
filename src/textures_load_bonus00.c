/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_load_bonus00.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:26:20 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 16:26:20 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_outro_textures(t_game *game)
{
	char	path[27];
	int		f_dig;
	int		s_dig;
	int		t_dig;
	int		i;

	ft_strcpy(path, "textures/outro/outro000.xpm");
	get_last_three_digit_indexes(path, &f_dig, &s_dig, &t_dig);
	i = 0;
	while (i < MAX_OUTRO_TEXTURES)
	{
		path[f_dig] = '0' + (i / 100);
		path[s_dig] = '0' + ((i / 10) % 10);
		path[t_dig] = '0' + (i % 10);
		game->t_outro[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, \
		&game->t_outro[i].width, &game->t_outro[i].height);
		if (game->t_outro[i].img == NULL)
			return (texture_err_message(game));
		game->t_outro[i].data = mlx_get_data_addr(game->t_outro[i].img, \
		&game->t_outro[i].bpp, &game->t_outro[i].line_len, \
		&game->t_outro[i].endian);
		upd_prog_bar(game, i + 1, MAX_OUTRO_TEXTURES, "Loading outro textures");
		i++;
	}
	return (0);
}

int	load_enemy_textures(t_game *game)
{
	char	path[24];
	int		f_dig;
	int		s_dig;
	int		t_dig;
	int		i;

	ft_strcpy(path, "textures/enemies/000.xpm");
	get_last_three_digit_indexes(path, &f_dig, &s_dig, &t_dig);
	i = 0;
	while (i < E_T_N)
	{
		path[f_dig] = '0' + (i / 100);
		path[s_dig] = '0' + ((i / 10) % 10);
		path[t_dig] = '0' + (i % 10);
		game->enemy_textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr, \
		path, &game->enemy_textures[i].width, &game->enemy_textures[i].height);
		if (game->enemy_textures[i].img == NULL)
			return (texture_err_message(game));
		game->enemy_textures[i].data = mlx_get_data_addr(\
		game->enemy_textures[i].img, &game->enemy_textures[i].bpp, \
		&game->enemy_textures[i].line_len, &game->enemy_textures[i].endian);
		upd_prog_bar(game, i + 1, MAX_ENEMY_TEXTURES, "Loading enemy textures");
		i++;
	}
	return (0);
}

int	load_opening_textures(t_game *game)
{
	char	path[29];
	int		f_dig;
	int		s_dig;
	int		t_dig;
	int		i;

	ft_strcpy(path, "textures/jump/xpm/jump000.xpm");
	get_last_three_digit_indexes(path, &f_dig, &s_dig, &t_dig);
	i = 0;
	while (i < T_N_INTRO1)
	{
		path[f_dig] = '0' + (i / 100);
		path[s_dig] = '0' + ((i / 10) % 10);
		path[t_dig] = '0' + (i % 10);
		game->t_intro1[i].img = mlx_xpm_file_to_image(game->mlx_ptr, \
		path, &game->t_intro1[i].width, &game->t_intro1[i].height);
		if (game->t_intro1[i].img == NULL)
			return (texture_err_message(game));
		game->t_intro1[i].data = mlx_get_data_addr(game->t_intro1[i].img, \
		&game->t_intro1[i].bpp, &game->t_intro1[i].line_len, \
		&game->t_intro1[i].endian);
		upd_prog_bar(game, i + 1, T_N_INTRO1, "Loading opening textures");
		i++;
	}
	return (0);
}

int	load_land_textures(t_game *game)
{
	char	path[25];
	int		f_dig;
	int		s_dig;
	int		t_dig;
	int		i;

	ft_strcpy(path, "textures/land/land000.xpm");
	get_last_three_digit_indexes(path, &f_dig, &s_dig, &t_dig);
	i = 0;
	while (i < T_N_INTRO2)
	{
		path[f_dig] = '0' + (i / 100);
		path[s_dig] = '0' + ((i / 10) % 10);
		path[t_dig] = '0' + (i % 10);
		game->t_intro2[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, \
		&game->t_intro2[i].width, &game->t_intro2[i].height);
		if (game->t_intro2[i].img == NULL)
			return (texture_err_message(game));
		game->t_intro2[i].data = mlx_get_data_addr(game->t_intro2[i].img, \
		&game->t_intro2[i].bpp, &game->t_intro2[i].line_len, \
		&game->t_intro2[i].endian);
		upd_prog_bar(game, i + 1, T_N_INTRO2, "Loading land textures");
		i++;
	}
	return (0);
}

int	load_collectible_texture(t_game *game)
{
	char	path[39];

	upd_prog_bar(game, 0, 1, "Loading collectible texture");
	ft_strcpy(path, "textures/collectibles/collectible01.xpm");
	game->coll_texture[0].img = mlx_xpm_file_to_image(game->mlx_ptr, \
	(char *)path, &game->coll_texture[0].width, &game->coll_texture[0].height);
	if (!game->coll_texture[0].img)
		return (texture_err_message(game));
	game->coll_texture[0].data = mlx_get_data_addr(game->coll_texture[0].img, \
	&game->coll_texture[0].bpp, &game->coll_texture[0].line_len, \
	&game->coll_texture[0].endian);
	upd_prog_bar(game, 1, 1, "Loading collectible texture");
	return (0);
}
