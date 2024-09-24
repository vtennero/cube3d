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

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	if (x < 0 || x >= DEFAULT_S_WIDTH || y < 0 || y >= DEFAULT_S_HEIGHT)
	{
		printf("Attempted to write pixel out of bounds: x=%d, y=%d\n", x, y);
		return ;
	}
	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	run_keystroke_handlers(t_game *game)
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

int	core_game_loop(t_game *game)
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
	render_floor_rgb(&game->img, \
	game->floor_rgb[0].hex_color);
	render_sky_rgb(game, game->sky_rgb[0].hex_color);
	render_walls(game);
	mlx_put_image_to_window(game->mlx_ptr, \
	game->win_ptr, game->img.mlx_img, 0, 0);
	clean_rays(game);
	return (0);
}

int	render(t_game *game)
{
	if (game->win_ptr == NULL)
		return (1);
	if (game->bonus == 0)
		core_game_loop(game);
	else
		bonus_game_loop(game);
	return (0);
}

int	setup_game_mlx(t_game *game)
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
