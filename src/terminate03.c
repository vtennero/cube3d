/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:21:05 by cliew             #+#    #+#             */
/*   Updated: 2024/08/27 15:28:23 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube3d.h"

// void free2DArray(Array2D *arr) {
//     if (arr == NULL || arr->array == NULL) {
//         return;  // Handle the case where the array or the structure is NULL
//     }

//     // Free each row
//     for (int i = 0; i < arr->rows; i++) {
//         free(arr->array[i]);
//     }

//     // Free the array of pointers
//     free(arr->array);
//     arr->array = NULL;  // Optional: Set the pointer to NULL to avoid dangling pointers
// }