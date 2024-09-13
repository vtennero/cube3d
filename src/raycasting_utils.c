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
	ray->ray.mapX = (int)game->player->position.x;
}

void calc_map_y(t_game *game, t_ray_node *ray)
{
	ray->ray.mapY = (int)game->player->position.y;
}

void calc_side_dist(t_game *game, t_ray_node *ray)
{
	// Calculate delta distances
	ray->ray.deltaDistX = (ray->ray.rayDirX == 0) ? 1e30 : fabs(1 / ray->ray.rayDirX);
	ray->ray.deltaDistY = (ray->ray.rayDirY == 0) ? 1e30 : fabs(1 / ray->ray.rayDirY);

       if (ray->ray.rayDirX < 0)
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
       ray->ray.deltaDistX = (ray->ray.rayDirX == 0) ? 1e30 : fabs(1 / ray->ray.rayDirX);
       ray->ray.deltaDistY = (ray->ray.rayDirY == 0) ? 1e30 : fabs(1 / ray->ray.rayDirY);

    //    printf("Ray %d: deltaDistX=%.4f, deltaDistY=%.4f\n",               ray->ray.x, ray->ray.deltaDistX, ray->ray.deltaDistY);
   }

#define EPSILON 1e-6
#define MAX_STEPS 100000


// Helper function to check if the ray is out of bounds
static int is_out_of_bounds(t_game *game, t_ray *ray)
{
    return (ray->mapX < 0 || ray->mapX >= game->map->width ||
            ray->mapY < 0 || ray->mapY >= game->map->height);
}

static int	is_within_map_bounds(t_game *game, int x, int y)
{
	return (x >= 0 && x < game->map->width
		&& y >= 0 && y < game->map->height);
}

static void	update_ray_x(t_ray *ray)
{
	ray->sideDistX += ray->deltaDistX;
	ray->mapX += ray->stepX;
	ray->side = 0;
}

static void	update_ray_y(t_ray *ray)
{
	ray->sideDistY += ray->deltaDistY;
	ray->mapY += ray->stepY;
	ray->side = 1;
}

static void	handle_corner_case(t_game *game, t_ray *ray, int next_x, int next_y)
{
	if (game->map->data[next_x][ray->mapY] == 1
		&& game->map->data[ray->mapX][next_y] == 1)
		update_ray_x(ray);
	else if (game->map->data[next_x][ray->mapY] == 1)
		update_ray_y(ray);
	else
		update_ray_x(ray);
}

static void	handle_epsilon_case(t_game *game, t_ray *ray)
{
	int	next_x;
	int	next_y;

	next_x = ray->mapX + ray->stepX;
	next_y = ray->mapY + ray->stepY;
	if (is_within_map_bounds(game, next_x, next_y))
		handle_corner_case(game, ray, next_x, next_y);
}

// Helper function to move the ray
static void move_ray(t_ray *ray)
{
    if (ray->sideDistX < ray->sideDistY)
    {
        ray->sideDistX += ray->deltaDistX;
        ray->mapX += ray->stepX;
        ray->side = 0;
    }
    else
    {
        ray->sideDistY += ray->deltaDistY;
        ray->mapY += ray->stepY;
        ray->side = 1;
    }
}


static void	set_wall_face(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_face = (ray->stepX > 0) ? EAST : WEST;
	else
		ray->wall_face = (ray->stepY > 0) ? SOUTH : NORTH;
}

static int	is_wall(t_game *game, int mapY, int mapX)
{
	return (game->map->data[mapY][mapX] == 1);
}


static int	is_space_to_wall_transition(t_game *game, t_ray *ray,
		int prev_mapX, int prev_mapY)
{
	return ((prev_mapX != ray->mapX || prev_mapY != ray->mapY)
		&& !is_wall(game, prev_mapY, prev_mapX)
		&& is_wall(game, ray->mapY, ray->mapX));
}

static void	adjust_ray_position(t_ray *ray, int *prev_mapX, int *prev_mapY)
{
	if (ray->side == 0)
	{
		ray->sideDistX -= ray->deltaDistX;
		ray->mapX = *prev_mapX;
	}
	else
	{
		ray->sideDistY -= ray->deltaDistY;
		ray->mapY = *prev_mapY;
	}
}

static int	check_wall_hit(t_game *game, t_ray *ray,
		int *prev_mapX, int *prev_mapY)
{
	if (is_wall(game, ray->mapY, ray->mapX))
	{
		set_wall_face(ray);
		return (1);
	}
	else if (is_space_to_wall_transition(game, ray, *prev_mapX, *prev_mapY))
	{
		adjust_ray_position(ray, prev_mapX, prev_mapY);
		return (1);
	}
	*prev_mapX = ray->mapX;
	*prev_mapY = ray->mapY;
	return (0);
}

void perform_dda(t_game *game, t_ray_node *ray)
{
    int hit = 0;
    int step_count = 0;
    int prev_mapX = ray->ray.mapX;
    int prev_mapY = ray->ray.mapY;

    while (hit == 0 && step_count < 100)
    {
        if (is_out_of_bounds(game, &ray->ray))
        {
            hit = 1;
            break;
        }

        if (fabs(ray->ray.sideDistX - ray->ray.sideDistY) < EPSILON)
        {
            handle_epsilon_case(game, &ray->ray);
        }
        else
        {
            move_ray(&ray->ray);
        }

        hit = check_wall_hit(game, &ray->ray, &prev_mapX, &prev_mapY);
        step_count++;
    }
}

void calc_perp_wall_dist(t_game *game, t_ray_node *ray)
{
	(void)game;
	if (ray->ray.side == 0)
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
    int pitch_offset = (int)(game->player->pitch * game->screen_height);
    // int pitch_offset = -(int)(game->player->pitch * game->screen_height);

    ray->ray.lineHeight = (int)(game->screen_height / ray->ray.perpWallDist);

    // Adjust for player height
    int height_offset = (int)(game->player->height * game->screen_height / ray->ray.perpWallDist);

    // Adjust drawStart and drawEnd based on pitch and height
    ray->ray.draw_start = -ray->ray.lineHeight / 2 + game->screen_height / 2 + pitch_offset + height_offset;
    if (ray->ray.draw_start < 0)
        ray->ray.draw_start = 0;

    ray->ray.draw_end = ray->ray.lineHeight / 2 + game->screen_height / 2 + pitch_offset + height_offset;
    if (ray->ray.draw_end >= game->screen_height)
        ray->ray.draw_end = game->screen_height - 1;
}

void calc_texture_x(t_game *game, t_ray_node *ray)
{
	int textureWidth = game->walltextures[ray->ray.wall_face].width; // Dynamically get the width based on wall_face
	ray->ray.texX = (int)(ray->ray.wallX * (double)textureWidth);
	if (ray->ray.side == 0 && ray->ray.rayDirX > 0)
		ray->ray.texX = textureWidth - ray->ray.texX - 1;
	if (ray->ray.side == 1 && ray->ray.rayDirY < 0)
		ray->ray.texX = textureWidth - ray->ray.texX - 1;
}

void calc_wall_hit(t_game *game, t_ray_node *ray)
{
	double wallImpact; // point of impact along the wall, normalized to [0, 1]
	// Assuming a perpendicular hit, calculate where along the wall the ray hits
	if (ray->ray.side == 0)
	{ // Horizontal hit
		wallImpact = game->player->position.y + ray->ray.perpWallDist * ray->ray.rayDirY;
	}
	else
	{ // Vertical hit
		wallImpact = game->player->position.x + ray->ray.perpWallDist * ray->ray.rayDirX;
            // wallImpact = game->player->position.y + ray->ray.perpWallDist * ray->ray.rayDirY;

	}

	wallImpact -= floor(wallImpact); // Normalize the impact point
	ray->ray.wallX = wallImpact;
}


