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

// void addRay(t_ray_node** head, int x, int draw_start, int draw_end, int color)
// {
//     t_ray_node* newNode = malloc(sizeof(t_ray_node));
//     if (newNode == NULL) {
//         fprintf(stderr, "Error allocating memory for new node.\n");
//         return;
//     }

//     newNode->ray.x = x;
//     newNode->ray.draw_start = draw_start;
//     newNode->ray.draw_end = draw_end;
//     newNode->ray.color = color;

//     if (*head == NULL) { // List does not exist, create the first node
//         newNode->next = NULL;
//         *head = newNode;
//     } else { // List exists, add the new node to the front
//         newNode->next = *head;
//         *head = newNode;
//     }
// }

t_ray_node* addRay(t_ray_node** head) {
    t_ray_node* newNode = malloc(sizeof(t_ray_node));
    if (newNode == NULL) {
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

    if (*head == NULL) {
        newNode->next = NULL;
        *head = newNode;
    } else {
        newNode->next = *head;
        *head = newNode;
    }

    return newNode;
}

void printRayList(t_ray_node* head)
{
    t_ray_node* current = head;
    while (current != NULL) {
        printf("Ray at x=%d, draw_start=%d, draw_end=%d, color=%d\n",
               current->ray.x,
               current->ray.draw_start,
               current->ray.draw_end,
               current->ray.color);
        current = current->next;
    }
}

void printRayList_color_v1(t_ray_node* head)
{
    t_ray_node* current = head;
    while (current != NULL) {
        printf("Ray at x=%d, draw_start=%d, draw_end=%d, color=%d\n",
               current->ray.x,
               current->ray.draw_start,
               current->ray.draw_end,
               current->ray.color);
        current = current->next;
    }
}

void render_ray_list(t_ray_node* head, void *mlx_ptr, void *win_ptr)
{
    t_ray_node *current = head;

    while (current != NULL) {
        for (int y = current->ray.draw_start; y < current->ray.draw_end; y++) {
            mlx_pixel_put(mlx_ptr, win_ptr, current->ray.x, y, current->ray.color);
        }
        current = current->next;
    }
}

void render_ray_list_color_v1(t_ray_node* head, void *mlx_ptr, void *win_ptr)
{
    t_ray_node *current = head;

    while (current != NULL) {
        for (int y = current->ray.draw_start; y < current->ray.draw_end; y++) {
            mlx_pixel_put(mlx_ptr, win_ptr, current->ray.x, y, current->ray.color);
        }
        current = current->next;
    }
}