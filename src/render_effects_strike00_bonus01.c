/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike00_bonus01.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:21:11 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:21:57 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	initialize_eagle_strike(t_game *game)
{
	int	min_index;
	int	current_frame;

	if (!game->strike[0].is_active)
		return (-1);
	min_index = get_min_starting_index_eagle(&game->strike[0]);
	current_frame = get_next_eagle_frame(&game->strike[0], min_index);
	if (game->strike[0].frame_counts[min_index] >= NUM_AIRSTRIKE_FRAMES * 100)
	{
		reset_strike(game);
		return (-1);
	}
	return (current_frame);
}

int	get_min_starting_index_eagle(t_strike *strike)
{
	int	min_index;
	int	i;

	min_index = 0;
	i = 1;
	while (i < NUM_OFFSETS)
	{
		if (strike->frame_counts[i] < strike->frame_counts[min_index])
			min_index = i;
		i++;
	}
	return (min_index);
}

void	eagle_apply_screen_shake(t_game *game, int current_frame)
{
	float	shake_offset;

	shake_offset = calculate_screen_shake(game, current_frame);
	if (game->player->is_dead == 0)
		game->player->height = PLAYER_B_HEIGHT + shake_offset;
}

t_vector2d	*create_eagle_offsets(void)
{
	t_vector2d	*offsets;

	offsets = (t_vector2d *)malloc(NUM_OFFSETS * sizeof(t_vector2d));
	if (!offsets)
		return (NULL);
	offsets[0] = (t_vector2d){0, 0};
	offsets[1] = (t_vector2d){1, 0};
	offsets[2] = (t_vector2d){-1, 0};
	offsets[3] = (t_vector2d){0, 1};
	offsets[4] = (t_vector2d){0, -1};
	offsets[5] = (t_vector2d){1, 1};
	offsets[6] = (t_vector2d){1, -1};
	offsets[7] = (t_vector2d){-1, 1};
	offsets[8] = (t_vector2d){-1, -1};
	offsets[9] = (t_vector2d){2, 0};
	offsets[10] = (t_vector2d){-2, 0};
	offsets[11] = (t_vector2d){0, 2};
	offsets[12] = (t_vector2d){0, -2};
	return (offsets);
}

void	render_eagle_sprites(t_game *game)
{
	t_vector2d				*offsets;
	t_sprite_render_context	ctx;
	int						offset_frame;
	int						i;

	offsets = create_eagle_offsets();
	if (!offsets)
		return ;
	init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);
	i = 0;
	while (i < NUM_OFFSETS)
	{
		offset_frame = get_next_eagle_frame(&game->strike[0], i);
		if (offset_frame == -1)
		{
			i++;
			continue ;
		}
		setup_sprite_context(&ctx, game, offsets[i], \
		&game->t_eagle[offset_frame]);
		render_single_sprite(&ctx);
		i++;
	}
	free(offsets);
	offsets = NULL;
}
