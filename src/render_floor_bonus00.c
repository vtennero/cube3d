/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:41:48 by toto              #+#    #+#             */
/*   Updated: 2024/05/10 16:26:55 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_floor_line(t_game *game, t_floor_ray *floor_ray, int y)
{
	int	x;
	int	color;

	x = 0;
	while (x < DEFAULT_S_WIDTH)
	{
		color = calculate_floor_pixel_color(game, floor_ray->floor);
		img_pix_put(&game->img, x, y, color);
		floor_ray->floor.x += floor_ray->floor_step.x;
		floor_ray->floor.y += floor_ray->floor_step.y;
		x++;
	}
}

int	calculate_floor_start(t_game *game)
{
	float	pitch;
	int		pitch_pixel_offset;
	int		horizon;
	int		floor_start;

	pitch = game->player->pitch;
	pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
	horizon = DEFAULT_S_HEIGHT / 2;
	floor_start = horizon - pitch_pixel_offset;
	if (floor_start < 0)
		return (0);
	if (floor_start >= DEFAULT_S_HEIGHT)
		return (DEFAULT_S_HEIGHT - 1);
	return (floor_start);
}

int	validate_game_state(t_game *game)
{
	if (!game || !game->player || !game->map || !game->floor_texture_map)
	{
		printf("Error: Invalid game state in render_floor\n");
		return (0);
	}
	return (1);
}

void	calculate_floor_ray_params(t_game *game, t_floor_ray *floor_ray, int y)
{
	float	pitch;
	int		horizon;
	int		pitch_pixel_offset;
	int		p;
	float	pos_z;

	pitch = game->player->pitch;
	horizon = DEFAULT_S_HEIGHT / 2;
	pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
	p = y - horizon + pitch_pixel_offset;
	pos_z = 0.5f * DEFAULT_S_HEIGHT * (1.0f + game->player->height * 2);
	floor_ray->ray_dir_0.x = game->player->direction.x - game->player->plane.x;
	floor_ray->ray_dir_0.y = game->player->direction.y - game->player->plane.y;
	floor_ray->ray_dir_1.x = game->player->direction.x + game->player->plane.x;
	floor_ray->ray_dir_1.y = game->player->direction.y + game->player->plane.y;
	floor_ray->rowdist = pos_z / p;
	floor_ray->floor_step.x = floor_ray->rowdist * (floor_ray->ray_dir_1.x \
	- floor_ray->ray_dir_0.x) / DEFAULT_S_WIDTH;
	floor_ray->floor_step.y = floor_ray->rowdist * (floor_ray->ray_dir_1.y \
	- floor_ray->ray_dir_0.y) / DEFAULT_S_WIDTH;
	floor_ray->floor.x = game->player->position.x + floor_ray->rowdist \
	* floor_ray->ray_dir_0.x;
	floor_ray->floor.y = game->player->position.y + floor_ray->rowdist \
	* floor_ray->ray_dir_0.y;
}

void	render_floor(t_game *game)
{
	int			floor_start;
	t_floor_ray	floor_ray;
	int			y;

	if (!validate_game_state(game))
		return ;
	floor_start = calculate_floor_start(game);
	y = floor_start;
	while (y < DEFAULT_S_HEIGHT)
	{
		calculate_floor_ray_params(game, &floor_ray, y);
		render_floor_line(game, &floor_ray, y);
		y++;
	}
}
