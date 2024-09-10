import random

def generate_map(width, height):
    # Create the header
    header = """NO textures/foilagewall01.xpm
SO textures/dmgwall01.xpm
WE textures/dmgwall06.xpm
EA textures/dmgwall07.xpm


F 184,113,39
C 51,198,227

"""

    # Initialize the map with empty spaces
    map_data = [['0' for _ in range(width)] for _ in range(height)]

    # Add borders
    for i in range(height):
        map_data[i][0] = '1'
        map_data[i][-1] = '1'
    for j in range(width):
        map_data[0][j] = '1'
        map_data[-1][j] = '1'

    # Add random walls
    wall_density = 0.01  # Adjust this value to change the density of walls
    for i in range(1, height - 1):
        for j in range(1, width - 1):
            if random.random() < wall_density:
                map_data[i][j] = '1'

    # Add the starting position 'S'
    while True:
        x, y = random.randint(1, width - 2), random.randint(1, height - 2)
        if map_data[y][x] == '0':
            map_data[y][x] = 'S'
            break

    # Convert the map data to a string
    map_string = '\n'.join(' '.join(row) for row in map_data)

    return header + map_string

def save_map_to_file(filename, map_data):
    with open(filename, 'w') as f:
        f.write(map_data)

# Generate a map that's 3 times bigger than the input
width, height = 93, 75  # 31 * 3, 25 * 3
map_data = generate_map(width, height)
save_map_to_file('generated_map.cub', map_data)

print("Map has been generated and saved to 'generated_map.cub'")