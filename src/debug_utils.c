/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:19:19 by root              #+#    #+#             */
/*   Updated: 2024/07/09 18:19:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	print_barrage_loc(t_vector2d new_position, t_vector2d base_position)
{
	printf("New barrage location: (%f, %f), Base position: (%f, %f)\n",
		new_position.x, new_position.y,
		base_position.x, base_position.y);
}
