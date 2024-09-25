/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_effects_strike02_bonus02.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:54:54 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/25 16:45:57 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_next_barrage_frame(t_strike *strike)
{
	strike->frame_count++;
	if (strike->frame_count % AIRSTRIKE_ANIMATION_INTERVAL == 0)
		strike->current_frame = \
		(strike->current_frame + 1) % NUM_AIRSTRIKE_FRAMES;
	return (strike->current_frame);
}

void	handle_frame_specific_actions(t_game *game, int current_frame)
{
	if (current_frame == 17)
		add_script(game, play_barrage_shell, 2);
	if (current_frame == NUM_AIRSTRIKE_FRAMES - 1)
	{
		game->strike[2].is_animating = 0;
		game->strike[2].delay_frames = 0;
		printf("Barrage Hit\n");
		randomize_barrage_location(game);
	}
}

void	adjust_barrage_sprite_dimensions(t_sprite_calc *calc)
{
	int	center_y;
	int	height_diff;
	int	center_x;
	int	width_diff;

	center_y = (calc->draw_start_y + calc->draw_end_y) / 2;
	height_diff = calc->draw_end_y - calc->draw_start_y;
	calc->draw_start_y = center_y - (int)(height_diff \
	* STRIKE_BARRAGE_SCALE / 2);
	calc->draw_end_y = center_y + (int)(height_diff * STRIKE_BARRAGE_SCALE / 2);
	center_x = (calc->draw_start_x + calc->draw_end_x) / 2;
	width_diff = calc->draw_end_x - calc->draw_start_x;
	calc->draw_start_x = center_x - (int)(width_diff \
	* STRIKE_BARRAGE_SCALE / 2);
	calc->draw_end_x = center_x + (int)(width_diff * STRIKE_BARRAGE_SCALE / 2);
}

void	calc_barr_sprite_pos(t_game *game, t_vector2d *pos, t_vector2d *sprite)
{
	t_sprite_render_context	ctx;

	init_sprite_render_context(&ctx, game, *pos, NULL);
	calc_sprite_position(&ctx);
	*sprite = ctx.calc.sprite;
}

void	transf_barr_sprite(t_game *game, \
t_vector2d sprite, t_vector2d *transform)
{
	t_sprite_render_context	ctx;

	init_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);
	ctx.calc.sprite = sprite;
	transf_sprite(&ctx);
	*transform = ctx.calc.transform;
}
