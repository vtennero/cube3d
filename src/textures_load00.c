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

// void	update_progress_bar(int current, int total, const char *task_name)
// {
// 	static int	last_printed_length = 0;
// 	float		progress;
// 	int			bar_width;
// 	int			printed_length;
// 	int			task_name_length;

// 	progress = (float)current / total;
// 	bar_width = (int)(progress * PROGRESS_BAR_WIDTH);
// 	printf("\r");
// 	for (int i = 0; i < last_printed_length; i++)
// 		printf(" ");
// 	printf("\r");
// 	printed_length = 0;
// 	task_name_length = strlen(task_name);
// 	if (task_name_length > MAX_TASK_NAME_LENGTH)
// 		task_name_length = MAX_TASK_NAME_LENGTH;
// 	printed_length += printf("%-*.*s", TOTAL_PREFIX_LENGTH, task_name_length, task_name);
// 	printed_length += printf("[");
// 	for (int i = 0; i < PROGRESS_BAR_WIDTH; i++)
// 	{
// 		if (i < bar_width)
// 			printed_length += printf("#");
// 		else
// 			printed_length += printf(" ");
// 	}
// 	printed_length += printf("] %.1f%%", progress * 100.0f);
// 	if (current == total)
// 		printf("\n");
// 	last_printed_length = printed_length;
// }

void	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(
		game->mlx_ptr, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		ft_putstr_fd("Failed to load texture: ", 2);
		ft_putendl_fd(path, 2);
		exit(EXIT_FAILURE);
	}
	texture->data = mlx_get_data_addr(texture->img,
			&texture->tex_bpp, &texture->tex_line_len, &texture->tex_endian);
}


void	load_wall_textures(t_game *game)
{
	int	i;
	int	total_textures;

	i = NORTH;
	total_textures = WEST - NORTH + 1;
	while (i <= WEST)
	{
		load_texture(game, &game->walltextures[i], game->walltextures[i].path);
		update_progress_bar(game, i - NORTH + 1, total_textures, "Loading wall textures");
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
