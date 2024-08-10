/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:19:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/13 16:47:25 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void img_pix_put(t_img *img, int x, int y, int color)
{
    char *pixel;
    int i;

    if (x < 0 || x >= DEFAULT_S_WIDTH || y < 0 || y >= DEFAULT_S_HEIGHT)
    {
        fprintf(stderr, "Attempted to write pixel out of bounds: x=%d, y=%d\n", x, y);
        return; // Skip drawing for invalid coordinates
    }

    i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
    while (i >= 0)
    {
        /* big endian, MSB is the leftmost bit */
        if (img->endian != 0)
            *pixel++ = (color >> i) & 0xFF;
        /* little endian, LSB is the leftmost bit */
        else
            *pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
        i -= 8;
    }
}

int render(t_game *game)
{
    if (game->win_ptr == NULL)
        return (1);

    handle_movement_left(game);
    handle_movement_right(game);
    handle_movement_forward(game);
    handle_movement_backward(game);
    handle_movement_strafe_left(game);
    handle_movement_strafe_right(game);
    handle_movement_dash(game);
    // pitch
    handle_movement_up(game);
    handle_movement_down(game);

    // interactions
    handle_key_e(game);

    // rendering
    render_sky(game, "textures/sky06.xpm");
    render_floor(game);
    render_ray_list(game);
    render_collectibles(game);
    render_enemies(game);
    render_gun(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);

// we should free here
	game->ray_list = NULL;

    return (0);
}

int setup_game_mlx(t_game *game)
{

    if (game == NULL)
        return (0);

    game->mlx_ptr = mlx_init();
    if (game->mlx_ptr == NULL)
        return (0);
    game->win_ptr = mlx_new_window(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "my window");
    if (game->win_ptr == NULL)
    {
        free(game->win_ptr);
        return (0);
    }
    preload_textures(game);
    initialize_game_seed(game);
    initialize_floor_texture_weights(game);
    initialize_floor_texture_map(game);

    game->img.mlx_img = mlx_new_image(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp,
                                       &game->img.line_len, &game->img.endian);

    mlx_hook(game->win_ptr, 2, 1L << 0, ft_key_press, game);
    mlx_loop_hook(game->mlx_ptr, &render, game);
    mlx_hook(game->win_ptr, 3, 1L << 1, ft_key_release, game);

    // Add this line to handle mouse movement
    mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse_move, game);
    mlx_loop(game->mlx_ptr);

    /* we will exit the loop if there's no window left, and execute this code */
    // mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
    // mlx_destroy_display(game->mlx_ptr);
    // free(game->mlx_ptr);

    return (0);
}
