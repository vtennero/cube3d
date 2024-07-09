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

void printRayList(t_ray_node *head)
{
    t_ray_node *current = head;
    while (current != NULL)
    {
        printf("Ray at x=%d, draw_start=%d, draw_end=%d, color=%d\n",
               current->ray.x,
               current->ray.draw_start,
               current->ray.draw_end,
               current->ray.color);
        current = current->next;
    }
}

t_ray_node *calculate_rays(t_game *game, t_ray_node *list)
{
    int x;
    t_ray_node *current;

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
            // calc_tile_color(game, current);
        }
        x++;
    }
    return (list);
}
