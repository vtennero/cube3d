/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:20:12 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/17 12:17:51 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void print_ray(const t_ray *ray)
{
	printf("print_ray\n");
    printf("x: %d\n", ray->x);
    printf("cameraX: %.2f\n", ray->cameraX);
    printf("rayDirX: %.2f\n", ray->rayDirX);
    printf("rayDirY: %.2f\n", ray->rayDirY);
    printf("mapX: %d\n", ray->mapX);
    printf("mapY: %d\n", ray->mapY);
    printf("sideDistX: %.2f\n", ray->sideDistX);
    printf("sideDistY: %.2f\n", ray->sideDistY);
    printf("deltaDistX: %.2f\n", ray->deltaDistX);
    printf("deltaDistY: %.2f\n", ray->deltaDistY);
    printf("perpWallDist: %.2f\n", ray->perpWallDist);
    printf("stepX: %d\n", ray->stepX);
    printf("stepY: %d\n", ray->stepY);
    printf("hit: %d\n", ray->hit);
    printf("side: %d\n", ray->side);
    printf("lineHeight: %d\n", ray->lineHeight);
    printf("draw_start: %d\n", ray->draw_start);
    printf("draw_end: %d\n", ray->draw_end);
    printf("color: %d\n", ray->color);
    printf("wall_face: %d\n", ray->wall_face);
	printf("******************************\n");
}

void calc_camera_x(t_game *game, t_ray_node *ray)
{
	ray->ray.cameraX = 2 * ray->ray.x / (double)(game->screen_width) - 1;
}

void calc_ray_dir_x(t_game *game, t_ray_node *ray)
{
	ray->ray.rayDirX = game->player->direction.x + game->player->plane.x * ray->ray.cameraX;
}

void calc_ray_dir_y(t_game *game, t_ray_node *ray)
{
	ray->ray.rayDirY = game->player->direction.y + game->player->plane.y * ray->ray.cameraX;
}

void calc_map_x(t_game *game, t_ray_node *ray)
{
	ray->ray.mapX = game->player->position.x;
}

void calc_map_y(t_game *game, t_ray_node *ray)
{
	ray->ray.mapY = game->player->position.y;
}

void calc_side_dist(t_game *game, t_ray_node *ray)
{
	if (ray->ray.rayDirX  < 0)
	{
		ray->ray.stepX = -1;
		ray->ray.sideDistX = (game->player->position.x - ray->ray.mapX) * ray->ray.deltaDistX;
	}
	else
	{
		ray->ray.stepX = 1;
		ray->ray.sideDistX = (ray->ray.mapX + 1.0 - game->player->position.x) * ray->ray.deltaDistX;
	}
	if (ray->ray.rayDirY < 0)
	{
		ray->ray.stepY = -1;
		ray->ray.sideDistY = (game->player->position.y - ray->ray.mapY) * ray->ray.deltaDistY;
	}
	else
	{
		ray->ray.stepY = 1;
		ray->ray.sideDistY = (ray->ray.mapY + 1.0 - game->player->position.y) * ray->ray.deltaDistY;
	}
}



void calc_delta_dist(t_game *game, t_ray_node *ray)
{
	(void)game;
	if (ray->ray.rayDirX == 0)
		ray->ray.deltaDistX = 1e30;
	else
		ray->ray.deltaDistX = fabs(1 / ray->ray.rayDirX);
	if (ray->ray.rayDirY == 0)
		ray->ray.deltaDistY = 1e30;
	else
		ray->ray.deltaDistY = fabs(1 / ray->ray.rayDirY);
}

void	perform_dda(t_game *game, t_ray_node *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (ray->ray.sideDistX < ray->ray.sideDistY)
		{
			ray->ray.sideDistX += ray->ray.deltaDistX;
			ray->ray.mapX += ray->ray.stepX;
			ray->ray.side = 0;
		}
		else
		{
			ray->ray.sideDistY += ray->ray.deltaDistY;
			ray->ray.mapY += ray->ray.stepY;
			ray->ray.side = 1;
		}
		//Check if ray has hit a wall
		if (game->map->data[ray->ray.mapX][ray->ray.mapY] > 0)
		{
			hit = 1;
			if (ray->ray.side == 0) // EW wall
                ray->ray.wall_face = (ray->ray.stepX > 0) ? EAST : WEST;
            else // NS wall
                ray->ray.wall_face = (ray->ray.stepY > 0) ? SOUTH : NORTH;
		}

	}
}


void calc_perp_wall_dist(t_game *game, t_ray_node *ray)
{
	(void)game;
	if(ray->ray.side == 0)
		ray->ray.perpWallDist = (ray->ray.sideDistX - ray->ray.deltaDistX);
	else
		ray->ray.perpWallDist = (ray->ray.sideDistY - ray->ray.deltaDistY);
}


void calc_line_height(t_game *game, t_ray_node *ray)
{
	ray->ray.lineHeight = (int)(game->screen_height / ray->ray.perpWallDist);
}

void calc_draw_parameters(t_game *game, t_ray_node *ray)
{
	//calculate lowest and highest pixel to fill in current stripe
	ray->ray.draw_start = -ray->ray.lineHeight / 2 + game->screen_height / 2;
	if (ray->ray.draw_start < 0)
		ray->ray.draw_start = 0;
	ray->ray.draw_end = ray->ray.lineHeight / 2 + game->screen_height / 2;
	if(ray->ray.draw_end >= game->screen_height)
		ray->ray.draw_end = game->screen_height - 1;
}

void calc_texture_x(t_game *game, t_ray_node *ray)
{
    int textureWidth = game->walltextures[ray->ray.wall_face].width;  // Dynamically get the width based on wall_face
    ray->ray.texX = (int)(ray->ray.wallX * (double)textureWidth);
    if (ray->ray.side == 0 && ray->ray.rayDirX > 0)
        ray->ray.texX = textureWidth - ray->ray.texX - 1;
    if (ray->ray.side == 1 && ray->ray.rayDirY < 0)
        ray->ray.texX = textureWidth - ray->ray.texX - 1;
}


void calc_wall_hit(t_game *game, t_ray_node *ray) {
    double wallImpact;  // point of impact along the wall, normalized to [0, 1]
    // Assuming a perpendicular hit, calculate where along the wall the ray hits
    if (ray->ray.side == 0) {  // Horizontal hit
        wallImpact = game->player->position.y + ray->ray.perpWallDist * ray->ray.rayDirY;
    } else {  // Vertical hit
        wallImpact = game->player->position.x + ray->ray.perpWallDist * ray->ray.rayDirX;
    }

    wallImpact -= floor(wallImpact); // Normalize the impact point
    ray->ray.wallX = wallImpact;
}

