/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:49:22 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/17 12:27:19 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_ray_node *addRay(t_ray_node **head)
{
    t_ray_node *newNode = malloc(sizeof(t_ray_node));
    if (newNode == NULL)
    {
        fprintf(stderr, "Error allocating memory for new node.\n");
        return NULL;
    }

    // Initialize parameters as before
    newNode->ray.cameraX = 0.0;
    newNode->ray.rayDirX = 0.0;
    newNode->ray.rayDirY = 0.0;
    newNode->ray.mapX = 0;
    newNode->ray.mapY = 0;
    newNode->ray.sideDistX = 0.0;
    newNode->ray.sideDistY = 0.0;
    newNode->ray.deltaDistX = 0.0;
    newNode->ray.deltaDistY = 0.0;
    newNode->ray.perpWallDist = 0.0;
    newNode->ray.stepX = 0;
    newNode->ray.stepY = 0;
    newNode->ray.hit = 0;
    newNode->ray.side = 0;
    newNode->ray.lineHeight = 0;
    newNode->ray.draw_start = 0;
    newNode->ray.draw_end = 0;
    newNode->ray.color = 0;
    newNode->ray.wall_face = 0;
    newNode->ray.wallX = 0;

    if (*head == NULL)
    {
        newNode->next = NULL;
        *head = newNode;
    }
    else
    {
        newNode->next = *head;
        *head = newNode;
    }

    return newNode;
}

// t_ray_node *calculate_rays(t_game *game, t_ray_node *list)
// {
//     int x;
//     t_ray_node *current;

//     current = list;
//     x = 0;
//     while (x < game->screen_width)
//     {
//         current = addRay(&list);
//         if (current != NULL)
//         {
//             current->ray.x = x;
//             calc_camera_x(game, current);
//             calc_ray_dir_x(game, current);
//             calc_ray_dir_y(game, current);
//             calc_map_x(game, current);
//             calc_map_y(game, current);
//             calc_side_dist(game, current);
//             calc_delta_dist(game, current);
//             perform_dda(game, current);
//             calc_perp_wall_dist(game, current);
//             calc_wall_hit(game, current);
//             calc_texture_x(game, current);
//             calc_line_height(game, current);
//             calc_draw_parameters(game, current);
//             // calc_tile_color(game, current);
//         }
//         x++;
//     }
//     // printRayList(list);
//     return (list);
// }
t_vector2d calculate_floor_coordinates(t_game *game, t_ray_node *center_ray)
{
    t_vector2d floor_coords;
    float distance;

    // Use the center ray's direction
    float ray_dir_x = center_ray->ray.rayDirX;
    float ray_dir_y = center_ray->ray.rayDirY;

    // Check if we hit a wall
    if (center_ray->ray.hit)
    {
        // If we hit a wall, use the wall hit point
        distance = center_ray->ray.perpWallDist;
    }
    else
    {
        // If no wall, use the map's diagonal as the maximum distance
        distance = sqrt(game->map->width * game->map->width + game->map->height * game->map->height);
    }

    // Apply pitch
    float pitch_offset = game->player->pitch * distance;
    
    // Calculate the floor coordinates
    floor_coords.x = game->player->position.x + ray_dir_x * distance;
    floor_coords.y = game->player->position.y + ray_dir_y * distance;

    // Adjust for pitch (positive pitch looks down, negative looks up)
    if (pitch_offset > 0)
    {
        // Looking down, move the point closer
        floor_coords.x = game->player->position.x + ray_dir_x * (distance - pitch_offset);
        floor_coords.y = game->player->position.y + ray_dir_y * (distance - pitch_offset);
    }
    // When looking up (negative pitch), we keep the farthest point

    // Ensure coordinates are within map bounds
    floor_coords.x = fmax(0, fmin(floor_coords.x, game->map->width - 1));
    floor_coords.y = fmax(0, fmin(floor_coords.y, game->map->height - 1));

    return floor_coords;
}
void calculate_and_print_center_ray(t_game *game, t_ray_node *center_ray)
{
    t_vector2d floor_coords = calculate_floor_coordinates(game, center_ray);
    game->center_floor_coords = floor_coords;

    // Calculate tile coordinates
    t_vector2d tile_coords;
    tile_coords.x = floor(floor_coords.x);
    tile_coords.y = floor(floor_coords.y);

    // Print tile coordinates
    printf("Center ray aimed at tile: (%.0f, %.0f)\n", tile_coords.x, tile_coords.y);
    
    // Print more information
    printf("Exact floor coordinates: (%.2f, %.2f)\n", floor_coords.x, floor_coords.y);
    printf("Player position: (%.2f, %.2f)\n", game->player->position.x, game->player->position.y);
    // printf("Ray direction: (%.2f, %.2f)\n", center_ray->ray.rayDirX, center_ray->ray.rayDirY);
    // printf("Hit wall: %s\n", center_ray->ray.hit ? "Yes" : "No");
    if (center_ray->ray.hit)
    {
        printf("Wall distance: %.2f\n", center_ray->ray.perpWallDist);
    }
    // printf("Pitch: %.2f\n", game->player->pitch);
    // printf("Map size: %d x %d\n", game->map->width, game->map->height);
}
t_vector2d get_center_tile_coords(t_game *game)
{
    t_vector2d tile_coords;
    tile_coords.x = floor(game->center_floor_coords.x);
    tile_coords.y = floor(game->center_floor_coords.y);
    return tile_coords;
}

t_ray_node *calculate_rays(t_game *game, t_ray_node *list)
{
    int x;
    t_ray_node *current;
    t_ray_node *center_ray = NULL;

    current = list;
    x = 0;
    while (x < game->screen_width)
    {
        current = addRay(&list);
        if (current != NULL)
        {
            current->ray.x = x;
            calc_camera_x(game, current);
            calc_ray_dir_x(game, current);
            calc_ray_dir_y(game, current);
            calc_map_x(game, current);
            calc_map_y(game, current);
            calc_side_dist(game, current);
            calc_delta_dist(game, current);
            perform_dda(game, current);
            calc_perp_wall_dist(game, current);
            calc_wall_hit(game, current);
            calc_texture_x(game, current);
            calc_line_height(game, current);
            calc_draw_parameters(game, current);

            // Store the center ray
            if (x == game->screen_width / 2)
            {
                center_ray = current;
            }
        }
        x++;
    }

    // Calculate and print center ray information
    if (center_ray != NULL)
    {
        calculate_and_print_center_ray(game, center_ray);
    }

    return (list);
}