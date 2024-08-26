/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:01:14 by cliew             #+#    #+#             */
/*   Updated: 2024/08/26 20:19:01 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int read_cub_texture_and_analyze_map(t_game *game)
{
	char *line;
	int map_start;

	map_start=0;
    game->cub_fd = open(game->cub_filepath, O_RDONLY);
    if (game->cub_fd  < 0) {
        perror("Error \nCould not open file");
        return -1;
    }
    while ((line = get_next_line(game->cub_fd )) != NULL) 
	{
		game->cub_line_count++;
		if (check_line(game,line)==-1)
			map_start=1;  // Break is needed here, to indicate end of the first 6 elements, else we wont know
		if (map_start==1)
		{
			if ((int)(ft_strlen(line)) > game->cub_map_col_count)
				game->cub_map_col_count =ft_strlen(line);
			game->cub_map_row_count++;
		}
        free(line);
    }
	printf("line is now:\n%s",line); /// This should be the first line of the map
	printf("\n");
	close(game->cub_fd);
    return 1;
}

void texture_access_check(t_game* game,int *error)
{
	if (game->walltextures[0].path && access(game->walltextures[0].path, R_OK) != 0)
	{
		perror("Error\nFailed to parse North wall texture");
		*error=-1;
	}
	if (game->walltextures[1].path && access(game->walltextures[1].path, R_OK) != 0)
	{
		perror("Error\nFailed to parse East wall texture");
		*error=-1;
	}
	if (game->walltextures[2].path && access(game->walltextures[2].path, R_OK) != 0){
		perror("Error\nFailed to parse South wall texture");
		*error=-1;
	}
	if (game->walltextures[3].path && access(game->walltextures[3].path, R_OK) != 0){
		perror("Error\nFailed to parse West wall texture");
		*error=-1;
	}

}

int texture_error_handling(t_game* game)
{
	int error;
	
	error = 0;

	texture_access_check(game,&error);
	if (game->floor_rgb[0].path && check_invalid_rgb(game->floor_rgb[0].path)){
		printf("Failed to parse Floor texture\n");
		error=-1;
	}
	if (game->sky_rgb[0].path && check_invalid_rgb(game->sky_rgb[0].path)){
		printf("Failed to parse Sky texture\n");
		error=-1;
	}
	if ((game->walltextures[0].path) && (game->walltextures[1].path) && (game->walltextures[2].path) && (game->walltextures[3].path) && (game->floor_rgb[0].path) && (game->sky_rgb[0].path) && error==0)
		return 0;
	else
		error=-1;
	return error;
}



int check_line(t_game *game, char* line)

{
 	char** words;
	int word_count;
	line=trim_whitespace(line);
	words = ft_split(line, ' ');
	word_count=count_words_from_array(words);
	printf("word count is %d !\n",word_count);
	printf("words[0] is %s!\n",words[0]);
	printf("words[1]] is %s!\n",words[1]);

	if (word_count>2 )  // Change to or?
		return -1;
	if (word_count<2)
		return 0;
	// To remove trailing new line
	if ((words[1]) && (strlen(words[1]) > 0) && (words[1][strlen(words[1]) -1] == '\n') )
		words[1][strlen(words[1])-1] = '\0';
	
	// Check if reach the line of 0,1 or 1,0, then return -1, indicates first 6 element end le
	if (
		((strcmp(words[0],"0")==0) || (strcmp(words[0],"1")==0)) &&
		((strcmp(words[1],"0")==0) || (strcmp(words[1],"1")==0)) 
	)
	{
	return -1;
	}
	
	if (strcmp(words[0],"NO")==0 )
		game->walltextures[0].path=words[1];
	else if (strcmp(words[0],"EA")==0 )
		game->walltextures[1].path=words[1];
	else if (strcmp(words[0],"SO")==0 )
		game->walltextures[2].path=words[1];
	else if (strcmp(words[0],"WE")==0 )
		game->walltextures[3].path=words[1];
	else if (strcmp(words[0],"F")==0 )
		game->floor_rgb[0].path=words[1];

	else if (strcmp(words[0],"C")==0 ){
		game->sky_rgb[0].path=words[1];
	}
	return 0;
	
}