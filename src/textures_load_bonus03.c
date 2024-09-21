/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures04_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:13:32 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:17:55 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	scale_gun_textures(t_game *game)
{
	double		s_h;
	double		s_width;
	int			i;
	t_texture	*gun_texture;

	s_h = game->screen_height * 0.55;
	s_width = game->screen_width * 0.6;
	i = 0;
	while (i < game->num_gun_frames)
	{
		gun_texture = &game->gun_textures[i];
		gun_texture->height = (int)s_h;
		gun_texture->width = (int)(gun_texture->width * \
		(s_h / gun_texture->height));
		if (gun_texture->width > s_width)
		{
			gun_texture->width = (int)s_width;
			gun_texture->height = (int)(gun_texture->height * \
			(s_width / gun_texture->width));
		}
		i++;
	}
}

void	scale_shooting_textures(t_game *game)
{
	double		s_h;
	double		s_width;
	int			i;
	t_texture	*gun_texture;

	s_h = game->screen_height * 0.55;
	s_width = game->screen_width * 0.6;
	i = 0;
	while (i < game->num_gun_frames)
	{
		gun_texture = &game->sht_txture[i];
		gun_texture->height = (int)s_h;
		gun_texture->width = (int)(gun_texture->width * \
		(s_h / gun_texture->height));
		if (gun_texture->width > s_width)
		{
			gun_texture->width = (int)s_width;
			gun_texture->height = (int)(gun_texture->height * \
			(s_width / gun_texture->width));
		}
		i++;
	}
}

int	texture_err_message(t_game *game)
{
	printf("❌\n");
	return (game->text_err++);
}

int	load_sky_texture(t_game *game)
{
	char	path[18];

	printf("Loading sky texture\t\t\t[#");
	ft_strcpy(path, "textures/sky06.xpm");
	game->sky_texture.img = mlx_xpm_file_to_image(game->mlx_ptr, path, \
	&game->sky_texture.width, &game->sky_texture.height);
	if (!game->sky_texture.img)
		return (texture_err_message(game));
	game->sky_texture.data = mlx_get_data_addr(game->sky_texture.img, \
			&game->sky_texture.tex_bpp, &game->sky_texture.tex_line_len, \
			&game->sky_texture.tex_endian);
	printf("#############################] 100.0%%\n");
	return (0);
}
