/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 18:49:50 by toto              #+#    #+#             */
/*   Updated: 2024/08/23 11:44:26 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_active_extract(t_game *game)
{
	t_sprite_render_context	ctx;

	init_sprite_render_context(&ctx, game, \
	game->extract[0].position, &game->extract_texture[0]);
	render_sprite_common(ctx.game, ctx.position, ctx.texture);
	if (game->extract[0].is_available == 1)
		render_extract_ray(&ctx);
}

t_vector2d	calculate_tile_position(t_vector2d base, t_vector2d perp, int i)
{
	float	offset;

	offset = (i - (EXTRACT_N_TILES - 1) / 2.0f) * EXTRACT_OFFSET;
	return ((t_vector2d){
		base.x + perp.x * offset,
		base.y + perp.y * offset
	});
}

void	render_extract_multi_tile(t_game *game, t_vector2d base)
{
	t_vector2d				perp;
	t_sprite_render_context	ctx;
	int						i;

	calculate_perpendicular(game, &perp.x, &perp.y);
	init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, &game->extract_texture[0]);
	// init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);
	i = 0;
	while (i < EXTRACT_N_TILES)
	{
		ctx.position = calculate_tile_position(base, perp, i);
		ctx.texture = &game->extract_texture[i + 1];
		render_sprite_common(ctx.game, ctx.position, ctx.texture);
		i++;
	}
}

void	render_extract(t_game *game)
{
	if (is_extract_active(game))
		render_active_extract(game);
	else if (game->extract[0].is_landing == 1)
		render_extract_multi_tile(game, game->extract[0].position);
}
