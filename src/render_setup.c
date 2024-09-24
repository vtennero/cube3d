/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:05:32 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/24 17:06:06 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	initialize_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	return (game->mlx_ptr != NULL);
}

int	create_game_window(t_game *game)
{
	game->win_ptr = mlx_new_window(game->mlx_ptr, \
	DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "Helldivers 3D");
	if (game->win_ptr == NULL)
	{
		free(game->win_ptr);
		return (0);
	}
	return (1);
}

void	create_game_image(t_game *game)
{
	game->img.mlx_img = mlx_new_image(game->mlx_ptr, \
	DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img, \
	&game->img.bpp, &game->img.line_len, &game->img.endian);
}

void	setup_game_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, ft_key_press, game);
	mlx_loop_hook(game->mlx_ptr, &render, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, ft_key_release, game);
	mlx_hook(game->win_ptr, 17, 0, close_hook, game);
}
