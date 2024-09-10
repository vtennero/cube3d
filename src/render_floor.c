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

void render_floor_rgb(t_img *img, int color) {
	int i, j;
	for (i = DEFAULT_S_HEIGHT / 2; i < DEFAULT_S_HEIGHT; ++i) {
		for (j = 0; j < DEFAULT_S_WIDTH; ++j) {
			img_pix_put(img, j, i, color);
		}
	}
}
