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


// debug

void print_map_section(t_game *game, int center_x, int center_y, int radius)
{
       printf("Map section around player:\n");
       for (int y = center_y - radius; y <= center_y + radius; y++) {
           for (int x = center_x - radius; x <= center_x + radius; x++) {
               if (x >= 0 && x < game->map->width && y >= 0 && y < game->map->height) {
                   printf("%d ", game->map->data[x][y]);
               } else {
                   printf("# ");
               }
           }
           printf("\n");
       }
   }

int render(t_game *game)
{
    // printf("RENDER game sequence: %d\n", game->game_sequence);
    if (game->win_ptr == NULL)
        return (1);
    if (game->game_sequence == 0)
    {
        // handle_key_enter(game);
        update_scripts(game);
        handle_key_esc(game);
        render_menu(game);
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);
    }
    else if (game->game_sequence == 1)
    {
        // handle_key_enter(game);
        handle_key_esc(game);
        render_opening(game);
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);
    }
    else if (game->game_sequence == 2)
    {
        // handle_key_enter(game);
        handle_key_esc(game);
        render_land(game);
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);
    }
    else if (game->game_sequence == 3)
    {
    
    script_found_sth(game);
    script_found_supplies(game);
    script_take_supplies(game);
    script_strike_enemies(game);
    script_board(game);
    // trigger_gunshots(game);
    update_scripts(game);
    game->num_enemies = calculate_enemy_count(game);
    relocate_enemies(game);
    enemies_hit(game);

    handle_key_esc(game);
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
    // handle_space_shoot(game);

    // rendering
	if (game->bonus==1)
    {
		render_sky(game, "textures/sky06.xpm");
		render_floor(game);
	}
	else
	{
		render_floor_rgb(&game->img, game->floor_rgb[0].hex_color);
		render_sky_rgb(game, game->sky_rgb[0].hex_color);
	}
	


    // c_render_ray_list(game);
    render_ray_list(game);
    render_collectibles(game);
    render_supplies(game);
    render_extract(game);
    render_enemies(game);
    render_strike(game);

    check_enemy_at_center(game);
    randomize_dead_enemy_positions(game);
    // print_alive_enemies(game);

    update_gun_state(game);
    render_gun(game);
    render_hit(game);
    render_supply_take(game);

    // print_map_section(game, game->player->position.x, game->player->position.y, 5);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);

    clean_rays(game);
    }
    else if (game->game_sequence == 4)
    {
        render_outro(game);
        update_scripts(game);
        mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);
    }
    else
    {
        printf("game_sequence error %d\n", game->game_sequence);
    }
    return (0);
}

int setup_game_mlx(t_game *game)
{

    if (game == NULL)
        return (0);

    game->mlx_ptr = mlx_init();
    if (game->mlx_ptr == NULL)
        return (0);
    game->win_ptr = mlx_new_window(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "Helldivers 3D");
    if (game->win_ptr == NULL)
    {
        free(game->win_ptr);
        return (0);
    }

    // comment this (for testing purposes)
    game->game_sequence = 3;
    // preload_textures(game);
	preload_textures_non_bonus(game);
    initialize_game_seed(game);
    initialize_floor_texture_weights(game);
    initialize_floor_texture_map(game);

    initializeAudio();
    playAudioFileWithDelay("audio/menu.mp3", 2);
    add_script(game, menu_background, 5);
    add_script(game, menu_background_voice, 10);


    game->img.mlx_img = mlx_new_image(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp,
                                       &game->img.line_len, &game->img.endian);

    mlx_hook(game->win_ptr, 2, 1L << 0, ft_key_press, game);
    mlx_loop_hook(game->mlx_ptr, &render, game);
    mlx_hook(game->win_ptr, 3, 1L << 1, ft_key_release, game);

    // Add this line to handle mouse movement
    mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse_move, game);
    mlx_mouse_hook(game->win_ptr, handle_mouse_click, game);
    mlx_hook(game->win_ptr, 5, 1L << 3, handle_mouse_release, game);


    // mlx_hook(game->win_ptr, 17, 0, handle_cross_key, game);

    mlx_loop(game->mlx_ptr);



    return (0);
}
