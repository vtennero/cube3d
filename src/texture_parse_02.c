/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/07/12 21:01:14 by cliew             #+#    #+#             */
/*   Updated: 2024/08/26 20:19:01 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	handle_error(const char *message, int error_code)
{
	ft_printf(message);
	return (error_code);
}

void	texture_access_check(t_game *game, int *error)
{
	if (game->walltextures[0].path && access(game->walltextures[0].path,
			R_OK) != 0)
	{
		perror("Error\nFailed to parse North wall texture");
		*error = -1;
	}
	if (game->walltextures[1].path && access(game->walltextures[1].path,
			R_OK) != 0)
	{
		perror("Error\nFailed to parse East wall texture");
		*error = -1;
	}
	if (game->walltextures[2].path && access(game->walltextures[2].path,
			R_OK) != 0)
	{
		perror("Error\nFailed to parse South wall texture");
		*error = -1;
	}
	if (game->walltextures[3].path && access(game->walltextures[3].path,
			R_OK) != 0)
	{
		perror("Error\nFailed to parse West wall texture");
		*error = -1;
	}
}

int	texture_error_handling(t_game *game)
{
	int	error;

	error = 0;
	texture_access_check(game, &error);
	if (game->floor_rgb[0].path && check_invalid_rgb(game->floor_rgb[0].path))
	{
		ft_printf("Error\nFailed to parse Floor texture\n");
		error = -1;
	}
	if (game->sky_rgb[0].path && check_invalid_rgb(game->sky_rgb[0].path))
	{
		ft_printf("Error\nFailed to parse Sky texture\n");
		error = -1;
	}
	if ((game->walltextures[0].path) && (game->walltextures[1].path)
		&& (game->walltextures[2].path) && (game->walltextures[3].path)
		&& (game->floor_rgb[0].path) && (game->sky_rgb[0].path) && error == 0)
		return (0);
	else
		error = -1;
	return (error);
}

int	all_paths_set(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->walltextures[i].path == NULL)
		{
			return (0);
		}
		i++;
	}
	if (game->floor_rgb[0].path == NULL)
	{
		return (0);
	}
	if (game->sky_rgb[0].path == NULL)
	{
		return (0);
	}
	return (1);
}
