/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_bonus01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:46:30 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/11 13:46:30 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	handle_first_loop(t_game *game)
{
	int	frame_to_render;

	frame_to_render = get_current_frame(&game->opening_start_time);
	play_audio_on_frame(game, frame_to_render);
	if (frame_to_render >= MAX_OPENING_TEXTURES - 1)
		frame_to_render = prepare_second_loop(game);
	return (frame_to_render);
}
int	handle_second_loop(t_game *game)
{
	int	elapsed_frames;
	int	frame_to_render;

	elapsed_frames = get_current_frame(&game->opening_start_time);
	frame_to_render = game->opening_state.randomized_frames[
		elapsed_frames % (MAX_OPENING_TEXTURES - SECOND_LOOP_START)];
	if (elapsed_frames >= MAX_OPENING_TEXTURES - SECOND_LOOP_START)
	{
		game->opening_state.second_loop_count++;
		check_second_loop_end(game);
	}
	return (frame_to_render);
}

void	render_current_frame(t_game *game, int frame_to_render)
{
	t_texture	*opening_texture;

	opening_texture = &game->opening_texture[frame_to_render];
	check_texture_loaded(opening_texture);
	render_frame(game, opening_texture);
}

int	select_frame_to_render(t_game *game)
{
	int	frame_to_render;

	if (game->opening_state.current_loop == 0)
		frame_to_render = handle_first_loop(game);
	else
		frame_to_render = handle_second_loop(game);
	return (frame_to_render);
}

void	render_opening(t_game *game)
{
	int	frame_to_render;

	frame_to_render = select_frame_to_render(game);
	if (game->game_sequence == 2)
		return;
	render_current_frame(game, frame_to_render);
	game->current_frame = frame_to_render;
}
