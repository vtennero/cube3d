/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   napalm_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:07:16 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 16:32:02 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// #define NAPALM_WIDTH_FACTOR 0.1 // Adjust this value to change the overall width scaling
// #define NAPALM_SHAKE_DURATION 30 // Number of frames the shake effect lasts
// #define NAPALM_SHAKE_INTENSITY 0.3f // Maximum shake offset
// #define NAPALM_BASE_PLAYER_HEIGHT 0.2f // Base player height
// #define NUM_NAPALM_OFFSETS 36

// float calculate_napalm_screen_shake(t_game *game, int current_frame)
// {
//     if (current_frame >= NAPALM_SHAKE_DURATION)
//         return 0.0f;

//     float random_offset = (float)random_int(game, 1000) / 1000.0f;
//     float intensity = NAPALM_SHAKE_INTENSITY * (1.0f - (float)current_frame / NAPALM_SHAKE_DURATION);
//     float shake = sinf(current_frame * 0.5f) * intensity;
//     return shake * random_offset;
// }

// void draw_napalm_stripe(t_game *game, int stripe, int drawStartY, int drawEndY, float distance)
// {
//     int total_width = (int)(NAPALM_WIDTH_FACTOR * game->screen_width / distance);
//     total_width = (total_width < 3) ? 3 : total_width;

//     int orange_width = total_width / 2;

//     for (int y = 0; y < drawEndY; y++)
//     {
//         for (int i = -total_width/2; i < total_width/2; i++)
//         {
//             int x = stripe + i;
//             if (x >= 0 && x < game->screen_width)
//             {
//                 int color;
//                 if (i >= -orange_width/2 && i < orange_width/2)
//                 {
//                     color = 0xFFA500; // Orange in the middle
//                 }
//                 else
//                 {
//                     float gradient = 1.0f - (float)abs(i) / (total_width/2);
//                     int red_value = 128 + (int)(127 * gradient);
//                     int green_value = 64 + (int)(63 * gradient);
//                     color = (red_value << 16) | (green_value << 8); // Red and green channels for fire effect
//                 }
//                 img_pix_put(&game->img, x, y, color);
//             }
//         }
//     }
// }

// void render_call_napalm(t_game *game, t_vector2d position)
// {
//     float spriteX, spriteY;
//     calculate_sprite_position(game, position.x, position.y, &spriteX, &spriteY);

//     float transformX, transformY;
//     transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

//     int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

//     int spriteHeight, drawStartY, drawEndY;
//     calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

//     float dx = position.x - game->player->position.x;
//     float dy = position.y - game->player->position.y;
//     float distance = sqrt(dx * dx + dy * dy);

//     int stripe = spriteScreenX;
//     if (is_sprite_in_front(transformY, stripe, game->screen_width))
//     {
//         draw_napalm_stripe(game, stripe, drawStartY, drawEndY, distance);
//     }
// }

// int get_next_napalm_frame(t_strike *strike)
// {
//     strike[1].frame_count++;

//     if (strike[1].frame_count % AIRSTRIKE_ANIMATION_INTERVAL != 0)
//         return strike[1].current_frame;

//     strike[1].current_frame = (strike[1].current_frame + 1) % NUM_AIRSTRIKE_FRAMES;

//     if (strike[1].current_frame == 0)
//     {
//         strike[1].is_active = 0;
//         strike[1].is_launching = 0;
//     }

//     return strike[1].current_frame;
// }

// void render_ongoing_napalm(t_game *game)
// {
//     if (!game->strike[1].is_active)
//         return;

//     int current_frame = get_next_napalm_frame(game->strike);
//     t_texture *napalm_texture = &game->airstrike_textures[current_frame];

//     float shake_offset = calculate_napalm_screen_shake(game, current_frame);

//     if (game->player->is_dead == 0)
//         game->player->height = NAPALM_BASE_PLAYER_HEIGHT + shake_offset;

//     int offsets[NUM_NAPALM_OFFSETS][2] = {
//         {0, 0},
//         {1, 0}, {-1, 0}, {0, 1}, {0, -1},
//         {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
//         {2, 0}, {-2, 0}, {0, 2}, {0, -2},
//         {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
//         {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
//         {3, 0}, {-3, 0}, {0, 3}, {0, -3},
//         {3, 1}, {3, -1}, {-3, 1}, {-3, -1},
//         {1, 3}, {1, -3}, {-1, 3}, {-1, -3},
//         {4, 0}, {-4, 0}, {0, 4}, {0, -4}
//     };

//     for (int i = 0; i < NUM_NAPALM_OFFSETS; i++)
//     {
//         float spriteX, spriteY;
//         calculate_sprite_position(game,
//                                   game->strike[1].position.x + offsets[i][0],
//                                   game->strike[1].position.y + offsets[i][1],
//                                   &spriteX, &spriteY);

//         float transformX, transformY;
//         transform_sprite(game, spriteX, spriteY, &transformX, &transformY);

//         int spriteScreenX = calculate_sprite_screen_x(game, transformX, transformY);

//         int spriteHeight, drawStartY, drawEndY;
//         calculate_sprite_height(game, transformY, &spriteHeight, &drawStartY, &drawEndY);

//         int spriteWidth, drawStartX, drawEndX;
//         calculate_sprite_width(game, transformY, spriteScreenX, &spriteWidth, &drawStartX, &drawEndX);

//         for (int stripe = drawStartX; stripe < drawEndX; stripe++)
//         {
//             if (is_sprite_in_front(transformY, stripe, game->screen_width))
//             {
//                 draw_sprite_stripe(game, napalm_texture, stripe, drawStartY, drawEndY, spriteHeight, spriteWidth, spriteScreenX, transformY);
//             }
//         }
//     }
// }

// void render_napalm(t_game *game)
// {
//     if (game->strike[1].is_launching)
//         render_call_napalm(game, game->strike[1].position);
//     else if (game->strike[1].is_active)
//         render_ongoing_napalm(game);
// }
