/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:04:58 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:04:58 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_ray(t_img *img, t_ray ray, t_texture *texture, t_game *game)
{
	t_vector2d	pos;
	t_vector2d	tex;
	int			color;
	double		step;
	double		tex_pos;

	step = calculate_tex_step(texture, ray.line_h);
	tex_pos = calculate_initial_tex_pos(&ray, game, step);
	pos.y = ray.draw_start;
	while (pos.y < ray.draw_end)
	{
		tex.y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		tex.x = (int)((double)ray.tex_x * texture->width \
		/ 1024) & (texture->width - 1);
		color = get_texture_color(texture, tex.x, tex.y);
		img_pix_put(img, ray.x, pos.y, color);
		pos.y++;
	}
}

void	render_walls(t_game *game)
{
	t_ray_node	*current;
	t_texture	*used_texture;

	current = game->ray_list;
	while (current != NULL)
	{
		used_texture = &game->walltextures[current->ray.wall_face];
		render_ray(&game->img, current->ray, used_texture, game);
		current = current->next;
	}
}
