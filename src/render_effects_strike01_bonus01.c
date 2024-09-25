/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike01_bonus01.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:22:15 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/25 18:17:40 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_next_napalm_frame(t_strike *strike, int offset_index)
{
	int	frame;

	strike->frame_counts[offset_index] \
	+= (int)(strike->speed_multipliers[offset_index] * 100);
	if (strike->frame_counts[offset_index] < 0)
		return (-1);
	frame = (strike->frame_counts[offset_index] / 100) % NUM_NAPALM_FRAMES;
	if (strike->frame_counts[offset_index] >= NUM_NAPALM_FRAMES * 100)
		strike->frame_counts[offset_index] = 0;
	return (frame);
}

void	fill_napalm_offsets(t_vector2d *offsets, int *index, int r)
{
	int	x;
	int	y;

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (abs(x) == r || abs(y) == r)
			{
				if (*index < NUM_NAPALM_OFFSETS)
					offsets[(*index)++] = (t_vector2d){x, y};
			}
			x++;
		}
		y++;
	}
}

t_vector2d	*create_napalm_offsets(void)
{
	t_vector2d	*offsets;
	int			index;
	int			r;

	offsets = (t_vector2d *)calloc(NUM_NAPALM_OFFSETS, sizeof(t_vector2d));
	if (!offsets)
		return (NULL);
	index = 0;
	offsets[index++] = (t_vector2d){0, 0};
	r = 1;
	while (r <= 4)
	{
		fill_napalm_offsets(offsets, &index, r);
		r++;
	}
	return (offsets);
}

void	render_napalm_sprites(t_game *game, int current_frames[])
{
	t_vector2d				*offsets;
	t_sprite_render_context	ctx;
	int						i;

	offsets = create_napalm_offsets();
	if (!offsets)
		return ;
	init_sprite_render_context(&ctx, game, (t_vector2d){0, 0},  &game->extract_texture[0]);
	// init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);
	i = 0;
	while (i < NUM_NAPALM_OFFSETS)
	{
		if (current_frames[i] == -1)
		{
			i++;
			continue ;
		}
		setup_napalm_sprite_context(&ctx, game, offsets[i], \
		&game->t_napalm[current_frames[i]]);
		render_single_sprite(&ctx);
		i++;
	}
	free(offsets);
	offsets = NULL;
}

void	setup_napalm_sprite_context(t_sprite_render_context *ctx, \
t_game *game, t_vector2d offset, t_texture *texture)
{
	ctx->game = game;
	ctx->texture = texture;
	ctx->position.x = game->strike[1].position.x + offset.x;
	ctx->position.y = game->strike[1].position.y + offset.y;
	calc_sprite_transforms(ctx);
	calc_sprite_dimensions(ctx);
}
