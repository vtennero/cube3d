/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting04.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:31:18 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:35:15 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calc_perp_wall_dist(t_game *game, t_ray_node *ray)
{
	(void)game;
	if (ray->ray.side == 0)
		ray->ray.perpwalldist = (ray->ray.side_d_x - ray->ray.delta_d_x);
	else
		ray->ray.perpwalldist = (ray->ray.side_d_y - ray->ray.delta_d_y);
}

void	calc_line_height(t_game *game, t_ray_node *ray)
{
	ray->ray.line_h = (int)(game->screen_height / ray->ray.perpwalldist);
}

void	calc_draw_parameters(t_game *game, t_ray_node *ray)
{
	int	pitch_offset;
	int	height_offset;

	pitch_offset = (int)(game->player->pitch * game->screen_height);
	ray->ray.line_h = (int)(game->screen_height / ray->ray.perpwalldist);
	height_offset = (int)(game->player->height * game->screen_height \
	/ ray->ray.perpwalldist);
	ray->ray.draw_start = -ray->ray.line_h / 2 + game->screen_height \
	/ 2 + pitch_offset + height_offset;
	if (ray->ray.draw_start < 0)
		ray->ray.draw_start = 0;
	ray->ray.draw_end = ray->ray.line_h / 2 + game->screen_height \
	/ 2 + pitch_offset + height_offset;
	if (ray->ray.draw_end >= game->screen_height)
		ray->ray.draw_end = game->screen_height - 1;
}

void	calc_texture_x(t_game *game, t_ray_node *ray)
{
	int	texture_width;

	texture_width = game->walltextures[ray->ray.wall_face].width;
	ray->ray.tex_x = (int)(ray->ray.wall_x * (double)texture_width);
	if (ray->ray.side == 0 && ray->ray.ray_dir_x > 0)
		ray->ray.tex_x = texture_width - ray->ray.tex_x - 1;
	if (ray->ray.side == 1 && ray->ray.ray_dir_y < 0)
		ray->ray.tex_x = texture_width - ray->ray.tex_x - 1;
}

void	calc_wall_hit(t_game *game, t_ray_node *ray)
{
	double	wall_impact;

	if (ray->ray.side == 0)
	{
		wall_impact = game->player->position.y \
		+ ray->ray.perpwalldist * ray->ray.ray_dir_y;
	}
	else
	{
		wall_impact = game->player->position.x \
		+ ray->ray.perpwalldist * ray->ray.ray_dir_x;
	}
	wall_impact -= floor(wall_impact);
	ray->ray.wall_x = wall_impact;
}
