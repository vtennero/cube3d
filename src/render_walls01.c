/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:04:51 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:04:51 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_texture_color(t_texture *texture, int x, int y)
{
	int	pixel_pos;
	int	color;

	if (texture->width == 0 || texture->height == 0 || texture->data == NULL)
		return (0xFF0000);
	x = x % texture->width;
	y = y % texture->height;
	pixel_pos = y * texture->line_len + x * (texture->bpp / 8);
	if (pixel_pos < 0 || pixel_pos >= (texture->height
			* texture->line_len))
		return (0xFF0000);
	color = *(int *)(texture->data + pixel_pos);
	return (color);
}

void	update_tex_pos(double *tex_pos, double step)
{
	*tex_pos += step;
}

double	calculate_tex_step(t_texture *texture, double line_h)
{
	return (1.0 * texture->height / line_h);
}

double	calculate_initial_tex_pos(t_ray *ray, t_game *game, double step)
{
	return ((ray->draw_start - (int)(game->player->pitch * game->screen_height)
		- (int)(game->player->height * game->screen_height
		/ ray->perpwalldist) - game->screen_height / 2 + ray->line_h
			/ 2) * step);
}
