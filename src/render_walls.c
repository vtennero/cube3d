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

// #include <stdint.h>

// // Define a static array of 4 solid colors (ARGB format)
// static const uint32_t wall_colors[4] = {
//     0xFFFF0000,  // Red for North
//     0xFF00FF00,  // Green for South
//     0xFF0000FF,  // Blue for East
//     0xFFFFFF00   // Yellow for West
// };

// // Simplified function to get color (no longer needs texture coordinates)
// uint32_t get_wall_color(int wall_face)
// {
//     return wall_colors[wall_face];
// }

// void c_render_ray(t_img *img, t_ray ray, int wall_face, t_game *game)
// {
//     // int pitch_offset;
//     uint32_t color;

//     // pitch_offset = (int)(game->player->pitch * game->screen_height);
// 	(void)game;
//     color = get_wall_color(wall_face);

//     for (int y = ray.draw_start; y < ray.draw_end; y++)
//     {
//         img_pix_put(img, ray.x, y, color);
//     }
// }

// // void c_render_ray(t_img *img, t_ray ray, int wall_face, t_game *game)
// // {
// //     (void)game;
// //     uint32_t color = get_wall_color(wall_face);

// //     // Draw a single pixel at the middle of where the wall would be
// //     int mid_y = (ray.draw_start + ray.draw_end) / 2;
// //     img_pix_put(img, ray.x, mid_y, color);

// //     // Optionally, draw a few pixels to make it more visible
// //     if (mid_y > 0) img_pix_put(img, ray.x, mid_y - 1, color);
// //     if (mid_y < DEFAULT_S_HEIGHT - 1) img_pix_put(img, ray.x, mid_y + 1, color);
// // }

// void c_render_ray_list(t_game *game)
// {
//     int i = 0;
//     game->ray_list = calculate_rays(game, game->ray_list);
//     t_ray_node *current = game->ray_list;

//     while (current != NULL)
//     {
//         c_render_ray(&game->img, current->ray, current->ray.wall_face, game);
//         current = current->next;
//         i++;
//     }
// }
