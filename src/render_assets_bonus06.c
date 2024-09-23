/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus06.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:09:56 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:10:06 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_extract_active(t_game *game)
{
	return (game->extract[0].is_available == 1 \
	|| game->extract[0].is_activated == 1);
}

float	calculate_distance_to_player(t_game *game, t_vector2d position)
{
	float	dx;
	float	dy;

	dx = position.x - game->player->position.x;
	dy = position.y - game->player->position.y;
	return (sqrt(dx * dx + dy * dy));
}

void	render_extract_ray(t_sprite_render_context *ctx)
{
	float	distance;

	calc_sprite_transforms(ctx);
	calc_sprite_dimensions(ctx);
	if (is_sprite_in_front(ctx->calc.transform.y, \
	ctx->calc.sprite_screen_x, ctx->game->screen_width))
	{
		distance = calculate_distance_to_player(ctx->game, ctx->position);
		draw_extract_stripe(ctx->game, ctx->calc.sprite_screen_x, \
		ctx->calc.draw_start_y, distance);
	}
}
