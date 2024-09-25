/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_assets_bonus10.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:13:02 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/25 18:20:29 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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

// void	check_enemy_at_center(t_game *game)
// {
// 	float					center_x;
// 	float					center_y;
// 	t_sprite_render_context	ctx;
// 	int						i;

// 	center_x = game->screen_width / 2.0f;
// 	center_y = game->screen_height / 2.0f;
// 	i = 0;
// 	while (i < game->num_enemies)
// 	{
// 		if (game->enemies[i].is_alive)
// 		{
// 			init_sprite_render_context(&ctx, game,
// 			game->enemies[i].position, 0);
// 			calc_sprite_transforms(&ctx);
// 			calc_sprite_dimensions(&ctx);
// 			if (is_point_in_sprite(center_x, center_y, &ctx.calc))
// 			{
// 				if (game->is_shooting)
// 					handle_enemy_hit(game, i);
// 				return ;
// 			}
// 		}
// 		i++;
// 	}
// }

void check_enemy_at_center(t_game *game)
{
    float center_x;
    float center_y;
    t_sprite_render_context ctx;
    int i;

    if (!game || game->num_enemies <= 0 || !game->enemies)
    {
        printf("Error: Invalid game state in check_enemy_at_center\n");
        return;
    }

    center_x = game->screen_width / 2.0f;
    center_y = game->screen_height / 2.0f;

    for (i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].is_alive)
        {
            // Use the current_frame as the texture index
            int texture_index = game->enemies[i].current_frame;
            if (texture_index < 0 || texture_index >= MAX_ENEMY_TEXTURES)
            {
                printf("Warning: Invalid texture index %d for enemy %d\n", texture_index, i);
                continue;
            }

            t_texture *enemy_texture = &game->enemy_textures[texture_index];

            // Check if the texture is valid
            if (!enemy_texture->data)
            {
                printf("Warning: Invalid texture data for enemy %d, frame %d\n", i, texture_index);
                continue;
            }

            if (!init_sprite_render_context(&ctx, game, game->enemies[i].position, enemy_texture))
            {
                printf("Error: Failed to initialize sprite render context for enemy %d\n", i);
                continue;
            }

            calc_sprite_transforms(&ctx);
            calc_sprite_dimensions(&ctx);

            if (is_point_in_sprite(center_x, center_y, &ctx.calc))
            {
                if (game->is_shooting)
                    handle_enemy_hit(game, i);
                return;
            }
        }
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
