/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus05.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:09:12 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/29 16:19:06 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calculate_perpendicular(t_game *game, float *perp_x, float *perp_y)
{
	float	view_angle;

	view_angle = atan2(game->player->direction.y, game->player->direction.x);
	*perp_x = -sin(view_angle);
	*perp_y = cos(view_angle);
}

void	render_single_tile(t_game *game, t_vector2d tile_pos, int tex_index)
{
	t_texture	*e_txt;

	e_txt = &game->e_txt[tex_index];
	render_sprite_common(game, tile_pos, e_txt);
}

void	calculate_widths(t_game *game, float distance, int *total_width, \
int *white_width)
{
	*total_width = (int)(0.05 * game->screen_width / distance);
	if (*total_width < 3)
		*total_width = 3;
	if (*total_width < 3)
		*white_width = 1;
	else
		*white_width = *total_width / 2;
}

void	draw_stripe_pixel(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < game->screen_width)
		img_pix_put(&game->img, x, y, color);
}

void	draw_extract_stripe(t_game *game, int s, int start_y, float d)
{
	int	total_width;
	int	white_width;
	int	y;
	int	i;
	int	color;

	calculate_widths(game, d, &total_width, &white_width);
	y = 0;
	while (y < start_y)
	{
		i = -total_width / 2;
		while (i < total_width / 2)
		{
			color = calculate_color_with_base \
			(i, total_width, white_width, 0x0000FF);
			draw_stripe_pixel(game, s + i, y, color);
			i++;
		}
		y++;
	}
}
