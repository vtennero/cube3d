/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strike_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:43:39 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 17:54:30 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float calculate_screen_shake(t_game *game, int current_frame)
{
	if (current_frame >= STRIKE_SHAKE_DURATION || game->player->is_dead == 1)
		return 0.0f;

	// Use the random number generator for unpredictable shake
	float random_offset = (float)random_int(game, 1000) / 1000.0f;

	// Calculate a decreasing intensity over time
	float intensity = STRIKE_SHAKE_INTENSITY * (1.0f - (float)current_frame / STRIKE_SHAKE_DURATION);

	// Use a sine wave for a bouncing effect
	float shake = sinf(current_frame * 0.5f) * intensity;

	// Combine the sine wave with the random offset for more chaotic movement
	return shake * random_offset;
}

int	calculate_color_with_base(int i, int total_width, int white_width, int base_color)
{
	float	gradient;
	int		color_value;

	if (i == 0 || (i >= -white_width / 2 && i < white_width / 2))
		return (0xFFFFFF);
	else
	{
		gradient = 1.0f - (float)abs(i) / (total_width / 2);
		color_value = 128 + (int)(127 * gradient);
		return (color_value << (base_color == 0xFF0000 ? 16 : 0));
	}
}

void	draw_strike_stripe(t_game *game, int stripe, int draw_end_y, float distance)
{
	int	total_width;
	int	white_width;
	int	y;
	int	i;
	int	color;

	calculate_widths(game, distance, &total_width, &white_width);
	y = 0;
	while (y < draw_end_y)
	{
		i = -total_width / 2;
		while (i < total_width / 2)
		{
			color = calculate_color_with_base(i, total_width, white_width, 0xFF0000);
			draw_stripe_pixel(game, stripe + i, y, color);
			i++;
		}
		y++;
	}
}

void render_call_strike(t_game *game, t_vector2d position)
{
	t_sprite_render_context ctx;
	col_initialize_sprite_render_context(&ctx, game, position, NULL); // Assuming no texture is needed for the strike

	col_calculate_sprite_transforms(&ctx);
	col_calculate_sprite_dimensions(&ctx);

	float distance = calculate_distance_to_player(game, position);

	// We only need to render a single stripe for the strike
	int stripe = ctx.calc.sprite_screen_x;
	if (ctx.calc.transform_y > 0 && stripe > 0 && stripe < game->screen_width)
		draw_strike_stripe(game, stripe, ctx.calc.draw_end_y, distance);
}

int get_next_airstrike_frame(t_strike *strike, int offset_index)
{
	strike[0].frame_counts[offset_index] += strike[0].speed_multipliers[offset_index];

	if (strike[0].frame_counts[offset_index] < 0)
		return -1;  // Indicate that nothing should be displayed

	int frame = (int)(strike[0].frame_counts[offset_index] / 100) % NUM_AIRSTRIKE_FRAMES;

	// printf("Offset %d: Frame count %.2d, Speed %.2f, Current frame %d\n",
	//        offset_index, strike[0].frame_counts[offset_index], strike[0].speed_multipliers[offset_index], frame);

	return frame;
}

int get_min_starting_index(t_strike *strike)
{
	int min_index = 0;
	for (int i = 1; i < NUM_OFFSETS; i++)
	{
		if (strike->frame_counts[i] < strike->frame_counts[min_index])
		{
			min_index = i;
		}
	}
	return min_index;
}

// void render_ongoing_strike(t_game *game)
// {
// 	if (!game->strike[0].is_active)
// 		return;

// 	int min_index = get_min_starting_index(&game->strike[0]);
// 	int current_frame = get_next_airstrike_frame(&game->strike[0], min_index);

// 	if (game->strike[0].frame_counts[min_index] >= NUM_AIRSTRIKE_FRAMES * 100)
// 	{
// 		// Reset strike logic (same as original)
// 		game->strike[0].is_active = 0;
// 		game->strike[0].is_animating = 0;
// 		for (int i = 0; i < NUM_OFFSETS; i++)
// 		{
// 			game->strike[0].frame_counts[i] = rand() % (NUM_AIRSTRIKE_FRAMES * 100);
// 		}
// 		printf("Strike deactivated and reset\n");
// 		return;
// 	}

// 	// Calculate screen shake offset (same as original)
// 	float shake_offset = calculate_screen_shake(game, current_frame);

// 	// Apply screen shake to player height (same as original)
// 	if (game->player->is_dead == 0)
// 		game->player->height = PLAYER_B_HEIGHT + shake_offset;

// 	int offsets[NUM_OFFSETS][2] =
// 	{
// 		{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1},
// 		{1, 1}, {1, -1}, {-1, 1}, {-1, -1},
// 		{2, 0}, {-2, 0}, {0, 2}, {0, -2}
// 	};

// 	t_sprite_render_context ctx;
// 	col_initialize_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);

// 	for (int i = 0; i < NUM_OFFSETS; i++)
// 	{
// 		int offset_frame = get_next_airstrike_frame(&game->strike[0], i);
// 		if (offset_frame == -1)
// 			continue;

// 		ctx.texture = &game->airstrike_textures[offset_frame];
// 		ctx.position.x = game->strike[0].position.x + offsets[i][0];
// 		ctx.position.y = game->strike[0].position.y + offsets[i][1];

// 		col_calculate_sprite_transforms(&ctx);
// 		col_calculate_sprite_dimensions(&ctx);

// 		for (int stripe = ctx.calc.draw_start_x; stripe < ctx.calc.draw_end_x; stripe++)
// 		{
// 			if (is_sprite_in_front(ctx.calc.transform_y, stripe, game->screen_width))
// 			{
// 				draw_sprite_stripe(game, ctx.texture, stripe, ctx.calc.draw_start_y, ctx.calc.draw_end_y,
// 								   ctx.calc.sprite_height, ctx.calc.sprite_width, ctx.calc.sprite_screen_x, ctx.calc.transform_y);
// 			}
// 		}
// 	}
// }



int initialize_strike(t_game *game)
{
    if (!game->strike[0].is_active)
        return -1;

    int min_index = get_min_starting_index(&game->strike[0]);
    int current_frame = get_next_airstrike_frame(&game->strike[0], min_index);

    if (game->strike[0].frame_counts[min_index] >= NUM_AIRSTRIKE_FRAMES * 100)
    {
        reset_strike(game);
        return -1;
    }

    return current_frame;
}

void reset_strike(t_game *game)
{
    game->strike[0].is_active = 0;
    game->strike[0].is_animating = 0;
    for (int i = 0; i < NUM_OFFSETS; i++)
    {
        game->strike[0].frame_counts[i] = rand() % (NUM_AIRSTRIKE_FRAMES * 100);
    }
    printf("Strike deactivated and reset\n");
}

void apply_screen_shake(t_game *game, int current_frame)
{
    float shake_offset = calculate_screen_shake(game, current_frame);
    if (game->player->is_dead == 0)
        game->player->height = PLAYER_B_HEIGHT + shake_offset;
}

void render_strike_sprites(t_game *game)
{
    t_vector2d offsets[NUM_OFFSETS] = {
        {0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
        {2, 0}, {-2, 0}, {0, 2}, {0, -2}
    };

    t_sprite_render_context ctx;
    col_initialize_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);

    for (int i = 0; i < NUM_OFFSETS; i++)
    {
        int offset_frame = get_next_airstrike_frame(&game->strike[0], i);
        if (offset_frame == -1)
            continue;

        setup_sprite_context(&ctx, game, offsets[i], &game->airstrike_textures[offset_frame]);
        render_single_sprite(&ctx);
    }
}

void setup_sprite_context(t_sprite_render_context *ctx, t_game *game, t_vector2d offset, t_texture *texture)
{
    ctx->texture = texture;
    ctx->position.x = game->strike[0].position.x + offset.x;
    ctx->position.y = game->strike[0].position.y + offset.y;

    col_calculate_sprite_transforms(ctx);
    col_calculate_sprite_dimensions(ctx);
}

void render_single_sprite(t_sprite_render_context *ctx)
{
    for (int stripe = ctx->calc.draw_start_x; stripe < ctx->calc.draw_end_x; stripe++)
    {
        if (is_sprite_in_front(ctx->calc.transform_y, stripe, ctx->game->screen_width))
        {
            draw_sprite_stripe(ctx->game, ctx->texture, stripe, ctx->calc.draw_start_y, ctx->calc.draw_end_y,
                               ctx->calc.sprite_height, ctx->calc.sprite_width, ctx->calc.sprite_screen_x, ctx->calc.transform_y);
        }
    }
}

void render_ongoing_strike(t_game *game)
{
    int current_frame = initialize_strike(game);
    if (current_frame == -1) return;  // Strike not active or needs reset

    apply_screen_shake(game, current_frame);
    render_strike_sprites(game);
}

void render_strike(t_game *game)
{
	int frame_counter = 0;
	frame_counter++;

	// printf("Frame: %d\n", frame_counter);

	if (game->strike[0].is_launching)
		render_call_strike(game, game->strike[0].position);
	else if (game->strike[0].is_active)
		render_ongoing_strike(game);
}

int get_next_napalm_frame(t_strike *strike, int offset_index)
{
	strike->frame_counts[offset_index] += (int)(strike->speed_multipliers[offset_index] * 100);

	if (strike->frame_counts[offset_index] < 0)
		return -1;
	int frame = (strike->frame_counts[offset_index] / 100) % NUM_NAPALM_FRAMES;

	if (strike->frame_counts[offset_index] >= NUM_NAPALM_FRAMES * 100)
		strike->frame_counts[offset_index] = 0;
	return frame;
}

// void render_ongoing_napalm(t_game *game)
// {
// 	if (!game->strike[1].is_active)
// 		return;

// 	int first_visible_frame = -1;
// 	int current_frames[NUM_NAPALM_OFFSETS];

// 	// Update all frame counts and get current frames
// 	for (int i = 0; i < NUM_NAPALM_OFFSETS; i++)
// 	{
// 		current_frames[i] = get_next_napalm_frame(&game->strike[1], i);
// 		if (first_visible_frame == -1 && current_frames[i] != -1)
// 		{
// 			first_visible_frame = current_frames[i];
// 		}
// 	}

// 	// Screen shake calculation
// 	if (game->strike[1].is_animating && first_visible_frame != -1)
// 	{
// 		float shake_offset = calculate_screen_shake(game, first_visible_frame);
// 		if (game->player->is_dead == 0)
// 			game->player->height = PLAYER_B_HEIGHT + shake_offset;

// 		// Check if we've completed one full cycle
// 		if (game->strike[1].frame_counts[0] >= NUM_NAPALM_FRAMES * 50)
// 		{
// 			game->strike[1].is_animating = 0;
// 		}
// 	}
// 	else if (game->player->is_dead == 0)
// 	{
// 		game->player->height = PLAYER_B_HEIGHT;
// 	}

// 	int offsets[NUM_NAPALM_OFFSETS][2] = {
// 		{0, 0},
// 		{1, 0}, {-1, 0}, {0, 1}, {0, -1},
// 		{1, 1}, {1, -1}, {-1, 1}, {-1, -1},
// 		{2, 0}, {-2, 0}, {0, 2}, {0, -2},
// 		{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
// 		{3, 0}, {-3, 0}, {0, 3}, {0, -3},
// 		{3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {1, 3}, {1, -3}, {-1, 3}, {-1, -3},
// 		{4, 0}, {-4, 0}, {0, 4}, {0, -4}
// 	};


// 	for (int i = 0; i < NUM_NAPALM_OFFSETS; i++)
// 	{
// 		if (current_frames[i] == -1)
// 			continue;

// 		t_texture *napalm_texture = &game->napalm_textures[current_frames[i]];

// 		float spriteX, spriteY;
// 		calculate_sprite_position(game,
// 								  game->strike[1].position.x + offsets[i][0],
// 								  game->strike[1].position.y + offsets[i][1],
// 								  &spriteX, &spriteY);

// 		float transformX, transformY;
// 		transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

// 		int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

// 		int spriteHeight, drawStartY, drawEndY;
// 		calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

// 		int spriteWidth, drawStartX, drawEndX;
// 		calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

// 		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
// 		{
// 			if (is_sprite_in_front(transformY, stripe, game->screen_width))
// 			{
// 				draw_sprite_stripe(game, napalm_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
// 			}
// 		}
// 	}
// }

void render_ongoing_napalm(t_game *game)
{
    int current_frames[NUM_NAPALM_OFFSETS];
    int first_visible_frame = initialize_napalm(game, current_frames);
    if (first_visible_frame == -1) return;  // Napalm not active

    apply_napalm_screen_shake(game, first_visible_frame);
    render_napalm_sprites(game, current_frames);
}

int initialize_napalm(t_game *game, int current_frames[])
{
    if (!game->strike[1].is_active)
        return -1;

    int first_visible_frame = -1;
    for (int i = 0; i < NUM_NAPALM_OFFSETS; i++)
    {
        current_frames[i] = get_next_napalm_frame(&game->strike[1], i);
        if (first_visible_frame == -1 && current_frames[i] != -1)
        {
            first_visible_frame = current_frames[i];
        }
    }
    return first_visible_frame;
}

void apply_napalm_screen_shake(t_game *game, int first_visible_frame)
{
    if (game->strike[1].is_animating && first_visible_frame != -1)
    {
        float shake_offset = calculate_screen_shake(game, first_visible_frame);
        if (game->player->is_dead == 0)
            game->player->height = PLAYER_B_HEIGHT + shake_offset;

        // Check if we've completed one full cycle
        if (game->strike[1].frame_counts[0] >= NUM_NAPALM_FRAMES * 50)
        {
            game->strike[1].is_animating = 0;
        }
    }
    else if (game->player->is_dead == 0)
    {
        game->player->height = PLAYER_B_HEIGHT;
    }
}

void render_napalm_sprites(t_game *game, int current_frames[])
{
    t_vector2d offsets[NUM_NAPALM_OFFSETS] = {
        {0, 0},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
        {2, 0}, {-2, 0}, {0, 2}, {0, -2},
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
        {3, 0}, {-3, 0}, {0, 3}, {0, -3},
        {3, 1}, {3, -1}, {-3, 1}, {-3, -1}, {1, 3}, {1, -3}, {-1, 3}, {-1, -3},
        {4, 0}, {-4, 0}, {0, 4}, {0, -4}
    };

    t_sprite_render_context ctx;
    col_initialize_sprite_render_context(&ctx, game, (t_vector2d){0, 0}, NULL);

    for (int i = 0; i < NUM_NAPALM_OFFSETS; i++)
    {
        if (current_frames[i] == -1)
            continue;

        setup_napalm_sprite_context(&ctx, game, offsets[i], &game->napalm_textures[current_frames[i]]);
        render_single_sprite(&ctx);
    }
}

void setup_napalm_sprite_context(t_sprite_render_context *ctx, t_game *game, t_vector2d offset, t_texture *texture)
{
    ctx->texture = texture;
    ctx->position.x = game->strike[1].position.x + offset.x;
    ctx->position.y = game->strike[1].position.y + offset.y;

    float spriteX, spriteY;
    calculate_sprite_position(game, ctx->position.x, ctx->position.y, &spriteX, &spriteY);

    float transformX, transformY;
    transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

    ctx->calc.sprite_screen_x = calculate_sprite_screen_x(game, transformX, transformY);

    calculate_sprite_height(game, transformY, &ctx->calc.sprite_height, &ctx->calc.draw_start_y, &ctx->calc.draw_end_y);
    calculate_sprite_width(game, transformY, ctx->calc.sprite_screen_x, &ctx->calc.sprite_width, &ctx->calc.draw_start_x, &ctx->calc.draw_end_x);

    ctx->calc.transform_y = transformY;
}


void render_napalm(t_game *game)
{
	if (game->strike[1].is_launching)
	{
		render_call_strike(game, game->strike[1].position);
		game->strike[1].is_animating = 1; // Start animating when launching
	}
	else if (game->strike[1].is_active)
	{
		render_ongoing_napalm(game);
	}
}


// void randomize_barrage_location(t_game *game)
// {
// 	// Assuming the game map is a grid with dimensions defined somewhere
// 	int map_width = game->map->width;
// 	int map_height = game->map->height;

// 	// Define the proximity radius (adjust this value as needed)
// 	float proximity_radius = 10.0f; // For example, 5 units radius

// 	// Generate random angle and distance within the proximity radius
// 	float angle = random_float(game) * 2 * M_PI; // Random angle between 0 and 2π
// 	float distance = random_float(game) * proximity_radius; // Random distance within the radius

// 	// Calculate new position relative to base position
// 	float delta_x = cosf(angle) * distance;
// 	float delta_y = sinf(angle) * distance;

// 	// Calculate new absolute position
// 	int new_x = (int)(game->strike[2].base_position.x + delta_x);
// 	int new_y = (int)(game->strike[2].base_position.y + delta_y);

// 	// Ensure the new position is within map bounds
// 	new_x = fmax(0, fmin(new_x, map_width - 1));
// 	new_y = fmax(0, fmin(new_y, map_height - 1));

// 	// Update the strike position (not the base position)
// 	game->strike[2].position.x = new_x;
// 	game->strike[2].position.y = new_y;

// 	// Ensure the new position is valid
// 	int attempts = 0;
// 	while (!is_valid_location(game, new_x, new_y) && attempts < 10)
// 	{
// 		// If not valid, try a new random position
// 		angle = random_float(game) * 2 * M_PI;
// 		distance = random_float(game) * proximity_radius;
// 		delta_x = cosf(angle) * distance;
// 		delta_y = sinf(angle) * distance;
// 		new_x = (int)(game->strike[2].base_position.x + delta_x);
// 		new_y = (int)(game->strike[2].base_position.y + delta_y);
// 		new_x = fmax(0, fmin(new_x, map_width - 1));
// 		new_y = fmax(0, fmin(new_y, map_height - 1));
// 		game->strike[2].position.x = new_x;
// 		game->strike[2].position.y = new_y;
// 		attempts++;
// 	}

// 	// Reset relevant strike parameters
// 	game->strike[2].frame_count = 0;
// 	game->strike[2].current_frame = 0;
// 	game->strike[2].is_active = 1;
// 	game->strike[2].is_launching = 1;
// 	game->strike[2].is_animating = 0;
// 	game->strike[2].delay_frames = 0;
// 	game->strike[2].delay_duration = 60 * 2; // 3 seconds at 60 FPS, adjust as needed

// 	// Debug output
// 	printf("New barrage location: (%d, %d), Base position: (%f, %f)\n",
// 		   new_x, new_y,
// 		   game->strike[2].base_position.x,
// 		   game->strike[2].base_position.y);
// }


// New helper functions
t_vector2d generate_random_offset(t_game *game, float proximity_radius)
{
    float angle = random_float(game) * 2 * M_PI;
    float distance = random_float(game) * proximity_radius;

    t_vector2d offset;
    offset.x = cosf(angle) * distance;
    offset.y = sinf(angle) * distance;

    return offset;
}

t_vector2d calculate_new_position(t_vector2d base_position, t_vector2d offset)
{
    t_vector2d new_position;
    new_position.x = base_position.x + offset.x;
    new_position.y = base_position.y + offset.y;
    return new_position;
}

t_vector2d clamp_position(t_vector2d position, int map_width, int map_height)
{
    t_vector2d clamped;
    clamped.x = fmax(0, fmin(position.x, map_width - 1));
    clamped.y = fmax(0, fmin(position.y, map_height - 1));
    return clamped;
}

void reset_strike_parameters(t_strike *strike)
{
    strike->frame_count = 0;
    strike->current_frame = 0;
    strike->is_active = 1;
    strike->is_launching = 1;
    strike->is_animating = 0;
    strike->delay_frames = 0;
    strike->delay_duration = 60 * 2; // 3 seconds at 60 FPS, adjust as needed
}

void debug_output(t_vector2d new_position, t_vector2d base_position)
{
    printf("New barrage location: (%f, %f), Base position: (%f, %f)\n",
           new_position.x, new_position.y,
           base_position.x, base_position.y);
}

// Main function
void randomize_barrage_location(t_game *game)
{
    int map_width = game->map->width;
    int map_height = game->map->height;
    float proximity_radius = 10.0f;

    t_vector2d offset = generate_random_offset(game, proximity_radius);
    t_vector2d new_position = calculate_new_position(game->strike[2].base_position, offset);
    new_position = clamp_position(new_position, map_width, map_height);

    int attempts = 0;
    while (!is_valid_location(game, (int)new_position.x, (int)new_position.y) && attempts < 10)
    {
        offset = generate_random_offset(game, proximity_radius);
        new_position = calculate_new_position(game->strike[2].base_position, offset);
        new_position = clamp_position(new_position, map_width, map_height);
        attempts++;
    }

    game->strike[2].position.x = new_position.x;
    game->strike[2].position.y = new_position.y;

    reset_strike_parameters(&game->strike[2]);
    debug_output(new_position, game->strike[2].base_position);
}


int get_next_barrage_frame(t_strike *strike)
{
	strike->frame_count++;

	if (strike->frame_count % AIRSTRIKE_ANIMATION_INTERVAL == 0)
		strike->current_frame = (strike->current_frame + 1) % NUM_AIRSTRIKE_FRAMES;
	return strike->current_frame;
}


// void render_ongoing_barrage(t_game *game)
// {
// 	if (!game->strike[2].is_active)
// 		return;

// 	int current_frame = get_next_barrage_frame(&game->strike[2]);
// 	t_texture *strike_texture = &game->airstrike_textures[current_frame];
// 	printf("render_ongoing_barrage: current_frame: %d\n", current_frame);

// 	float shake_offset = calculate_screen_shake(game, current_frame);

// 	if (game->player->is_dead == 0)
// 		game->player->height = PLAYER_B_HEIGHT + shake_offset;

// 	int offsets[1][2] = {{0, 0}};

// 	for (int i = 0; i < 1; i++)
// 	{
// 		float spriteX, spriteY;
// 		calculate_sprite_position(game,
// 								  game->strike[2].position.x + offsets[i][0],
// 								  game->strike[2].position.y + offsets[i][1],
// 								  &spriteX, &spriteY);

// 		float transformX, transformY;
// 		transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

// 		int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

// 		int spriteHeight, drawStartY, drawEndY;
// 		calculate_sprite_height(game, transformY / STRIKE_BARRAGE_SCALE, &spriteHeight, &drawStartY, &drawEndY);

// 		// Adjust drawStartY and drawEndY for scaling
// 		int centerY = (drawStartY + drawEndY) / 2;
// 		drawStartY = centerY - (int)((drawEndY - drawStartY) * STRIKE_BARRAGE_SCALE / 2);
// 		drawEndY = centerY + (int)((drawEndY - drawStartY) * STRIKE_BARRAGE_SCALE / 2);

// 		int spriteWidth, drawStartX, drawEndX;
// 		calculate_sprite_width(game, transformY / STRIKE_BARRAGE_SCALE, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

// 		// Adjust drawStartX and drawEndX for scaling
// 		int centerX = (drawStartX + drawEndX) / 2;
// 		drawStartX = centerX - (int)((drawEndX - drawStartX) * STRIKE_BARRAGE_SCALE / 2);
// 		drawEndX = centerX + (int)((drawEndX - drawStartX) * STRIKE_BARRAGE_SCALE / 2);

// 		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
// 		{
// 			if (is_sprite_in_front(transformY, stripe, game->screen_width))
// 			{
// 				draw_sprite_stripe(game, strike_texture, stripe, drawStartY, drawEndY, spriteHeight * STRIKE_BARRAGE_SCALE, spriteWidth * STRIKE_BARRAGE_SCALE, spriteScreenX, transformY);
// 			}
// 		}

// 		if (current_frame == 17)
// 			add_script(game, play_barrage_shell, 1);
// 		if (current_frame == NUM_AIRSTRIKE_FRAMES - 1)
// 		{
// 			game->strike[2].is_animating = 0;
// 			game->strike[2].delay_frames = 0;
// 			printf("render_ongoing_barrage: Completed full animation cycle, randomizing location\n");
// 			printf("Barrage Hit\n");
// 			randomize_barrage_location(game);
// 		}
// 	}
// }


void render_ongoing_barrage(t_game *game)
{
    int current_frame = initialize_barrage(game);
    if (current_frame == -1) return;  // Barrage not active

    apply_barrage_screen_shake(game, current_frame);
    render_barrage_sprite(game, current_frame);
    handle_frame_specific_actions(game, current_frame);
}

int initialize_barrage(t_game *game)
{
    if (!game->strike[2].is_active)
        return -1;

    int current_frame = get_next_barrage_frame(&game->strike[2]);
    printf("render_ongoing_barrage: current_frame: %d\n", current_frame);
    return current_frame;
}

void apply_barrage_screen_shake(t_game *game, int current_frame)
{
    float shake_offset = calculate_screen_shake(game, current_frame);
    if (game->player->is_dead == 0)
        game->player->height = PLAYER_B_HEIGHT + shake_offset;
}

void render_barrage_sprite(t_game *game, int current_frame)
{
    t_sprite_render_context ctx;
    t_vector2d offset = {0, 0};
    t_texture *strike_texture = &game->airstrike_textures[current_frame];

    setup_barrage_sprite_context(&ctx, game, offset, strike_texture);

    for (int stripe = ctx.calc.draw_start_x; stripe < ctx.calc.draw_end_x; stripe++)
    {
        if (is_sprite_in_front(ctx.calc.transform_y, stripe, game->screen_width))
        {
            draw_sprite_stripe(game, ctx.texture, stripe, ctx.calc.draw_start_y, ctx.calc.draw_end_y,
                               ctx.calc.sprite_height * STRIKE_BARRAGE_SCALE,
                               ctx.calc.sprite_width * STRIKE_BARRAGE_SCALE,
                               ctx.calc.sprite_screen_x, ctx.calc.transform_y);
        }
    }
}

void setup_barrage_sprite_context(t_sprite_render_context *ctx, t_game *game, t_vector2d offset, t_texture *texture)
{
    ctx->texture = texture;
    ctx->position.x = game->strike[2].position.x + offset.x;
    ctx->position.y = game->strike[2].position.y + offset.y;

    float spriteX, spriteY, transformX, transformY;
    calculate_barrage_sprite_position(game, &ctx->position, &spriteX, &spriteY);
    transform_barrage_sprite(game, spriteX, spriteY, &transformX, &transformY);
    calculate_barrage_sprite_screen_x(game, transformX, transformY, &ctx->calc.sprite_screen_x);

    ctx->calc.transform_y = transformY;
    calculate_barrage_sprite_dimensions(game, transformY, &ctx->calc);
    adjust_barrage_sprite_dimensions_for_scaling(&ctx->calc);
}

void calculate_barrage_sprite_position(t_game *game, t_vector2d *position, float *spriteX, float *spriteY)
{
    calculate_sprite_position(game, position->x, position->y, spriteX, spriteY);
}

void transform_barrage_sprite(t_game *game, float spriteX, float spriteY, float *transformX, float *transformY)
{
    transform_sprite(game, spriteX, spriteY, transformX, transformY);
}

void calculate_barrage_sprite_screen_x(t_game *game, float transformX, float transformY, int *spriteScreenX)
{
    *spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);
}

void calculate_barrage_sprite_dimensions(t_game *game, float transformY, t_sprite_calc *calc)
{
    calculate_sprite_height(game, transformY / STRIKE_BARRAGE_SCALE, &calc->sprite_height, &calc->draw_start_y, &calc->draw_end_y);
    calculate_sprite_width(game, transformY / STRIKE_BARRAGE_SCALE, calc->sprite_screen_x, &calc->sprite_width, &calc->draw_start_x, &calc->draw_end_x);
}

void adjust_barrage_sprite_dimensions_for_scaling(t_sprite_calc *calc)
{
    // Adjust Y dimensions
    int centerY = (calc->draw_start_y + calc->draw_end_y) / 2;
    int heightDiff = calc->draw_end_y - calc->draw_start_y;
    calc->draw_start_y = centerY - (int)(heightDiff * STRIKE_BARRAGE_SCALE / 2);
    calc->draw_end_y = centerY + (int)(heightDiff * STRIKE_BARRAGE_SCALE / 2);

    // Adjust X dimensions
    int centerX = (calc->draw_start_x + calc->draw_end_x) / 2;
    int widthDiff = calc->draw_end_x - calc->draw_start_x;
    calc->draw_start_x = centerX - (int)(widthDiff * STRIKE_BARRAGE_SCALE / 2);
    calc->draw_end_x = centerX + (int)(widthDiff * STRIKE_BARRAGE_SCALE / 2);
}

void handle_frame_specific_actions(t_game *game, int current_frame)
{
    if (current_frame == 17)
        add_script(game, play_barrage_shell, 1);
    if (current_frame == NUM_AIRSTRIKE_FRAMES - 1)
    {
        game->strike[2].is_animating = 0;
        game->strike[2].delay_frames = 0;
        printf("render_ongoing_barrage: Completed full animation cycle, randomizing location\n");
        printf("Barrage Hit\n");
        randomize_barrage_location(game);
    }
}



void render_barrage(t_game *game)
{
	if (game->strike[2].is_launching)
		render_call_strike(game, game->strike[2].base_position);
		// render_call_barrage(game, game->strike[2].base_position);
	if (game->strike[2].is_active)
	{
		if (!game->strike[2].is_animating)
		{
			if (game->strike[2].delay_frames >= game->strike[2].delay_duration)
			{
				game->strike[2].is_animating = 1;
				game->strike[2].current_frame = 0;
				game->strike[2].frame_count = 0;
			}
			else
				game->strike[2].delay_frames++;
		}
		if (game->strike[2].is_animating)
			render_ongoing_barrage(game);
	}
}

