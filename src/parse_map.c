/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 12:42:15 by cliew             #+#    #+#             */
/*   Updated: 2024/08/27 15:17:58 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"



	int parse_line_to_map_array(char* line, t_game *game,int map_line)
	{	
		int j;
		int i;

		i=0;
		j=0;
		printf("%s\n", line);

		while (line[i] != '\0') 
		{
			if (i % 2 == 0  && i<= game->cub_map_col_count)
			{
				// printf("i is %d \n",i);
				// printf("j is %d \n",j);
				// printf("%c\n",line[i]);
				game->cub_map_array[map_line][j] = parse_char_to_int(line[i]);
				j++;
			}
			i++;
			}
		// To parse empty space after \0
		while (i <= game->cub_map_col_count) {
    	if (i % 2 == 0) {
        	game->cub_map_array[map_line][j] = 9;
        	j++;
    		}
    	i++;
		}
	return 1;

	}


	int loop_thru_line_in_map_array(t_game *game)
	{		
		int fd;
		int line_count;
		int map_line;
		char* line;

		map_line=0;
		line_count=0; 
		fd = open(game->cub_filepath, O_RDONLY);

	
    	if (fd  < 0) {
        	perror("Error \nCould not open file");
        	return -1;
    	}
    	while ((line = get_next_line(fd)) != NULL) 
		{
			if ((line_count>=game->cub_line_count-game->cub_map_row_count) && (map_line<=game->cub_map_row_count))
			{
				// printf("line count: %d,game->cub_line_count:%d,game->cub_map_row_count:%d,map_line is %d,game->cub_map_row_count is %d",line_count,game->cub_line_count,game->cub_map_row_count,map_line,game->cub_map_row_count);
				// printf("line of map is now:\n%s",line); /// This should be the first line of the map
				parse_line_to_map_array(line,game,map_line);
				map_line++;

			}
			line_count++;
			free(line);
		}
		return 1;
	}

	int check_player_position_helper(t_game *game,int i,int j,int *player_found)
	{	
		
		// printf("OUTSIDE i is %d and j is %d  and player_found = %d \n",i,j,*player_found);

		if (game->cub_map_array[i][j]==2 || game->cub_map_array[i][j]==3 || game->cub_map_array[i][j]==4 || game->cub_map_array[i][j]==5 )
			{
				if (*player_found==0)
					{						
						*player_found=1;
						game->cub_player_x=i;
						game->cub_player_y=j;
						game->cub_player_o=game->cub_map_array[i][j];
						printf("i is %d and j is %d  and player_found = %d \n",i,j,*player_found);

					}
				else
						return -1;
				}
		return 1;
	}
				


	int check_player_postion_and_map_char(t_game *game)
	{
		int i;
		int j;
		int player_found=0;

		i=0;
		j=0;
		player_found=0;
		while (i < game->cub_map_row_count)
		{
					// printf("OUTSIDE i is %d and j is %d  and player_found = %d \n",i,j,*player_found);

			while (j < (game->cub_map_col_count+1)/2)
			{
				// printf("\n%d,%d,%d",i,j,game->cub_map_array[i][j]);
				if (check_player_position_helper(game,i,j,&player_found)==-1)
					return -1; 
				if (game->cub_map_array[i][j] ==-1)
					return -2;
				j++;
			}
			j=0;
			i++;
		}

		if (player_found==0)
			return 0;
		return 1;
	}


	int parse_map_to_array(t_game *game)

	{       
		int check_status;
		game->cub_map_array=initializeArray(game->cub_map_row_count, (game->cub_map_col_count + 1) / 2); 
		// initializeArray(game,game->cub_map_row_count, (game->cub_map_col_count + 1) / 2); 
		print_2d_array(game,game->cub_map_array);
		loop_thru_line_in_map_array(game);
		print_2d_array(game,game->cub_map_array);
		check_status=check_player_postion_and_map_char(game);
		if (check_status!=1)
		{
			if (check_status==0)
				printf("No player postion is detected!");
			if (check_status==-1)
				printf("2 Player postion detected!");
			if (check_status==-2)
				printf("Invalid character in map detected!");
			return -1;
		}
		printf("player position is %d,%d and the orientation is %d\n",game->cub_player_x,game->cub_player_y,game->cub_player_o);
	
		return 1;
	}

	
