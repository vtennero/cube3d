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

void update_enemy_frame_count(t_enemy *enemy)
{
	enemy->frame_count++;
	enemy->animation_steps++;
}

int handle_periodic_jump(t_enemy *enemy)
{
	if (enemy->animation_steps >= E_JUMP_INT && (rand() % 100) < 10)
	{
		int jump = (rand() % 6) + 5;  // Jump 5-10 frames
		if (rand() % 2 == 0) jump = -jump;  // 50% chance to jump backwards
		enemy->current_frame = (enemy->current_frame + jump + E_N_FRAMES) % E_N_FRAMES;
		enemy->momentum = 0;
		enemy->animation_steps = 0;
		return 1;
	}
	return 0;
}

void adjust_momentum(t_enemy *enemy)
{
	if (enemy->momentum > 0) enemy->momentum--;
	else if (enemy->momentum < 0) enemy->momentum++;
}

int determine_direction(t_enemy *enemy)
{
	if (enemy->momentum > 0) return 1;
	if (enemy->momentum < 0) return -1;
	return (rand() % 2 == 0) ? 1 : -1;
}

int calculate_move_chance(int momentum_strength)
{
	if (momentum_strength >= 2) return 80;
	if (momentum_strength == 1) return 65;
	printf("momentum strength %d\n", momentum_strength);
	return 0;
	// return 50;
}

void update_frame_and_momentum(t_enemy *enemy, int direction, int move)
{
	if (move)
	{
		enemy->current_frame = (enemy->current_frame + direction + E_N_FRAMES) % E_N_FRAMES;
		enemy->momentum += direction;
	}
	else
	{
		enemy->current_frame = (enemy->current_frame - direction + E_N_FRAMES) % E_N_FRAMES;
		enemy->momentum -= direction;
	}
	enemy->momentum = (enemy->momentum > 3) ? 3 : (enemy->momentum < -3) ? -3 : enemy->momentum;
}

void handle_normal_transition(t_enemy *enemy)
{
	int roll = rand() % 100;
	// if (roll < 70)
	if (roll < 95)
	{
		// adjust_momentum(enemy);
	}
	else
	{
		int direction = determine_direction(enemy);
		int momentum_strength = abs(enemy->momentum);
		int move_chance = calculate_move_chance(momentum_strength);
		int move = (rand() % 100) < move_chance;
		update_frame_and_momentum(enemy, direction, move);
	}
}

int get_next_enemy_frame(t_enemy *enemy)
{
	update_enemy_frame_count(enemy);

	if (enemy->frame_count % E_ANIM_INT != 0)
		return enemy->current_frame;

	if (handle_periodic_jump(enemy))
		return enemy->current_frame;

	handle_normal_transition(enemy);

	return enemy->current_frame;
}




// ----------------------------------------

void render_enemy(t_game *game, t_enemy *enemy)
{
	int current_frame = get_next_enemy_frame(enemy);
	t_texture *enemy_texture = &game->enemy_textures[current_frame];
	col_render_sprite_common(game, enemy->position, enemy_texture);
	// render_sprite_common(game, enemy->position, enemy_texture);
}

void render_enemies(t_game *game)
{
	for (int i = 0; i < game->num_enemies; i++)
	{
		if (game->enemies[i].is_alive)
		{
			render_enemy(game, &game->enemies[i]);
		}
	}
}

// void check_enemy_at_center(t_game *game)
// {
// 	float centerX = game->screen_width / 2.0f;
// 	float centerY = game->screen_height / 2.0f;

// 	for (int i = 0; i < game->num_enemies; i++)
// 	{
// 		if (!game->enemies[i].is_alive)
// 			continue;

// 		float spriteX, spriteY;
// 		calculate_sprite_position(game, game->enemies[i].position.x, game->enemies[i].position.y, &spriteX, &spriteY);

// 		float transformX, transformY;
// 		transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

// 		int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

// 		int spriteHeight, drawStartY, drawEndY;
// 		calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

// 		int spriteWidth, drawStartX, drawEndX;
// 		calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

// 		// Check if the center of the screen is within the enemy's sprite boundaries
// 		if (centerX >= drawStartX && centerX < drawEndX &&
// 			centerY >= drawStartY && centerY < drawEndY && game->enemies[i].is_alive )
// 		{
// 			// printf("Aiming at enemy %d\n", i);
// 			if (game->is_shooting)
// 			{
// 				game->enemies[i].is_alive = 0;
// 				// play_bug_death(game);
// 				add_script(game, play_bug_death, 0);
// 			}
// 			return;  // Exit the function after finding the first enemy at the center
// 		}
// 	}

// 	// If no enemy is found at the center
// 	// printf("No enemy at the center of the screen\n");
// }

static int	is_point_in_sprite(float x, float y, const t_sprite_calc *calc)
{
	return (x >= calc->draw_start_x && x < calc->draw_end_x &&
		y >= calc->draw_start_y && y < calc->draw_end_y);
}

static void	handle_enemy_hit(t_game *game, int enemy_index)
{
	game->enemies[enemy_index].is_alive = 0;
	add_script(game, play_bug_death, 0);
}

void	check_enemy_at_center(t_game *game)
{
	float				center_x;
	float				center_y;
	t_sprite_render_context	ctx;
	int				i;

	center_x = game->screen_width / 2.0f;
	center_y = game->screen_height / 2.0f;
	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].is_alive)
		{
			col_initialize_sprite_render_context(&ctx, game,
				game->enemies[i].position, 0);
			col_calculate_sprite_transforms(&ctx);
			col_calculate_sprite_dimensions(&ctx);
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

int randomize_dead_enemy_positions(t_game *game)
{
	int i, x, y;
	int enemies_repositioned = 0;

	for (i = 0; i < game->num_enemies; i++)
	{
		if (game->enemies[i].is_alive == 0)
		{
			do {
				x = random_int(game, game->map->width);
				y = random_int(game, game->map->height);
			} while (game->map->data[y][x] == 1);

			game->enemies[i].position.x = (float)x + 0.5f;
			game->enemies[i].position.y = (float)y + 0.5f;
			game->enemies[i].is_alive = 1;
			game->enemies[i].frame_count = 0;
			game->enemies[i].current_frame = 0;
			game->enemies[i].momentum = 0;
			game->enemies[i].animation_steps = 0;
			enemies_repositioned++;
		}
	}
	return (enemies_repositioned);
}
