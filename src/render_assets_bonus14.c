/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus14.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:17:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:17:07 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_ray_node	*find_ray_node(t_game *game, int stripe)
{
	t_ray_node	*current;

	current = game->ray_list;
	while (current && current->ray.x != stripe)
		current = current->next;
	return (current);
}

int	is_point_in_sprite(t_vector2d point, const t_sprite_calc *calc)
{
	return (point.x >= calc->draw_start_x && point.x < calc->draw_end_x
		&& point.y >= calc->draw_start_y && point.y < calc->draw_end_y);
}

t_vector2d	calculate_screen_center(t_game *game)
{
	t_vector2d	center;

	center.x = game->screen_width / 2.0f;
	center.y = game->screen_height / 2.0f;
	return (center);
}

int	is_enemy_texture_valid(t_game *game, int enemy_index, int texture_index)
{
	t_texture	*enemy_texture;

	if (texture_index < 0 || texture_index >= MAX_ENEMY_TEXTURES)
	{
		printf("Warning: Invalid texture index %d for \
		enemy %d\n", texture_index, enemy_index);
		return (0);
	}
	enemy_texture = &game->enemy_textures[texture_index];
	if (!enemy_texture->data)
	{
		printf("Warning: Invalid texture data for \
		enemy %d, frame %d\n", enemy_index, texture_index);
		return (0);
	}
	return (1);
}

int	process_enemy(t_game *game, int enemy_index, t_vector2d center)
{
	int						texture_index;
	t_texture				*enemy_texture;
	t_sprite_render_context	ctx;

	texture_index = game->enemies[enemy_index].current_frame;
	if (!is_enemy_texture_valid(game, enemy_index, texture_index))
		return (0);
	enemy_texture = &game->enemy_textures[texture_index];
	if (!init_sprite_render_context(&ctx, game, \
	game->enemies[enemy_index].position, enemy_texture))
	{
		printf("Error: Failed to initialize sprite render \
		context for enemy %d\n", enemy_index);
		return (0);
	}
	calc_sprite_transforms(&ctx);
	calc_sprite_dimensions(&ctx);
	if (is_point_in_sprite(center, &ctx.calc))
	{
		if (game->is_shooting)
			handle_enemy_hit(game, enemy_index);
		return (1);
	}
	return (0);
}
