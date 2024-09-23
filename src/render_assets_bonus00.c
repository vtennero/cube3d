/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus00.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:11:16 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:11:16 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	* gun_texture->line_len + tex_x * (gun_texture->bpp / 8)));
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
