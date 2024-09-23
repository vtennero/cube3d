/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:50:35 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/20 16:50:35 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	calc_camera_x(t_game *game, t_ray_node *ray)
{
	ray->ray.camera_x = 2 * ray->ray.x / (double)(game->screen_width) - 1;
}

void	calc_ray_dir_x(t_game *game, t_ray_node *ray)
{
	ray->ray.ray_dir_x = game->player->direction.x + game->player->plane.x * \
	ray->ray.camera_x;
}

void	calc_ray_dir_y(t_game *game, t_ray_node *ray)
{
	ray->ray.ray_dir_y = game->player->direction.y + game->player->plane.y * \
	ray->ray.camera_x;
}

void	calc_map_x(t_game *game, t_ray_node *ray)
{
	ray->ray.map_x = (int)game->player->position.x;
}

void	calc_map_y(t_game *game, t_ray_node *ray)
{
	ray->ray.map_y = (int)game->player->position.y;
}

void	calc_side_dist_x(t_game *game, t_ray_node *ray)
{
	if (ray->ray.ray_dir_x == 0)
		ray->ray.delta_d_x = 1e30;
	else
		ray->ray.delta_d_x = fabs(1 / ray->ray.ray_dir_x);
	if (ray->ray.ray_dir_x < 0)
	{
		ray->ray.step_x = -1;
		ray->ray.side_d_x = (game->player->position.x - ray->ray.map_x) \
		* ray->ray.delta_d_x;
	}
	else
	{
		ray->ray.step_x = 1;
		ray->ray.side_d_x = (ray->ray.map_x + 1.0 - game->player->position.x) \
		* ray->ray.delta_d_x;
	}
}

void	calc_side_dist_y(t_game *game, t_ray_node *ray)
{
	if (ray->ray.ray_dir_y == 0)
		ray->ray.delta_d_y = 1e30;
	else
		ray->ray.delta_d_y = fabs(1 / ray->ray.ray_dir_y);
	if (ray->ray.ray_dir_y < 0)
	{
		ray->ray.step_y = -1;
		ray->ray.side_d_y = (game->player->position.y - ray->ray.map_y) \
		* ray->ray.delta_d_y;
	}
	else
	{
		ray->ray.step_y = 1;
		ray->ray.side_d_y = (ray->ray.map_y + 1.0 - game->player->position.y) \
		* ray->ray.delta_d_y;
	}
}

void	calc_side_dist(t_game *game, t_ray_node *ray)
{
	calc_side_dist_x(game, ray);
	calc_side_dist_y(game, ray);
}

void	calc_delta_dist(t_game *game, t_ray_node *ray)
{
	(void)game;
	if (ray->ray.ray_dir_x == 0)
		ray->ray.delta_d_x = 1e30;
	else
		ray->ray.delta_d_x = fabs(1 / ray->ray.ray_dir_x);
	if (ray->ray.ray_dir_y == 0)
		ray->ray.delta_d_y = 1e30;
	else
		ray->ray.delta_d_y = fabs(1 / ray->ray.ray_dir_y);
}

int	is_out_of_bounds(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= game->map->width \
	|| ray->map_y < 0 || ray->map_y >= game->map->height)
		return (1);
	else
		return (0);
}

int	is_within_map_bounds(t_game *game, int x, int y)
{
	if (x >= 0 && x < game->map->width && y >= 0 && y < game->map->height)
		return (1);
	else
		return (0);
}

void	update_ray_x(t_ray *ray)
{
	ray->side_d_x += ray->delta_d_x;
	ray->map_x += ray->step_x;
	ray->side = 0;
}

void	update_ray_y(t_ray *ray)
{
	ray->side_d_y += ray->delta_d_y;
	ray->map_y += ray->step_y;
	ray->side = 1;
}

void	handle_corner_case(t_game *game, t_ray *ray, int next_x, int next_y)
{
	if (game->map->data[next_x][ray->map_y] == 1
		&& game->map->data[ray->map_x][next_y] == 1)
		update_ray_x(ray);
	else if (game->map->data[next_x][ray->map_y] == 1)
		update_ray_y(ray);
	else
	{
		update_ray_x(ray);
	}
}

void	handle_epsilon_case(t_game *game, t_ray *ray)
{
	int	next_x;
	int	next_y;

	next_x = ray->map_x + ray->step_x;
	next_y = ray->map_y + ray->step_y;
	if (is_within_map_bounds(game, next_x, next_y))
	{
		handle_corner_case(game, ray, next_x, next_y);
	}
}

void	move_ray(t_ray *ray)
{
	if (ray->side_d_x < ray->side_d_y)
	{
		ray->side_d_x += ray->delta_d_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_d_y += ray->delta_d_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	set_wall_face(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->wall_face = EAST;
		else
			ray->wall_face = WEST;
	}
	else
	{
		if (ray->step_y > 0)
			ray->wall_face = SOUTH;
		else
			ray->wall_face = NORTH;
	}
}

int	is_wall(t_game *game, int map_y, int map_x)
{
	if (game->map->data[map_y][map_x] == 1)
		return (1);
	else
		return (0);
}

int	is_space_to_wall_transition(t_game *game, t_ray *ray, \
int prev_map_x, int prev_map_y)
{
	if ((prev_map_x != ray->map_x || prev_map_y != ray->map_y)
		&& !is_wall(game, prev_map_y, prev_map_x)
		&& is_wall(game, ray->map_y, ray->map_x))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	adjust_ray_position(t_ray *ray, int *prev_map_x, int *prev_map_y)
{
	if (ray->side == 0)
	{
		ray->side_d_x -= ray->delta_d_x;
		ray->map_x = *prev_map_x;
	}
	else
	{
		ray->side_d_y -= ray->delta_d_y;
		ray->map_y = *prev_map_y;
	}
}

int	check_wall_hit(t_game *game, t_ray *ray, int *prev_map_x, int *prev_map_y)
{
	if (is_wall(game, ray->map_y, ray->map_x))
	{
		set_wall_face(ray);
		return (1);
	}
	else if (is_space_to_wall_transition(game, ray, *prev_map_x, *prev_map_y))
	{
		adjust_ray_position(ray, prev_map_x, prev_map_y);
		return (1);
	}
	*prev_map_x = ray->map_x;
	*prev_map_y = ray->map_y;
	return (0);
}

void	perform_dda(t_game *game, t_ray_node *ray)
{
	int	hit;
	int	step_count;
	int	prev_map_x;
	int	prev_map_y;

	hit = 0;
	step_count = 0;
	prev_map_x = ray->ray.map_x;
	prev_map_y = ray->ray.map_y;
	while (hit == 0 && step_count < 100)
	{
		if (is_out_of_bounds(game, &ray->ray))
		{
			hit = 1;
			break ;
		}
		if (fabs(ray->ray.side_d_x - ray->ray.side_d_y) < RAY_EPSILON)
			handle_epsilon_case(game, &ray->ray);
		else
			move_ray(&ray->ray);
		hit = check_wall_hit(game, &ray->ray, &prev_map_x, &prev_map_y);
		step_count++;
	}
}

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
