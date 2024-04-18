/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:29:27 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/15 17:45:08 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static const t_keymap	g_keymap[] = {
{K_W, &handle_key_w},
{K_A, &handle_key_a},
{K_S, &handle_key_s},
{K_D, &handle_key_d},
{K_RIGHT, &handle_key_right},
{K_LEFT, &handle_key_left},
// {DOWN_ARROW_KEYCODE, &handle_down},
// {RIGHT_ARROW_KEYCODE, &handle_right},
// {LEFT_ARROW_KEYCODE, &handle_left},
// {ESC_ARROW_KEYCODE, &handle_esc},
{0, NULL}
};

const char* get_cardinal_direction(float x, float y) {
    float angle = atan2(y, x); // Get angle in radians from x-axis
    if (angle < 0) {
        angle += 2 * M_PI; // Normalize angle to be between 0 and 2*pi
    }

    // Define angle thresholds for cardinal directions
    const float pi_8 = M_PI / 8; // Pi divided by 8 (22.5 degrees in radians)
    if (angle < pi_8 || angle > 15 * pi_8) return "East";
    else if (angle < 3 * pi_8) return "North-East";
    else if (angle < 5 * pi_8) return "North";
    else if (angle < 7 * pi_8) return "North-West";
    else if (angle < 9 * pi_8) return "West";
    else if (angle < 11 * pi_8) return "South-West";
    else if (angle < 13 * pi_8) return "South";
    else return "South-East";
}

void handle_key_left(t_game *game)
{
    // Implement what happens when 'Left' is pressed
    printf("You just pressed Left!\n");

    float angle = 0.0872665;  // 5 degrees in radians
    float oldX = game->player->direction.x;
    float oldY = game->player->direction.y;

    game->player->direction.x = oldX * cos(angle) - oldY * sin(angle);
    game->player->direction.y = oldX * sin(angle) + oldY * cos(angle);
    
    printf("New direction.x = %f, New direction.y = %f\n", game->player->direction.x, game->player->direction.y);
    const char *direction = get_cardinal_direction(game->player->direction.x, game->player->direction.y);
    printf("Facing direction: %s\n", direction);
}


void handle_key_right(t_game *game)
{
    // Implement what happens when 'Right' is pressed
    printf("You just pressed Right!\n");

    float angle = 0.0872665;  // 5 degrees in radians
    float oldX = game->player->direction.x;
    float oldY = game->player->direction.y;

    game->player->direction.x = oldX * cos(angle) + oldY * sin(angle);
    game->player->direction.y = oldY * cos(angle) - oldX * sin(angle);
    
    printf("New direction.x = %f, New direction.y = %f\n", game->player->direction.x, game->player->direction.y);
        const char *direction = get_cardinal_direction(game->player->direction.x, game->player->direction.y);
    printf("Facing direction: %s\n", direction);
}

void handle_key_w(t_game *game)
{
    printf("You just pressed W!\n");

    float speed = 0.8;  // Speed of movement, adjust as necessary
    float buffer = 0.8; // Buffer distance to prevent entering into a wall
    float newX = game->player->position.x + game->player->direction.x * speed;
    float newY = game->player->position.y + game->player->direction.y * speed;

    // Check collision using the buffer for more predictive collision detection
    int mapX = (int)(newX + game->player->direction.x * buffer);
    int mapY = (int)(newY + game->player->direction.y * buffer);

    // Ensure within map bounds and not a wall tile
    if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL) {
        game->player->position.x = newX;
        game->player->position.y = newY;
        printf("New player position: x = %f, y = %f\n", game->player->position.x, game->player->position.y);
    } else {
        printf("Collision detected! Close to a wall.\n");
    }
    print_game_map(game);
}


// void handle_key_a(t_game *game)
// {
//     // Implement what happens when 'A' is pressed
//     printf("You just pressed A!\n");

//     float speed = 0.8;  // Speed of movement, adjust as necessary
//     float buffer = 0.8; // Buffer distance to prevent entering into a wall
//     // Calculate left strafe direction
//     float newX = game->player->position.x - game->player->direction.y * speed;
//     float newY = game->player->position.y + game->player->direction.x * speed;
//     int mapX = (int)newX;
//     int mapY = (int)newY;

//     // Check collision using the buffer for more predictive collision detection
//     int mapX = (int)(newX + game->player->direction.x * buffer);
//     int mapY = (int)(newY + game->player->direction.y * buffer);

//     // Check if the new position is within the bounds of the map and not a wall
//     if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL) {
//         game->player->position.x = newX;
//         game->player->position.y = newY;
//         printf("game->player->position.x = %f\n", game->player->position.x);
//         printf("game->player->position.y = %f\n", game->player->position.y);
//     }
//     else
//         printf("Collision/Out of Map movement\n");
// }


// void handle_key_s(t_game *game)
// {
//     // Implement what happens when 'S' is pressed
//     printf("You just pressed S!\n");

//     float speed = 0.8;  // Speed of movement, adjust as necessary
//     float buffer = 0.8; // Buffer distance to prevent entering into a wall
//     float newX = game->player->position.x - game->player->direction.x * speed;
//     float newY = game->player->position.y - game->player->direction.y * speed;
//     int mapX = (int)newX;
//     int mapY = (int)newY;

//     // Check collision using the buffer for more predictive collision detection


//     if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL) {
//         game->player->position.x = newX;
//         game->player->position.y = newY;
//         printf("game->player->position.x = %f\n", game->player->position.x);
//         printf("game->player->position.y = %f\n", game->player->position.y);
//     }
//     else
//         printf("Collision/Out of Map movement\n");
// }

void handle_key_s(t_game *game)
{
    printf("You just pressed S!\n");

    float speed = 0.8;  // Speed of movement, adjust as necessary
    float buffer = 0.8; // Buffer distance to prevent entering into a wall
    float newX = game->player->position.x - game->player->direction.x * (speed + buffer);
    float newY = game->player->position.y - game->player->direction.y * (speed + buffer);
    int mapX = (int)(newX);
    int mapY = (int)(newY);

    // Check collision with buffered coordinates
    if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL) {
        game->player->position.x = newX + game->player->direction.x * buffer; // Revert buffer
        game->player->position.y = newY + game->player->direction.y * buffer; // Revert buffer
        printf("game->player->position.x = %f\n", game->player->position.x);
        printf("game->player->position.y = %f\n", game->player->position.y);
    } else {
        printf("Collision/Out of Map movement\n");
    }
    print_game_map(game);
}


// void handle_key_d(t_game *game)
// {
//     // Implement what happens when 'D' is pressed
//     (void)game;
//     printf("You just pressed D!\n");

//     float speed = 0.8;  // Speed of movement, adjust as necessary
//     float buffer = 0.8; // Buffer distance to prevent entering into a wall
//     float newX = game->player->position.x + game->player->direction.y * speed;
//     float newY = game->player->position.y - game->player->direction.x * speed;
//     int mapX = (int)newX;
//     int mapY = (int)newY;



//     if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL) {
//         game->player->position.x = newX;
//         game->player->position.y = newY;
//         printf("game->player->position.x = %f\n", game->player->position.x);
//         printf("game->player->position.y = %f\n", game->player->position.y);
//     }
//     else
//         printf("Collision/Out of Map movement\n");
// }


float calculate_dynamic_buffer(t_player *player, float base_speed) {
    // Calculate buffer based on the dot product of direction and plane vectors
    float dir_mag = sqrt(player->direction.x * player->direction.x + player->direction.y * player->direction.y);
    float plane_mag = sqrt(player->plane.x * player->plane.x + player->plane.y * player->plane.y);
    float dot_product = player->direction.x * player->plane.x + player->direction.y * player->plane.y;
    
    float cosine_angle = dot_product / (dir_mag * plane_mag);
    float dynamic_buffer = base_speed * (1 - fabs(cosine_angle)); // Reduce buffer as angle approaches 90 degrees
    printf("dynamic buffer %f\n", dynamic_buffer);
    return dynamic_buffer;
}

void handle_key_a(t_game *game)
{
    printf("You just pressed A!\n");

    float speed = 0.8;
    float buffer = 10;
    // float buffer = calculate_dynamic_buffer(game->player, speed);

    float newX = game->player->position.x - game->player->plane.x * (speed + buffer); // Left perpendicular to direction
    float newY = game->player->position.y - game->player->plane.y * (speed + buffer);
    int mapX = (int)(newX);
    int mapY = (int)(newY);

    if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL) {
        game->player->position.x = newX + game->player->plane.x * buffer;
        game->player->position.y = newY + game->player->plane.y * buffer;
        printf("game->player->position.x = %f\n", game->player->position.x);
        printf("game->player->position.y = %f\n", game->player->position.y);
    } else {
        printf("Collision/Out of Map movement\n");
    }
    print_game_map(game);
}

void handle_key_d(t_game *game)
{
    printf("You just pressed D!\n");

    float speed = 0.8;
    float buffer = 5;
    float newX = game->player->position.x + game->player->plane.x * (speed + buffer); // Right perpendicular to direction
    float newY = game->player->position.y + game->player->plane.y * (speed + buffer);
    int mapX = (int)(newX);
    int mapY = (int)(newY);

    if (mapX >= 0 && mapX < game->map->width && mapY >= 0 && mapY < game->map->height && game->map->data[mapY][mapX] != TILE_WALL) {
        game->player->position.x = newX - game->player->plane.x * buffer;
        game->player->position.y = newY - game->player->plane.y * buffer;
        printf("game->player->position.x = %f\n", game->player->position.x);
        printf("game->player->position.y = %f\n", game->player->position.y);
    } else {
        printf("Collision/Out of Map movement\n");
    }
    print_game_map(game);
}



// int key_hook(int keycode, t_game *game)
// {
// 	// printf("Hello from key_hook! %d\n", keycode);
// 	(void)game;
//     if (keycode == K_W) {
//         handle_key_w(game);
//     } else if (keycode == K_A) {
//         handle_key_a(game);
//     } else if (keycode == K_S) {
//         handle_key_s(game);
//     } else if (keycode == K_D) {
//         handle_key_d(game);
//     }
//     return 0;
// }

int	handle_key(int keycode, t_game *game_state)
{
	int	i;

	i = 0;
	while (g_keymap[i].func != NULL)
	{
		if (g_keymap[i].keycode == keycode)
		{
			g_keymap[i].func(game_state);
			break ;
		}
		i++;
	}
	// event_handler(game_state);
	mlx_clear_window(game_state->mlx_ptr, game_state->win_ptr);
	refresh_screen(game_state);
	// display_map(game_state->mlx_ptr, game_state->win_ptr, game_state);
	return (0);
}

int	close_hook(t_game *game_state)
{
	ft_printf("Close button clicked, exiting...\n");
	// clear_mlx_resources(game_state);
	// clear_game_state(game_state);
	(void)game_state;
	exit(0);
	return (0);
}

void set_up_hooks(t_game *game)
{
	// // so long
	// mlx_key_hook(game_state->win_ptr, handle_key, game_state);
	// mlx_hook(game_state->win_ptr, 17, 0, close_hook, game_state);

	// // working v1
	// mlx_key_hook(game->win_ptr, key_hook, game);

	// v2
	mlx_key_hook(game->win_ptr, handle_key, game);
	mlx_hook(game->win_ptr, 17, 0, close_hook, game);
}



