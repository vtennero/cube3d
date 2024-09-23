/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:44:50 by toto              #+#    #+#             */
/*   Updated: 2024/08/22 23:19:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	update_enemy_frame_count(t_enemy *enemy)
{
	enemy->frame_count++;
	enemy->animation_steps++;
}

int	handle_periodic_jump(t_enemy *enemy)
{
	int	jump;

	if (enemy->animation_steps >= E_JUMP_INT && (rand() % 100) < 10)
	{
		jump = (rand() % 6) + 5;
		if (rand() % 2 == 0)
			jump = -jump;
		enemy->current_frame = (enemy->current_frame \
		+ jump + E_N_FRAMES) % E_N_FRAMES;
		enemy->momentum = 0;
		enemy->animation_steps = 0;
		return (1);
	}
	return (0);
}

void	adjust_momentum(t_enemy *enemy)
{
	if (enemy->momentum > 0)
		enemy->momentum--;
	else if (enemy->momentum < 0)
		enemy->momentum++;
}

int	determine_e_direction(t_enemy *enemy)
{
	if (enemy->momentum > 0)
		return (1);
	if (enemy->momentum < 0)
		return (-1);
	if (rand() % 2 == 0)
		return (1);
	else
		return (-1);
}

int	calculate_move_chance(int momentum_strength)
{
	if (momentum_strength >= 2)
		return (80);
	if (momentum_strength == 1)
		return (65);
	return (0);
}

void	update_frame_and_momentum(t_enemy *enemy, int direction, int move)
{
	if (move)
	{
		enemy->current_frame = (enemy->current_frame \
		+ direction + E_N_FRAMES) % E_N_FRAMES;
		enemy->momentum += direction;
	}
	else
	{
		enemy->current_frame = (enemy->current_frame \
		- direction + E_N_FRAMES) % E_N_FRAMES;
		enemy->momentum -= direction;
	}
	if (enemy->momentum > 3)
		enemy->momentum = 3;
	else if (enemy->momentum < -3)
		enemy->momentum = -3;
}

void	handle_normal_transition(t_enemy *enemy)
{
	int	roll;
	int	direction;
	int	momentum_strength;
	int	move_chance;
	int	move;

	roll = rand() % 100;
	if (roll < 95)
		adjust_momentum(enemy);
	else
	{
		direction = determine_e_direction(enemy);
		momentum_strength = abs(enemy->momentum);
		move_chance = calculate_move_chance(momentum_strength);
		move = (rand() % 100) < move_chance;
		update_frame_and_momentum(enemy, direction, move);
	}
}

int	get_next_enemy_frame(t_enemy *enemy)
{
	update_enemy_frame_count(enemy);
	if (enemy->frame_count % E_ANIM_INT != 0)
		return (enemy->current_frame);
	if (handle_periodic_jump(enemy))
		return (enemy->current_frame);
	handle_normal_transition(enemy);
	return (enemy->current_frame);
}

void	render_enemy(t_game *game, t_enemy *enemy)
{
	int			current_frame;
	t_texture	*enemy_texture;

	current_frame = get_next_enemy_frame(enemy);
	enemy_texture = &game->enemy_textures[current_frame];
	render_sprite_common(game, enemy->position, enemy_texture);
}

void	render_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].is_alive)
			render_enemy(game, &game->enemies[i]);
		i++;
	}
}

static int	is_point_in_sprite(float x, float y, const t_sprite_calc *calc)
{
	return (x >= calc->draw_start_x && x < calc->draw_end_x \
	&& y >= calc->draw_start_y && y < calc->draw_end_y);
}

static void	handle_enemy_hit(t_game *game, int enemy_index)
{
	game->enemies[enemy_index].is_alive = 0;
	add_script(game, play_bug_death, 0);
}

void	check_enemy_at_center(t_game *game)
{
	float					center_x;
	float					center_y;
	t_sprite_render_context	ctx;
	int						i;

	center_x = game->screen_width / 2.0f;
	center_y = game->screen_height / 2.0f;
	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].is_alive)
		{
			init_sprite_render_context(&ctx, game, \
			game->enemies[i].position, 0);
			calc_sprite_transforms(&ctx);
			calc_sprite_dimensions(&ctx);
			if (is_point_in_sprite(center_x, center_y, &ctx.calc))
			{
				if (game->is_shooting)
					handle_enemy_hit(game, i);
				return ;
			}
		}
		i++;
	}
}

void	reinitialize_enemy(t_enemy *enemy, float x, float y)
{
	enemy->position.x = x + 0.5f;
	enemy->position.y = y + 0.5f;
	enemy->is_alive = 1;
	enemy->frame_count = 0;
	enemy->current_frame = 0;
	enemy->momentum = 0;
	enemy->animation_steps = 0;
}

int	randomize_dead_enemy_positions(t_game *game)
{
	int	i;
	int	x;
	int	y;
	int	enemies_repositioned;

	enemies_repositioned = 0;
	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].is_alive == 0)
		{
			x = random_int(game, game->map->width);
			y = random_int(game, game->map->height);
			while (game->map->data[y][x] == 1)
			{
				x = random_int(game, game->map->width);
				y = random_int(game, game->map->height);
			}
			reinitialize_enemy(&game->enemies[i], (float)x, (float)y);
			enemies_repositioned++;
		}
		i++;
	}
	return (enemies_repositioned);
}
