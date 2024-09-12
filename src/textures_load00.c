/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:29:32 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:29:32 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"



void update_progress_bar(int current, int total, const char *task_name)
{
    static int last_printed_length = 0;
    float progress = (float)current / total;
    int bar_width = (int)(progress * PROGRESS_BAR_WIDTH);

    // Move cursor to the beginning of the line
    printf("\r");

    // Clear the previous line
    for (int i = 0; i < last_printed_length; i++) {
        printf(" ");
    }
    printf("\r");

    // Construct the new progress bar
    int printed_length = 0;
    int task_name_length = strlen(task_name);

    // Truncate task name if it's too long
    if (task_name_length > MAX_TASK_NAME_LENGTH) {
        task_name_length = MAX_TASK_NAME_LENGTH;
    }

    // Print task name left-aligned in a field of TOTAL_PREFIX_LENGTH
    printed_length += printf("%-*.*s", TOTAL_PREFIX_LENGTH, task_name_length, task_name);

    printed_length += printf("[");
    for (int i = 0; i < PROGRESS_BAR_WIDTH; i++) {
        if (i < bar_width) printed_length += printf("#");
        else printed_length += printf(" ");
    }
    printed_length += printf("] %.1f%%", progress * 100.0f);

    // If completed, move to next line
    if (current == total) {
        printf("\n");
    }

    // Remember the length of the printed line for the next update
    last_printed_length = printed_length;
}

void load_wall_textures(t_game *game)
{
    int i = NORTH;
    int total_textures = WEST - NORTH + 1;

    while (i <= WEST)
    {
        game->walltextures[i].img = mlx_xpm_file_to_image(
                game->mlx_ptr,
                game->walltextures[i].path,
                &game->walltextures[i].width,
                &game->walltextures[i].height);
        if (!game->walltextures[i].img)
        {
            ft_putstr_fd("Failed to load wall texture: ", 2);
            ft_putendl_fd(game->walltextures[i].path, 2);
            exit(EXIT_FAILURE);
        }
        game->walltextures[i].data = mlx_get_data_addr(
                game->walltextures[i].img,
                &game->walltextures[i].tex_bpp,
                &game->walltextures[i].tex_line_len,
                &game->walltextures[i].tex_endian);

        update_progress_bar(i - NORTH + 1, total_textures, "Loading wall textures");
        i++;
    }
}


void	load_bonus_textures(t_game *game)
{
	load_floor_textures(game);
	load_collectible_texture(game, "textures/collectibles/collectible01.xpm");
	load_gun_textures(game);
	load_shooting_textures(game);
	load_enemy_textures(game, "textures/enemies/%03d.xpm", NUM_ENEMY_TEXTURES);
	load_menu_texture(game, "textures/menu/menu.xpm");
	load_opening_textures(game, "textures/jump/xpm/jump%03d.xpm", MAX_OPENING_TEXTURES);
	load_land_textures(game, "textures/land/land%03d.xpm", MAX_LAND_TEXTURES);
	load_outro_textures(game);
	load_extract_textures(game);
	load_napalm_textures(game);
	load_strike_textures(game);
	load_supplies_texture(game, "textures/supplies/supplies.xpm");
	load_pelican_inside_texture(game, "textures/extract/pelicaninside.xpm");
	scale_gun_textures(game);
	scale_shooting_textures(game);
}

void	load_textures(t_game *game)
{
	load_wall_textures(game);
	if (game->bonus == 1)
		load_bonus_textures(game);
}
