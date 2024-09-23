/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:30:53 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/23 18:33:34 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_ray_node	*add_ray(t_ray_node **head)
{
	t_ray_node	*new;

	new = ft_calloc(1, sizeof(t_ray_node));
	if (new == NULL)
	{
		printf("Error allocating memory for new node.\n");
		return (NULL);
	}
	if (*head == NULL)
	{
		new->next = NULL;
		*head = new;
	}
	else
	{
		new->next = *head;
		*head = new;
	}
	return (new);
}

t_ray_node	*calculate_rays(t_game *game, t_ray_node *list)
{
	int			x;
	t_ray_node	*current;
	t_ray_node	*center_ray;

	current = list;
	center_ray = NULL;
	x = 0;
	while (x < game->screen_width)
	{
		current = add_ray(&list);
		if (current != NULL)
		{
			current->ray.x = x;
			run_raycasting_calculations(game, current);
			if (x == game->screen_width / 2)
				center_ray = current;
		}
		x++;
	}
	if (center_ray != NULL)
		calculate_and_print_center_ray(game, center_ray);
	return (list);
}
