/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:16:06 by root              #+#    #+#             */
/*   Updated: 2024/07/10 13:04:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_normal_gun_frame(t_game *game)
{
	int	frames_per_switch;

	frames_per_switch = 4;
	if (game->normal_gun_frame_counter >= frames_per_switch)
	{
		game->current_gun_frame = (game->current_gun_frame \
		+ 1) % game->num_gun_frames;
		game->normal_gun_frame_counter = 0;
	}
	game->normal_gun_frame_counter++;
}

void	update_shooting_gun_frame(t_game *game)
{
	int	frames_per_switch;
	int	num_shooting_frames;

	frames_per_switch = 4;
	num_shooting_frames = 4;
	if (game->shooting_gun_frame_counter >= frames_per_switch)
	{
		game->current_shooting_frame \
		= (game->current_shooting_frame + 1) % num_shooting_frames;
		game->shooting_gun_frame_counter = 0;
	}
	game->shooting_gun_frame_counter++;
}

t_texture	*select_gun_texture(t_game *game)
{
	if (game->is_shooting)
		return (&game->sht_txture[game->current_shooting_frame]);
	else
		return (&game->gun_textures[game->current_gun_frame]);
}

void	calculate_gun_position(t_game *game, t_texture \
*gun_texture, t_vector2d *start)
{
	int	offset;

	offset = gun_texture->width / 4;
	start->x = game->screen_width - gun_texture->width + offset;
	start->y = game->screen_height - gun_texture->height;
}

void	draw_gun_pixel(t_game *game, t_texture *gun_texture, \
t_vector2d start, t_vector2d pos)
{
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = pos.x;
	tex_y = pos.y;
	color = *(int *)(gun_texture->data + (tex_y \
	* gun_texture->tex_line_len + tex_x * (gun_texture->tex_bpp / 8)));
	if ((unsigned int)color != 0xFF000000)
		img_pix_put(&game->img, start.x + pos.x, start.y + pos.y, color);
}

void	update_gun_state(t_game *game)
{
	if (game->is_shooting)
		update_shooting_gun_frame(game);
	else
	{
		if (game->is_moving_fwd)
			update_normal_gun_frame(game);
	}
}

void	render_gun(t_game *game)
{
	t_texture	*gun_texture;
	t_vector2d	start;
	t_vector2d	size;
	t_vector2d	pos;

	gun_texture = select_gun_texture(game);
	calculate_gun_position(game, gun_texture, &start);
	size.x = gun_texture->width;
	size.y = gun_texture->height;
	pos.y = 0;
	while (pos.y < size.y)
	{
		pos.x = 0;
		while (pos.x < size.x)
		{
			if (start.x + pos.x < game->screen_width)
				draw_gun_pixel(game, gun_texture, start, pos);
			pos.x++;
		}
		pos.y++;
	}
}
