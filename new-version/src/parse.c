#include "cub3d.h"

int	check_spacee(char **colors)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (colors[i])
	{
		while (colors[i][j])
		{
			while (colors[i][j] && colors[i][j] != ' ' && colors[i][j] != '\t')
				j++;
			while (colors[i][j] && (colors[i][j] == ' ' || colors[i][j] == '\t'))
				j++;
			if (colors[i][j] && (colors[i][j] >= '0' && colors[i][j] <= '9'))
				return (1);
		}
		i++;
		j = 0;
	}
	return (0);
}

int check_again(char **colors)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (colors[i])
	{
		while (colors[i][j])
		{
			if ((colors[i][j] >= '0' && colors[i][j] <= '9') || colors[i][j] == ' ' || colors[i][j] == '\t')
				j++;
			else
				return (1);
		}
		i++;
		j = 0;
	}
	return (0);
}

static int parse_color(char *line)
{
	int     r, g, b;
	char    **colors;
	int i = 0;
	int		j;

	j = 0;
	while (line[j])
	{
		if (line[j] == ',')
			i++;
		j++;
	}
	colors = ft_split(line, ',');
	if (!colors)
	ft_error("Memory allocation failed");
	if (i != 2) 
	{
		i++;
		while (i > 0)
		free(colors[--i]);
		free(colors);
		ft_error("Invalid RGB color format");
	}
	i = 0;
	while (colors[i])
		i++;
	if (i != 3)
		ft_error("Invalid RGB color format");
	if (check_spacee(colors) || check_again(colors))
	ft_error("Invalid RGB color format");
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

int len_cal(t_list *list)
{
	size_t i;

	i = 0;
	while (list)
	{
		if (ft_strlen(list->str) > i)
			i = ft_strlen(list->str);
		list = list->next;
	}
	return (i);
}

char **list_to_array(t_list *list)
{
	t_list *lst;
	char **map;
	int i;
	int	len;

	i = 0;
	len = len_cal(list);
	lst = list;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	map = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (list)
	{
		map[i] = ft_strdup1(list->str, len);
		i++;
		list = list->next;
	}
	map[i] = NULL;
	i = 0;
	return (map);
}

int check_sides(char **map1)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map1[0][j])
	{
		while (map1[0][j] == ' ' || map1[0][j] == '\t')
			j++;
		if (map1[0][j] != '1' && map1[0][j] != ' ' && map1[0][j] != '\t' && map1[0][j] != '\n')
			return (1);
		j++;
	}
	j = 0;
	while (map1[i + 1])
		i++;
	while (map1[i][j])
	{
		while (map1[i][j] == ' ' || map1[i][j] == '\t')
			j++;
		if (map1[i][j] != '1' && map1[i][j] != ' ' && map1[i][j] != '\t' && map1[i][j] != '\n')
			return (1);
		j++;
	}
	return (0);
}

int check_zero(char **map, int i, int j)
{
	// if (!map[i][j + 1])
	// 	return (1);
	if (map[i][j + 1] != '0' && map[i][j + 1] != '1' && map[i][j + 1] != 'S' && map[i][j + 1] != 'W' && 
		map[i][j + 1] != 'E' && map[i][j + 1] != 'N')
		return (1);
	if (map[i][j - 1] != '0' && map[i][j - 1] != '1' && map[i][j - 1] != 'S' && map[i][j - 1] != 'W' && 
		map[i][j - 1] != 'E' && map[i][j - 1] != 'N')
		return (1);
	if (map[i + 1][j] != '0' && map[i + 1][j] != '1' && map[i + 1][j] != 'S' && map[i + 1][j] != 'W' && 
		map[i + 1][j] != 'E' && map[i + 1][j] != 'N')
		return (1);
	if (map[i - 1][j] != '0' && map[i - 1][j] != '1' && map[i - 1][j] != 'S' && map[i - 1][j] != 'W' && 
		map[i - 1][j] != 'E' && map[i - 1][j] != 'N')
		return (1);
	
	return (0);
}

int parse_1(char **map1, t_config **config)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(map1[i])
	{
		if (check_sides(map1))
			return (1);
		if (!map1[i + 1])
			break;
		while (map1[i][j])
		{
			if (map1[i][j] == ' ' || map1[i][j] == '\t')
			{
				j++;
				continue;
			}
			if (map1[i][j] == 'S' || map1[i][j] == 'N'|| map1[i][j] == 'E'|| map1[i][j] == 'W')
			{
				if ((*config)->flag_player == 0)
				{
					// data_player(map1[i][j], data);
					(*config)->flag_player = 1;
				}
				else
					return(1);
			}

			if (map1[i][j] == '0')
			{
				if (check_zero(map1, i, j))
					return (1);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (0);
}

int check_line(char *line)
{
	int i;
	int index = 0;
	
	i = 0;
	if (line[0] == '\n')
	return (1);
	while (line[i]!= '\0')
	{
			// printf("%s", line);
			if(line[i] == ' ' || line[i] == '\t' || line[i]== '\n')
				index++;
			i++;
		}
		if (i == index)
			return(1);
	return (0);
}

void parse_cub_file(const char *filename, t_data *data)
{
	int fd;
	int error_flag = 0;
	t_list *list = NULL;
	t_list *list_copy = NULL;
	char **map1;
	t_config *config;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Cannot open .cub file");

	char *line;
	int map_started = 0;
	int line_count = 0;
	int map_line_start = 0;

	config = &data->config;
	config->width = WIDTH;
	config->height = HEIGHT;
	config->no_texture = NULL;
	config->so_texture = NULL;
	config->we_texture = NULL;
	config->ea_texture = NULL;
	config->flag_player = 0;
	config->floor_color = 0;
	config->ceil_color = 0;
	config->map = NULL;

	while ((line = get_next_line(fd)) != NULL)
	{
		char *trimmed = ft_strtrim(line, " \t\n");
		if (!trimmed)
		{
			// free

			
		}
		if (*trimmed == '\0' && !map_started)
		{
			free(trimmed);
			free(line);
			continue;
		}
		if (!map_started && ft_strncmp(trimmed, "NO ", 3) == 0 && !config->no_texture)
		{
			char *path_start = ft_strtrim(trimmed + 3, " \t\n");
			if (!path_start) ft_error("Memory allocation failed");
			config->no_texture = ft_strdup(path_start);
			free(path_start);
			if (!config->no_texture) ft_error("Texture allocation failed");
		}
		else if (!map_started && ft_strncmp(trimmed, "SO ", 3) == 0 && !config->so_texture)
		{
			char *path_start = ft_strtrim(trimmed + 3, " \t\n");
			if (!path_start)
			ft_error("Memory allocation failed");
			config->so_texture = ft_strdup(path_start);
			free(path_start);
			if (!config->so_texture) ft_error("Texture allocation failed");
		}
		else if (!map_started && ft_strncmp(trimmed, "WE ", 3) == 0 && !config->we_texture)
		{
			char *path_start = ft_strtrim(trimmed + 3, " \t\n");
			if (!path_start)
			ft_error("Memory allocation failed");
			config->we_texture = ft_strdup(path_start);
			free(path_start);
			if (!config->we_texture)
			ft_error("Texture allocation failed");
		}
		else if (!map_started && ft_strncmp(trimmed, "EA ", 3) == 0 && !config->ea_texture)
		{
			char *path_start = ft_strtrim(trimmed + 3, " \t\n");
			if (!path_start)
			ft_error("Memory allocation failed");
			config->ea_texture = ft_strdup(path_start);
			free(path_start);
			if (!config->ea_texture) ft_error("Texture allocation failed");
		}
		else if (!map_started && ft_strncmp(trimmed, "F ", 2) == 0 && !config->floor_color) {
			char *color_str = ft_strtrim(trimmed + 2, " \t\n");
			if (!color_str) ft_error("Memory allocation failed");
			config->floor_color = parse_color(color_str);
			free(color_str);
		}
		else if (!map_started && ft_strncmp(trimmed, "C ", 2) == 0 && !config->ceil_color) {
			char *color_str = ft_strtrim(trimmed + 2, " \t\n");
			if (!color_str) ft_error("Memory allocation failed");
			config->ceil_color = parse_color(color_str);
			free(color_str);
		}
		else if (!map_started && strchr("01NSEW ", *trimmed)) {
			map_started = 1;
			error_flag = 1;
			map_line_start = line_count;
		}
		else if (!error_flag)
		{
			free(line);
			ft_error("parce error\n");
		}
		
		if (map_started)
		{
			if (!config->no_texture || !config->so_texture || !config->we_texture ||
				!config->ea_texture || !config->ceil_color || !config->floor_color)
				ft_error("Missing required elements in .cub file");
			if(check_line(line))
				ft_error("parsing map");
			list_copy = ft_lstnew(line);
			ft_lstadd_back(&list, list_copy);
		}
		else
			free(line);
		free(trimmed);

		line_count++;
	}
	if (list)
		map1 = list_to_array(list);
	
	if ((map1 && parse_1(map1, &config)))
		ft_error("parsing map");
	if (!config->flag_player)
		ft_error("parsing map");
	if (map_started)
		parse_map(config, data, map1, line_count - map_line_start);
	close(fd);

	if (!config->no_texture || !config->so_texture || !config->we_texture ||
		!config->ea_texture)
		ft_error("Missing required elements in .cub file");
}
