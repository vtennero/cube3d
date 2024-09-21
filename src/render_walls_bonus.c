/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:42:52 by root              #+#    #+#             */
/*   Updated: 2024/07/09 18:51:13 by root             ###   ########.fr       */
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
	pixel_pos = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
	if (pixel_pos < 0 || pixel_pos >= (texture->height
			* texture->tex_line_len))
		return (0xFF0000);
	color = *(int *)(texture->data + pixel_pos);
	return (color);
}

void	update_tex_pos(double *texPos, double step)
{
	*texPos += step;
}

double	calculate_tex_step(t_texture *texture, double lineHeight)
{
	return (1.0 * texture->height / lineHeight);
}

double	calculate_initial_tex_pos(t_ray *ray, t_game *game, double step)
{
	return ((ray->draw_start - (int)(game->player->pitch * game->screen_height)
		- (int)(game->player->height * game->screen_height
		/ ray->perpWallDist) - game->screen_height / 2 + ray->lineHeight
			/ 2) * step);
}

void	render_ray(t_img *img, t_ray ray, t_texture *texture, t_game *game)
{
	int	y;
	int	texY;
	int	color;
	int texX;
	double step;
	double texPos;

	step = calculate_tex_step(texture, ray.lineHeight);
	texPos = calculate_initial_tex_pos(&ray, game, step);
	y = ray.draw_start;
	while (y < ray.draw_end)
	{
		texY = (int)texPos & (texture->height - 1);
		texPos += step;
		// update_tex_pos(&texPos, step);
		texX = (int)((double)ray.texX * texture->width / 1024) & (texture->width
				- 1);
		color = get_texture_color(texture, texX, texY);
		img_pix_put(img, ray.x, y, color);
		y++;
	}
}

void	render_walls(t_game *game)
{
	t_ray_node *current;
	t_texture *used_texture;

	current = game->ray_list;
	while (current != NULL)
	{
		used_texture = &game->walltextures[current->ray.wall_face];
		render_ray(&game->img, current->ray, used_texture, game);
		current = current->next;
	}
}
