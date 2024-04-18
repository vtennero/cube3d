/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_v1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:51:57 by toto              #+#    #+#             */
/*   Updated: 2024/04/18 10:53:03 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// Initialize MiniLibX, window, and image buffer
// void setup_mlx(t_game* game);

// // Main rendering loop
// void render_loop(t_game* game);

// // Draw a single frame
// void render_frame(t_game* game);

// // Cleanup resources
// void cleanup(t_game* game);

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

// discontinued
int render_game2(t_game *game)
{
    t_ray_node* list = NULL;
    t_ray_node* current;
    int x;

    game->mlx_ptr = mlx_init();
    game->win_ptr = mlx_new_window(game->mlx_ptr, game->screen_width, game->screen_height, "MLX Window");
    set_up_hooks(game);
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
            calc_line_height(game, current);
            calc_draw_parameters(game, current);
            print_ray(&current->ray);
        }
        x++;
    }

    render_ray_list(list, game->mlx_ptr, game->win_ptr);
    mlx_loop(game->mlx_ptr);
    return 0;
}