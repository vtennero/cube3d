/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sky_bonus01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:41:46 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/18 12:55:47 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	calculate_angle(t_game *game)
{
	return (atan2(game->player->direction.y, game->player->direction.x));
}

void	calculate_sky_range(t_sky_render *sky)
{
	int	pitch_offset;
	int	height_offset;

	pitch_offset = (int)(sky->game->player->pitch * sky->game->screen_height);
	height_offset = (int)(sky->game->player->height * sky->game->screen_height);
	sky->sky_start = 0;
	sky->sky_end = sky->game->screen_height / 2 + pitch_offset + height_offset;
	if (sky->sky_end > sky->game->screen_height)
		sky->sky_end = sky->game->screen_height;
}

float	calculate_texture_reveal(t_game *game)
{
	return ((1.0f - game->player->pitch) / 2.0f);
}

int	calculate_tx(t_sky_render *sky, int j)
{
	float	tx_ratio;
	int		tx;

	tx_ratio = (sky->angle + atan2((j - sky->game->screen_width / 2),
				sky->game->screen_width / 2)) / (2 * M_PI);
	tx_ratio = fmodf(tx_ratio, 1.0f);
	if (tx_ratio < 0)
		tx_ratio += 1.0f;
	tx = (int)(tx_ratio * sky->game->sky_texture.width);
	if (tx < 0)
		tx = 0;
	else if (tx >= sky->game->sky_texture.width)
		tx = sky->game->sky_texture.width - 1;
	return (tx);
}

int	calculate_ty(t_sky_render *sky, int i)
{
	float	screen_ratio;
	float	ty_ratio;
	int		ty;

	screen_ratio = (float)(i - sky->sky_start)
		/ (sky->sky_end - sky->sky_start);
	ty_ratio = sky->texture_reveal
		+ screen_ratio * (1.0f - sky->texture_reveal);
	ty_ratio = fminf(fmaxf(ty_ratio, 0.0f), 1.0f);
	ty = (int)(ty_ratio * sky->game->sky_texture.height);
	if (ty < 0)
		ty = 0;
	else if (ty >= sky->game->sky_texture.height)
		ty = sky->game->sky_texture.height - 1;
	return (ty);
}
