/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:16:37 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:16:42 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	render_floor_rgb(t_img *img, int color)
{
	int	i;
	int	j;

	i = DEFAULT_S_HEIGHT / 2;
	while (i < DEFAULT_S_HEIGHT)
	{
		j = 0;
		while (j < DEFAULT_S_WIDTH)
		{
			img_pix_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

