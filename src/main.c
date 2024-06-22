/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:55:31 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/17 17:35:54 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

unsigned int *texture[10];  // Array of pointers for 10 textures

// unsigned int texture[10][64 * 64];  // Example texture array for 10 textures, each 64x64 pixels
unsigned int buffer[DEFAULT_S_HEIGHT][DEFAULT_S_WIDTH];  // Screen buffer for the pixels
void    *mlx;
void    *win;

unsigned int *load_texture(char *file, int *width, int *height) {
    void *img;
    int bpp, sl, endian;
    unsigned int *data;

    img = mlx_xpm_file_to_image(mlx, file, width, height);
    if (!img) {
        fprintf(stderr, "Error loading %s\n", file);
        exit(1);
    }
    data = (unsigned int *)mlx_get_data_addr(img, &bpp, &sl, &endian);
    // Optionally, you can copy the data to a new buffer if you need to manage multiple textures.
    return data;
}

int charToEnum(char c)
{
    if (c == '0')
        return Empty;
    else if (c == '1')
        return Wall;
    else if (c == 'N')
        return PlayerN;
    else if (c == 'S')
        return PlayerS;
    else if (c == 'E')
        return PlayerE;
    else if (c == 'W')
        return PlayerW;
    else
        return Empty;  // Default case to handle unexpected characters or treat them as empty spaces
}

// void create_static_map(t_game *game, int screenWidth, int screenHeight)
// {
//     // Allocate memory for the map structure
//     t_map *map = malloc(sizeof(t_map));
//     if (map == NULL) {
//         fprintf(stderr, "Memory allocation failed for map structure.\n");
//         exit(1);
//     }
//     printf("Allocated memory for the map structure\n");
//     // Set the dimensions
//     map->width = screenWidth;
//     map->height = screenHeight;
//     printf("Set the dimensions\n");

//     // Allocate memory for the map data
//     map->data = malloc(screenHeight * sizeof(int *));
//     if (map->data == NULL) {
//         fprintf(stderr, "Memory allocation failed for map data.\n");
//         free(map); // Clean up previously allocated map
//         exit(1);
//     }
//     printf("Allocated memory for the map data\n");

//     for (int i = 0; i < screenHeight; i++) {
//         map->data[i] = malloc(screenWidth * sizeof(int));
//         if (map->data[i] == NULL) {
//             fprintf(stderr, "Memory allocation failed for map row.\n");
//             // Clean up previously allocated rows and map structure
//             for (int j = 0; j < i; j++) {
//                 free(map->data[j]);
//             }
//             free(map->data);
//             free(map);
//             exit(1);
//         }
//     }
    
//     // Static map data to copy into the newly allocated map
//     int staticMap[24][24] = {
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };
// // 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// // 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
// // 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
// // 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// // };
//     printf("defined static map data\n");

//     // Copy the static map to the allocated map
//     for (int y = 0; y < 24; y++)
//     {
//         // printf("for (int y = %d; y < screenHeight; y++)\n", y);
//         for (int x = 0; x < 24; x++) {
//             // printf("for int x = %d; x < screenWidth; x++\n", x);
//             map->data[y][x] = staticMap[y][x];
//         }
//     }
//     printf("copied the static map to the allocated map\n");

//     // Link the map to the game structure
//     game->map = map;
// }



void create_map_from_cub(t_game *game, int screenWidth, int screenHeight)
{
	
    // Allocate memory for the map structure
    t_map *map = malloc(sizeof(t_map));
    if (map == NULL) {
        fprintf(stderr, "Memory allocation failed for map structure.\n");
        exit(1);
    }
    printf("Allocated memory for the map structure\n");
    // Set the dimensions
    map->width = screenWidth;
    map->height = screenHeight;
    printf("Set the dimensions\n");

    // Allocate memory for the map data
    map->data = malloc(screenHeight * sizeof(int *));
    if (map->data == NULL) {
        fprintf(stderr, "Memory allocation failed for map data.\n");
        free(map); // Clean up previously allocated map
        exit(1);
    }
    printf("Allocated memory for the map data\n");

    for (int i = 0; i < screenHeight; i++) {
        map->data[i] = malloc(screenWidth * sizeof(int));
        if (map->data[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for map row.\n");
            // Clean up previously allocated rows and map structure
            for (int j = 0; j < i; j++) {
                free(map->data[j]);
            }
            free(map->data);
            free(map);
            exit(1);
        }
    }
    
    // Static map data to copy into the newly allocated map
    int staticMap[24][24] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

    printf("defined static map data\n");

    // Copy the static map to the allocated map
    for (int y = 0; y < 24; y++)
    {
        // printf("for (int y = %d; y < screenHeight; y++)\n", y);
        for (int x = 0; x < 24; x++) {
            // printf("for int x = %d; x < screenWidth; x++\n", x);
            map->data[y][x] = staticMap[y][x];
        }
    }
    printf("copied the static map to the allocated map\n");

    // Link the map to the game structure
    game->map = map;
}

// int     render_game(t_game *game)
// {
//     // set_up_display(game);

// }

int     map_is_valid()
{
    return (1);
}

int create_game_struct(t_game **game) {
    *game = calloc(1, sizeof(t_game));
    if (*game == NULL)
        return -1;
    (*game)->screen_height = DEFAULT_S_HEIGHT;
    (*game)->screen_width = DEFAULT_S_WIDTH;
	(*game)->cub_line_count = 0;

	// for (int i = 0; i < 4; i++) {
    //     // Assuming you have a valid way to initialize your walltextures
    //     // (*game)->walltextures[i] = initialize_texture(); 
    //     // For now, let's just set them to NULL or some default value
    //     // (*game)->walltextures[i] = (t_texture){0}; // Assuming t_texture can be zero-initialized
    //     printf("index is %d and value is %s\n", i, ((*game)->walltextures[i]).path);
    // }
    return 0;
}

char* trim_whitespace(char* str) {
    char* end;

    // Trim leading space by moving the str pointer to the first non-whitespace character
    while (ft_isspace((unsigned char)*str)) str++;

    if (*str == 0)  // All spaces, return an empty string
        return str;

    // Find the end of the string
    end = str + ft_strlen(str) - 1;

    // Move backwards from the end, skipping whitespace characters
    while (end > str && ft_isspace((unsigned char)*end)) {
        end--;
    }

    // Set the new null terminator character after the last non-whitespace character
    end[1] = '\0';

    return str;
}
int count_words_from_array(char **words) {
    int count = 0;
    while (words[count] != NULL) {
        count++;
    }
    return count;
}


int check_valid_rgb(char* word)
{
	char ** words;
	int count;
	int value;

	count=0;
	words=ft_split(word, ',');
    while (words[count] != NULL) {
		value=ft_atoi(words[count]);
		if ((value <0) || (value > 255))
			return 1;
        count++;
    }
	if (count!=3)
		return 1;
	return 0;
}

///// Check only, we want to try to do assign
int check_line(t_game *game, char* line,int (*man_info)[6])
{
 	char** words;
	int word_count;
	line=trim_whitespace(line);
	words = ft_split(line, ' ');
	word_count=count_words_from_array(words);
	printf("word count is %d !\n",word_count);
	printf("words[0] is %s!\n",words[0]);
	printf("words[1]] is %s!\n",words[1]);
	// printf("Access to sky02.xpm is %d",access("textures/sky02.xpm", R_OK));
	// printf("Access to words[1] is %d",access(words[1], R_OK));

	// if (word_count!=2 && ft_strcmp(words[0],"\n"))  // Change to or?
	// 	return -1;
	if (word_count>2 )  // Change to or?
		return -1;
	if (word_count<2)
		return 0;
    // ensure_null_terminated(str1, sizeof(str1));

	// To remove trailing new line
	// printf("%ld",ft_strlen(words[1]));
	// printf("%d",words[1][ft_strlen(words[1]) -1]);
	if ((words[1]) && (strlen(words[1]) > 0) && (words[1][strlen(words[1]) -1] == '\n') )
		words[1][strlen(words[1])-1] = '\0';
	if (strcmp(words[0],"NO")==0 && (access(words[1], R_OK) == 0)){
		game->walltextures[0].path=words[1];
		(*man_info[0])=1;
	}
	else if (strcmp(words[0],"EA")==0 && (access(words[1], R_OK) == 0)){
		game->walltextures[1].path=words[1];
		(*man_info)[1]=1;
	}
	else if (strcmp(words[0],"SO")==0 && (access(words[1], R_OK) == 0)){
		game->walltextures[2].path=words[1];
		(*man_info)[2]=1;
	}
	else if (strcmp(words[0],"WE")==0 && (access(words[1], R_OK) == 0)){
		game->walltextures[3].path=words[1];
		(*man_info)[3]=1;
	}
	else if (strcmp(words[0],"F")==0 && (check_valid_rgb(words[1]) == 0)){
		game->floortexture[0].path=words[1];
		(*man_info)[4]=1;
	}	
	else if (strcmp(words[0],"C")==0 &&  (check_valid_rgb(words[1]) == 0)){
		game->skytexture[0].path=words[1];
		(*man_info)[5]=1;
	}
	return 0;
	
}




char *strjoin_odd(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    char *result = (char *)malloc(len + 1); // Allocate memory for the result
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }
    
    size_t i = 0;
    size_t result_index = 0;
    while (i < len) {
        if ((i % 2 == 0) ) { // Include spaces as well
            result[result_index++] = str[i];
        }
        i++;
    }
    result[result_index] = '\0'; // Null-terminate the result string
    
    return result;
}

// int parse_map(char*line,int fd, t_game *game)
// {
// 	char *new_line;
// 	char *parsed_line;
// 	char *combined_line;
// 	(void)game;

// 	if (strchr(line, '1') != NULL)
// 		parsed_line=strjoin_odd(new_line);
// 		combined_line=parsed_line;
// 		free(parsed_line);
// 	else {
// 		printf("hello");
// 		combined_line=" ds";
// 	}

// 	while ((new_line = get_next_line(fd)) != NULL)
// 	{
// 		parsed_line=strjoin_odd(new_line);
// 		combined_line=ft_strjoin;

// 		printf("parsed_line is %s\n",parsed_line);
// 	}
// 	return 0;
// }

// int parse_map(char*line,int fd, t_game *game)
// {
	
// 	return 0;
// }

// int parse_map_size()
// int read_cub(t_game *game)
// {
// 	int fd1;
// 	int fd;
// 	char *line;
// 	int man_info[6];

// 	// Initialize the array to 0 using ft_memset
//     ft_memset(man_info, 0, 6 * sizeof(int));
	
//     // Print the array to verify
//     // printf("Array after initialization:\n");
//     // for (int i = 0; i < 6; i++) {
//     //     printf("%d ", man_info[i]);
//     // }
//     // printf("\n");

//     fd = open(game->cub_filepath, O_RDONLY);
//     if (fd < 0) {
//         perror("Could not open file");
//         return -1;
//     }


//     while ((line = get_next_line(fd)) != NULL) 
// 	{
	
// 		if (check_line(line,&man_info)==-1)
// 			break;  // Break is needed here, to indicate end of the first 6 elements, else we wont know
//         // printf("words count = %d\n", words);
//         free(line);
//     }
	
// 		//Print the array to verify
// 	printf("Array after initialization:\n");
// 	for (int i = 0; i < 6; i++) {
// 		printf("%d ", man_info[i]);
// 	}

// 	/////// GET CUB_LINE_COUNT
// 	// fd1 = open(game->cub_filepath, O_RDONLY);
//     // if (fd1 < 0) {
//     //     perror("Could not open file");
//     //     return -1;
//     // }
// 	// while ((line = get_next_line(fd1)) != NULL) 
// 	// {
// 	// 	game->cub_line_count++;
//     //     free(line);
// 	// 	close(fd1);
// 	// }
// 	// printf("cub_line count is %d",game->cub_line_count);

	
// 	printf("\n");
//     // Start parsing map
// 	// parse_map(line,fd,game);
	
// 	close(fd);
//     return 0;

// }


char* read_cub_texture(t_game *game)
{
	// int fd1;
	// int fd;
	char *line;
	int man_info[6];

	// Initialize the array to 0 using ft_memset
    ft_memset(man_info, 0, 6 * sizeof(int));
	
    game->cub_fd = open(game->cub_filepath, O_RDONLY);
    if (game->cub_fd  < 0) {
        perror("Could not open file");
        return NULL;
    }


    while ((line = get_next_line(game->cub_fd )) != NULL) 
	{
	
		if (check_line(game,line,&man_info)==-1)
			break;  // Break is needed here, to indicate end of the first 6 elements, else we wont know
        // printf("words count = %d\n", words);
        free(line);
    }
	
	//Print the array to verify
	printf("Array after initialization:\n");
	for (int i = 0; i < 6; i++) {
		printf("%d ", man_info[i]);
	}
	printf("line is now:\n%s",line); /// This should be the first line of the map

	
	/////// GET CUB_LINE_COUNT
	// fd1 = open(game->cub_filepath, O_RDONLY);
    // if (fd1 < 0) {
    //     perror("Could not open file");
    //     return -1;
    // }
	// while ((line = get_next_line(fd1)) != NULL) 
	// {
	// 	game->cub_line_count++;
    //     free(line);
	// 	close(fd1);
	// }
	// printf("cub_line count is %d",game->cub_line_count);

	
	printf("\n");
    // Start parsing map
	// parse_map(line,fd,game);
	
	// close(fd);
    return line;

}

int texture_error_handling(t_game* game)
{
	if (!game->walltextures[0].path)
		perror("Failed to parse North wall texture");
	if (!game->walltextures[1].path)
		perror("Failed to parse East wall texture");
	if (!game->walltextures[2].path)
		perror("Failed to parse South wall texture");
	if (!game->walltextures[3].path)
		perror("Failed to parse West wall texture");
	if (!game->floortexture[0].path)
		perror("Failed to parse Floor texture");
	if (!game->skytexture[0].path)
		perror("Failed to parse Sky texture");
	if ((game->walltextures[0].path) && (game->walltextures[1].path) && (game->walltextures[2].path) && (game->walltextures[3].path) && (game->floortexture[0].path) && (game->skytexture[0].path))
		return 0;
	// if (ft_strcmp(game->walltextures[0].path,"(null)")==0)
	// 	perror("Failed to parse North wall texture");
	// if (ft_strcmp(game->walltextures[1].path,"(null)")==0)
	// 	perror("Failed to parse East wall texture");
	// if (ft_strcmp(game->walltextures[2].path,"(null)")==0)
	// 	perror("Failed to parse South wall texture");
	// if (ft_strcmp(game->walltextures[3].path,"(null)")==0)
	// 	perror("Failed to parse West wall texture");
	// if (ft_strcmp(game->floortexture[0].path,"(null)")==0)
	// 	perror("Failed to parse Floor texture");
	// if (ft_strcmp(game->skytexture[0].path,"(null)")==0)
	// 	perror("Failed to parse Sky texture");
	return -1;
}

int create_map(t_game *game)
{
	char* map_line;

	map_line=read_cub_texture(game);
	if (!map_line)
		return -1;
	if (texture_error_handling(game) == -1)
		return -1;
	// analyze_map_structure(game,map_line);
	// map_error_handling(game);
	// parse_cub_map(game);
	// if (read_cub(game)<0)
	// {
	// 	printf("invalid map!, EXITING\n");
	// 	// free game memory
	// 	exit(1);
	// }
    // Implement map creation and initialization
    create_map_from_cub(game, game->screen_width, game->screen_width);
	// map parsing
	// set game->map->player->position.x,y,direction.x,y
	// set game->map->walltextures[4] - 0 to 3, NESW
	// set game->map->floortexture,skytexture
    return 0;
}

int create_player(t_game *game) {
    // Allocate memory for the player structure
    t_player *player = malloc(sizeof(t_player));
    if (player == NULL) {
        fprintf(stderr, "Failed to allocate memory for the player.\n");
        exit(1);  // or handle the error as appropriate
    }

    // Initialize player position
    player->position.x = 22;  // Middle of the map, adjust as necessary
    player->position.y = 12;

    // Initialize player direction (looking along the negative x-axis)
    player->direction.x = -1.0f;
    player->direction.y = 0.0f;

    // Initialize the camera plane for the raycasting (related to the FOV)
    player->plane.x = 0.0f;      // Adjust this value to change the FOV
    player->plane.y = 0.66f;     // This setting assumes a 66 degrees FOV

    // Initialize pitch (not needed for basic raycasting, useful for up/down look)
    player->pitch = 0.0f;

    // Assign the player to the game structure
    game->player = player;
    return 0;
}

// int set_up_hooks(t_game *game) {
//     // Setup necessary hooks for the game engine
//     return 0;
// }


t_ray_node*    calculate_rays(t_game *game, t_ray_node* list)
{
    int x;
    t_ray_node* current;

    current = list;
    x = 0;
    while (x < game->screen_width)
    {
        current = addRay(&list);
        if (current != NULL)
        {
            current->ray.x = x;
            calc_camera_x(game, current);
            calc_ray_dir_x(game, current);
            calc_ray_dir_y(game, current);
            calc_map_x(game, current);
            calc_map_y(game, current);
            calc_side_dist(game, current);
            calc_delta_dist(game, current);
            perform_dda(game, current);
            calc_perp_wall_dist(game, current);
            calc_wall_hit(game, current);
            calc_texture_x(game, current);
            calc_line_height(game, current);
            calc_draw_parameters(game, current);
            // calc_tile_color(game, current);
        }
        x++;
    }
    return (list);
}


void renderFloorAndCeiling(void *mlx, void *win, int screenHeight, int screenWidth)
{
    printf("renderFloorAndCeiling START\n");
    uint32_t floorColor = 0x8B4513;
    uint32_t ceilingColor = 0x87CEEB;

    for(int y = 0; y < screenHeight; y++) {
        for(int x = 0; x < screenWidth; ++x) {
            if (y < screenHeight / 2) {
                // Apply the ceiling color to the top half of the screen
                // buffer[y][x] = ceilingColor;

                mlx_pixel_put(mlx, win, x, y, ceilingColor);
            } else {
                // Apply the floor color to the bottom half of the screen
                // buffer[y][x] = floorColor;
                mlx_pixel_put(mlx, win, x, y, floorColor);
            }
        }
    }
    printf("renderFloorAndCeiling END\n");
}



// void    render_floor_and_ceiling()
// {


//     int texWidth, texHeight;
//     // unsigned int *textureData;

//     float dirX = 1.0, dirY = 0.0;  // Example player direction
//     float planeX = 0.0, planeY = 0.66; // Camera plane vector
//     float posX = 22.0, posY = 12.5; // Example player position

//     // Initialize MiniLibX and create a window
//     mlx = mlx_init();
//     win = mlx_new_window(mlx, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "Floor Casting Example");

//     // Load the texture
//     // textureData = load_texture("path/to/your/texture.xpm", &texWidth, &texHeight);

//     // You might want to store this texture data in a globally accessible way
//     // or modify your rendering functions to accept dynamic texture arrays.
//     // texture[0] = textureData; // Assuming you have a way to handle this
//     texture[0] = load_texture("textures/wood.xpm", &texWidth, &texHeight);

//     // Call the rendering function
//     renderFloorAndCeiling(DEFAULT_S_HEIGHT, DEFAULT_S_WIDTH, dirX, dirY, planeX, planeY, posX, posY, texWidth, texHeight);

//     // Add a loop to keep the window open and handle events, etc.
//     mlx_loop(mlx);
// }
void    render_floor_and_ceiling(t_game *game)
{
    // void *mlx = mlx_init();
    // if (mlx == NULL) {
    //     fprintf(stderr, "Error initializing MiniLibX.\n");
    //     return ;
    // }
    // void *win = mlx_new_window(mlx, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "Simple Floor Ceiling");
    // if (win == NULL) {
    //     fprintf(stderr, "Error creating new window.\n");
    //     return ;
    // }

    // Call the rendering function
    renderFloorAndCeiling(game->mlx_ptr, game->win_ptr, DEFAULT_S_HEIGHT, DEFAULT_S_WIDTH);

    // MiniLibX main loop to handle events
    // mlx_loop(mlx);
    return ;
}



void    refresh_screenv1(t_game *game)
{
    t_ray_node* list = NULL;

    // floor

    // ceiling
    // render_floor_and_ceiling(game);
    (void)list;

    // walls part
    list = calculate_rays(game, list);
    // render_ray_list(list, game);
}

void    refresh_screen(t_game *game)
{
    t_ray_node* list = NULL;

    // floor

    // ceiling
    (void)list;

    // walls part
    list = calculate_rays(game, list);
}

// int render_gamev1(t_game *game)
// {
//     // game->mlx_ptr = mlx_init();
//     // game->win_ptr = mlx_new_window(game->mlx_ptr, game->screen_width, game->screen_height, "MLX Window");
//     refresh_screen(game);
//     set_up_hooks(game);
//     mlx_loop(game->mlx_ptr);
//     return 0;
// }

#define CELL_SIZE 10

int     initgame(t_game **game,char *cub_filepath)
{
    printf("initgame\n");
    create_game_struct(game);
	(*game)->cub_filepath=cub_filepath;
    if (create_map(*game))
	{
		// free memory
		exit(-1);
	}
    create_player(*game);
    setup_game_mlx(*game);

    return(1);
}

#define WIN_WIDTH 500
#define WIN_HEIGHT 500
int main(int argc, char** argv)
{
    t_game     *game;

    game = NULL;
    // if (map_is_valid)
	if (argc==2)
	{
	
        initgame(&game,argv[1]);
	}
    // test_keyhold();


    return 0;
    (void)game;
    return (0);
}