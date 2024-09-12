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

int bonus_game_loop_0(t_game *game)
{
// run_static_scripts_0
// handle_movement_0
// render_0
	script_skip_enter(game);
	update_scripts(game);
	handle_key_esc(game);
	render_menu(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);
	return (0);
}

int bonus_game_loop_1(t_game *game)
{
	script_skip_enter(game);
	handle_key_esc(game);
	render_opening(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);
	return (0);
}

int bonus_game_loop_2(t_game *game)
{
	script_skip_enter(game);
	handle_key_esc(game);
	render_land(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);
	return (0);
}

// int bonus_game_loop_3(t_game *game)
// {
// 	game->ray_list = calculate_rays(game, game->ray_list);
// 	script_strike_player(game);
// 	script_napalm_enemies(game, 1, 6);
// 	script_napalm_player(game, 1, 6);
// 	player_burning(game);
// 	player_need_stims(game);
// 	script_barrage_enemies(game);
// 	script_barrage_player(game);
// 	script_die(game);
// 	script_found_sth(game);
// 	script_found_supplies(game);
// 	script_take_supplies(game);
// 	script_strike_enemies(game);


// 	script_board(game);
// 	script_takeoff(game);
// 	game->num_enemies = calculate_enemy_count(game);
// 	relocate_enemies(game);
// 	enemies_hit(game);
// 	update_scripts(game);

// 	handle_key_esc(game);
// 	handle_movement_left(game);
// 	handle_movement_right(game);
// 	handle_movement_forward(game);
// 	handle_movement_backward(game);
// 	handle_movement_strafe_left(game);
// 	handle_movement_strafe_right(game);
// 	handle_movement_dash(game);
// 	// pitch
// 	handle_movement_up(game);
// 	handle_movement_down(game);

// 	render_sky(game, "textures/sky06.xpm");
// 	render_floor(game);

// 	render_walls(game);
// 	render_collectibles(game);
// 	render_supplies(game);
// 	render_extract(game);
// 	render_enemies(game);
// 	render_strike(game);
// 	render_napalm(game);
// 	render_barrage(game);

// 	check_enemy_at_center(game);
// 	randomize_dead_enemy_positions(game);
// 	// print_alive_enemies(game);

// 	update_gun_state(game);
// 	render_gun(game);
// 	render_health_bar(game);
// 	render_crosshair(game);
// 	render_hit(game);
// 	render_supply_take(game);
// 	render_respawn(game);
// 	render_pelican_inside(game);
// 	// print_map_section(game, game->player->position.x, game->player->position.y, 5);
// 	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);

// 	clean_rays(game);
// 	return (0);
// }

static void run_dmg_script(t_game *game)
{
    script_strike_player(game);
    script_napalm_enemies(game, 1, 6);
    script_napalm_player(game, 1, 6);
    player_burning(game);
    player_need_stims(game);
    script_barrage_enemies(game);
    script_barrage_player(game);
    script_die(game);
    script_strike_enemies(game);
}

static void run_collectible_script(t_game *game)
{
    script_found_sth(game);
    script_found_supplies(game);
    script_take_supplies(game);
}

static void run_game_end_scripts(t_game *game)
{
    script_board(game);
    script_takeoff(game);
}

static void run_misc_enemies_scripts(t_game *game)
{
    game->num_enemies = calculate_enemy_count(game);
    relocate_enemies(game);
    enemies_hit(game);
    update_scripts(game);
    check_enemy_at_center(game);
    randomize_dead_enemy_positions(game);
    update_gun_state(game);
}

static void run_keystroke_handlers(t_game *game)
{
    handle_key_esc(game);
    handle_movement_left(game);
    handle_movement_right(game);
    handle_movement_forward(game);
    handle_movement_backward(game);
    handle_movement_strafe_left(game);
    handle_movement_strafe_right(game);
    handle_movement_dash(game);
    handle_movement_up(game);
    handle_movement_down(game);
}

static void run_rendering(t_game *game)
{
    render_sky(game, "textures/sky06.xpm");
    render_floor(game);
    render_walls(game);
    render_collectibles(game);
    render_supplies(game);
    render_extract(game);
    render_enemies(game);
    render_strike(game);
    render_napalm(game);
    render_barrage(game);
    render_gun(game);
    render_health_bar(game);
    render_crosshair(game);
    render_hit(game);
    render_supply_take(game);
    render_respawn(game);
    render_pelican_inside(game);
}

int bonus_game_loop_3(t_game *game)
{
    game->ray_list = calculate_rays(game, game->ray_list);

    run_dmg_script(game);
    run_collectible_script(game);
    run_game_end_scripts(game);
    run_misc_enemies_scripts(game);
    run_keystroke_handlers(game);
    run_rendering(game);

    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);

    clean_rays(game);
    return (0);
}

int bonus_game_loop_4(t_game *game)
{
	handle_key_esc(game);
	render_outro(game);
	update_scripts(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);
	return (0);
}



int bonus_game_loop(t_game *game)
{
	if (game->game_sequence == 0)
		bonus_game_loop_0(game);
	else if (game->game_sequence == 1)
		bonus_game_loop_1(game);
	else if (game->game_sequence == 2)
		bonus_game_loop_2(game);
	else if (game->game_sequence == 3)
		bonus_game_loop_3(game);
	else if (game->game_sequence == 4)
		bonus_game_loop_4(game);
	else
		printf("game_sequence error %d\n", game->game_sequence);
	return (0);
}

// void    render_core_game_loop()
// {

// }

int core_game_loop(t_game *game)
{
	game->game_sequence = 3;
	game->ray_list = calculate_rays(game, game->ray_list);
	handle_key_esc(game);
	handle_movement_left(game);
	handle_movement_right(game);
	handle_movement_forward(game);
	handle_movement_backward(game);
	handle_movement_strafe_left(game);
	handle_movement_strafe_right(game);
	render_floor_rgb(&game->img, game->floor_rgb[0].hex_color);
	render_sky_rgb(game, game->sky_rgb[0].hex_color);
	render_walls(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0, 0);
	clean_rays(game);
	return (0);
}

int render(t_game *game)
{
	if (game->win_ptr == NULL)
		return (1);
	if (game->bonus == 0)
	{
		core_game_loop(game);
	}
	else
		bonus_game_loop(game);
	return (0);
}

void	setup_bonus_assets(t_game *game)
{
	initialize_game_seed(game);
	initialize_floor_texture_weights(game);
	initialize_floor_texture_map(game);
	initialize_audio(game);
}

void	setup_bonus_scripts(t_game *game)
{
	play_audio_file(game, "audio/menu.mp3", 2);
	add_script(game, menu_background, 5);
	add_script(game, menu_background_voice, 10);
}
void	setup_bonus_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 6, 1L << 6, handle_mouse_move, game);
	mlx_mouse_hook(game->win_ptr, handle_mouse_click, game);
	mlx_hook(game->win_ptr, 5, 1L << 3, handle_mouse_release, game);
}

// void	setup_core_assets(game)
// {

// }

// int setup_game_mlx(t_game *game)
// {

// 	if (game == NULL)
// 		return (0);

// 	game->mlx_ptr = mlx_init();
// 	if (game->mlx_ptr == NULL)
// 		return (0);
// 	load_textures(game);
// 	game->win_ptr = mlx_new_window(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "Helldivers 3D");
// 	if (game->win_ptr == NULL)
// 	{
// 		free(game->win_ptr);
// 		return (0);
// 	}
// 	game->img.mlx_img = mlx_new_image(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT);
// 	game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp, &game->img.line_len, &game->img.endian);
// 	mlx_hook(game->win_ptr, 2, 1L << 0, ft_key_press, game);
// 	mlx_loop_hook(game->mlx_ptr, &render, game);
// 	mlx_hook(game->win_ptr, 3, 1L << 1, ft_key_release, game);
// 	mlx_hook(game->win_ptr, 17, 0, close_hook, game);
// 	if (game->bonus)
// 	{
// 		setup_bonus_assets(game);
// 		setup_bonus_scripts(game);
// 		setup_bonus_hooks(game);
// 	}
// 	mlx_loop(game->mlx_ptr);
// 	return (0);
// }


int initialize_mlx(t_game *game)
{
    game->mlx_ptr = mlx_init();
    return (game->mlx_ptr != NULL);
}

int create_game_window(t_game *game)
{
    game->win_ptr = mlx_new_window(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "Helldivers 3D");
    if (game->win_ptr == NULL)
    {
        free(game->win_ptr);
        return (0);
    }
    return (1);
}

void create_game_image(t_game *game)
{
    game->img.mlx_img = mlx_new_image(game->mlx_ptr, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.mlx_img, &game->img.bpp, &game->img.line_len, &game->img.endian);
}

void setup_game_hooks(t_game *game)
{
    mlx_hook(game->win_ptr, 2, 1L << 0, ft_key_press, game);
    mlx_loop_hook(game->mlx_ptr, &render, game);
    mlx_hook(game->win_ptr, 3, 1L << 1, ft_key_release, game);
    mlx_hook(game->win_ptr, 17, 0, close_hook, game);
}

void setup_bonus_features(t_game *game)
{
    if (game->bonus)
    {
        setup_bonus_assets(game);
        setup_bonus_scripts(game);
        setup_bonus_hooks(game);
    }
}

int setup_game_mlx(t_game *game)
{
    if (game == NULL)
        return (0);

    if (!initialize_mlx(game))
        return (0);

    load_textures(game);

    if (!create_game_window(game))
        return (0);

    create_game_image(game);
    setup_game_hooks(game);
    setup_bonus_features(game);

    mlx_loop(game->mlx_ptr);
    return (0);
}
