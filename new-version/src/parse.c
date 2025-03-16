#include "cub3d.h"

static int parse_color(char *line)
{
	int     r, g, b;
	char    **colors;

	colors = ft_split(line, ',');
	if (!colors)
		ft_error("Memory allocation failed");

	int i = 0;
	while (colors[i])
		i++;
	if (i != 3) {
		while (i > 0)
			free(colors[--i]);
		free(colors);
		ft_error("Invalid RGB color format");
	}

	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);

	i = 0;
	while (colors[i])
		free(colors[i++]);
	free(colors);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		ft_error("Invalid RGB color format");

	return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}

static void measure_map(char **lines, int *map_height, int *map_width, int line_count)
{
	*map_height = 0;
	*map_width = 0;
	int i;
	int width;

	i = 0;
	while (i < line_count)
	{
		width = ft_strlen(lines[i]);
		if (width > *map_width)
			*map_width = width;
		if (width > 0)
			(*map_height)++;
		i++;
	}
}

static void flood_fill(char **map, int x, int y, int width, int height, int *valid)
{
    if (x < 0 || x >= width || y < 0 || y >= height || map[y][x] == ' ') {
        *valid = 0; // Hit a space or out-of-bounds: map is invalid
        return;
    }
    if (map[y][x] == '1' || map[y][x] == 'X') // Wall or already visited
        return;

    map[y][x] = 'X'; // Mark as visited
    flood_fill(map, x + 1, y, width, height, valid);
    flood_fill(map, x - 1, y, width, height, valid);
    flood_fill(map, x, y + 1, width, height, valid);
    flood_fill(map, x, y - 1, width, height, valid);
}

static void validate_map_boundaries(t_config *config, t_data *data)
{
    char **map_copy = malloc(sizeof(char *) * config->map_height);
	int valid = 1;
	int i = 0;
    while (i < config->map_height)
	{
        map_copy[i] = ft_strdup(config->map[i]);
		i++;
	}

    flood_fill(map_copy, data->player.x / TILE_UNIT, data->player.y / TILE_UNIT,
               config->map_width, config->map_height, &valid);
	i = 0;
    while (i < config->map_height)
	{
        free(map_copy[i]);
		i++;
	}
    free(map_copy);

    if (!valid)
        ft_error("Map is not enclosed around player");
}

static void parse_map(t_config *config, t_data *data, char **map_lines, int line_count)
{
	int		row;
	int		i;
	int		col;
	char	*line;

	measure_map(map_lines, &config->map_height, &config->map_width, line_count);
	config->map = malloc(sizeof(char *) * config->map_height);
	if (!config->map)
		ft_error("Map allocation failed");

	row = 0;
	i = 0;
	while (i < line_count && row < config->map_height)
	{
		if (ft_strlen(map_lines[i]) == 0)
			continue ;
		config->map[row] = malloc(config->map_width + 1);
		if (!config->map[row])
			ft_error("Map row allocation failed");
		ft_memset(config->map[row], ' ', config->map_width);
		col = 0;
		line = map_lines[i];
		while (*line && col < config->map_width)
		{
			config->map[row][col] = *line;
			if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			{
				data->player.x = col * TILE_UNIT + (TILE_UNIT / 2);
				data->player.y = row * TILE_UNIT + (TILE_UNIT / 2);
				if (*line == 'N')
					data->player.angle = M_PI / 2;
				else if (*line == 'S')
					data->player.angle = 3 * M_PI / 2;
				else if (*line == 'E')
					data->player.angle = 0;
				else if (*line == 'W')
					data->player.angle = M_PI;
				config->map[row][col] = '0';
			}
			col++;
			line++;
		}
		config->map[row][config->map_width] = '\0';
		row++;
		i++;
	}
}

void parse_cub_file(const char *filename, t_data *data)
{
	int fd;
	t_config *config;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Cannot open .cub file");

	char *line;
	int map_started = 0;
	char *map_lines[1024];
	int line_count = 0;
	int map_line_start = 0;
	int i;

	config = &data->config;
	config->width = WIDTH;
	config->height = HEIGHT;
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	config->floor_color = 0;
	config->ceil_color = 0;
	config->map = NULL;

	while ((line = get_next_line(fd)) != NULL)
	{
		char *trimmed = ft_strtrim(line, " \t\n");
		if (!trimmed || *trimmed == '\0')
		{
			free(trimmed);
			free(line);
			continue;
		}

		if (!map_started && ft_strncmp(trimmed, "R ", 2) == 0)
		{
            char **res_split = ft_split(trimmed, ' ');
            if (!res_split)
                ft_error("Memory allocation failed");

            int i = 0;
            while (res_split[i])
                i++;
            if (i != 3 || ft_strncmp(res_split[0], "R", 2) != 0) {
                while (i > 0)
                    free(res_split[--i]);
                free(res_split);
                ft_error("Invalid resolution");
            }

            config->width = ft_atoi(res_split[1]);
            config->height = ft_atoi(res_split[2]);

            i = 0;
            while (res_split[i])
                free(res_split[i++]);
            free(res_split);

            if (config->width <= 0 || config->height <= 0)
                ft_error("Invalid resolution");
        }
		else if (!map_started && ft_strncmp(trimmed, "NO ", 3) == 0)
		{
			char *path_start = ft_strtrim(trimmed + 3, " \t\n");
			if (!path_start) ft_error("Memory allocation failed");
			config->no_texture = ft_strdup(path_start);
			free(path_start);
			if (!config->no_texture) ft_error("Texture allocation failed");
		}
		else if (!map_started && ft_strncmp(trimmed, "SO ", 3) == 0)
		{
			char *path_start = ft_strtrim(trimmed + 3, " \t\n");
			if (!path_start)
				ft_error("Memory allocation failed");
			config->so_texture = ft_strdup(path_start);
			free(path_start);
			if (!config->so_texture) ft_error("Texture allocation failed");
		}
		else if (!map_started && ft_strncmp(trimmed, "WE ", 3) == 0)
		{
			char *path_start = ft_strtrim(trimmed + 3, " \t\n");
			if (!path_start)
				ft_error("Memory allocation failed");
			config->we_texture = ft_strdup(path_start);
			free(path_start);
			if (!config->we_texture)
				ft_error("Texture allocation failed");
		}
		else if (!map_started && ft_strncmp(trimmed, "EA ", 3) == 0)
		{
			char *path_start = ft_strtrim(trimmed + 3, " \t\n");
			if (!path_start)
				ft_error("Memory allocation failed");
			config->ea_texture = ft_strdup(path_start);
			free(path_start);
			if (!config->ea_texture) ft_error("Texture allocation failed");
		}
		else if (!map_started && ft_strncmp(trimmed, "F ", 2) == 0) {
			char *color_str = ft_strtrim(trimmed + 2, " \t\n");
			if (!color_str) ft_error("Memory allocation failed");
			config->floor_color = parse_color(color_str);
			free(color_str);
		}
		else if (!map_started && ft_strncmp(trimmed, "C ", 2) == 0) {
			char *color_str = ft_strtrim(trimmed + 2, " \t\n");
			if (!color_str) ft_error("Memory allocation failed");
			config->ceil_color = parse_color(color_str);
			free(color_str);
		}
		else if (!map_started && strchr("01NSEW ", *trimmed)) {
			map_started = 1;
			map_line_start = line_count;
		}

		if (map_started) {
			if (line_count < 1024)
				map_lines[line_count] = line;
			else
				free(line);
		} else {
			free(line);
		}
		free(trimmed);
		line_count++;
	}

	if (map_started)
		parse_map(config, data, map_lines + map_line_start, line_count - map_line_start);
	validate_map_boundaries(config, data);

	i = map_line_start;
	while (i < line_count)
	{
		if (i < 1024)
			free(map_lines[i]);
		i++;
	}
	close(fd);

	if (!config->no_texture || !config->so_texture || !config->we_texture ||
		!config->ea_texture || !config->map)
		ft_error("Missing required elements in .cub file");
}
