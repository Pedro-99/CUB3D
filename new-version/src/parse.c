#include "cub3d.h"

static char *trim_whitespace(char *str) {
    while (*str == ' ' || *str == '\t')
        str++;
    char *end = str + ft_strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
        *end-- = '\0';
    return str;
}

static uint32_t parse_color(char *line) {
    int r, g, b;
    if (sscanf(line, "%d,%d,%d", &r, &g, &b) != 3 ||
        r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        ft_error("Invalid RGB color format");
    return (r << 24) | (g << 16) | (b << 8) | 0xFF; // RGBA (fully opaque)
}

static char *read_file(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        ft_error("Cannot open .cub file");

    char *content = NULL;
    char buffer[1024];
    size_t total_size = 0;
    ssize_t bytes;

    while ((bytes = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes] = '\0';
        char *tmp = realloc(content, total_size + bytes + 1);
        if (!tmp)
            ft_error("Memory allocation failed");
        content = tmp;
        memcpy(content + total_size, buffer, bytes);
        total_size += bytes;
        content[total_size] = '\0';
    }
    close(fd);
    if (bytes < 0)
        ft_error("Error reading file");
    return content;
}

static void measure_map(char *lines, int *map_height, int *map_width) {
    char *line = lines;
    *map_height = 0;
    *map_width = 0;
    while (*line) {
        int width = 0;
        while (*line && *line != '\n') {
            width++;
            line++;
        }
        if (width > *map_width)
            *map_width = width;
        if (width > 0)
            (*map_height)++;
        if (*line)
            line++; // Skip newline
    }
}

static void parse_map(t_config *config, t_data *data, char *map_start) {
    measure_map(map_start, &config->map_height, &config->map_width);
    config->map = malloc(sizeof(char *) * config->map_height);
    if (!config->map)
        ft_error("Map allocation failed");

    char *line = map_start;
    int row = 0;
    while (row < config->map_height) {
        config->map[row] = malloc(config->map_width + 1);
        if (!config->map[row])
            ft_error("Map row allocation failed");
        ft_memset(config->map[row], ' ', config->map_width); // Pad with spaces
        int col = 0;
        while (*line && *line != '\n' && col < config->map_width) {
            config->map[row][col] = *line;
            if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W') {
                data->player.x = col * 64 + 32; // Assuming 64x64 tiles
                data->player.y = row * 64 + 32;
                if (*line == 'N') data->player.angle = M_PI / 2;
                else if (*line == 'S') data->player.angle = 3 * M_PI / 2;
                else if (*line == 'E') data->player.angle = 0;
                else if (*line == 'W') data->player.angle = M_PI;
                config->map[row][col] = '0'; // Replace player start with empty space
            }
            col++;
            line++;
        }
        config->map[row][config->map_width] = '\0';
        while (*line && *line != '\n')
            line++; // Skip excess characters
        if (*line)
            line++; // Skip newline
        row++;
    }
}

void parse_cub_file(const char *filename, t_data *data) {
    char *content = read_file(filename);
    char *line = content;
    int map_started = 0;

    t_config *config = &data->config;
    config->width = WIDTH;
    config->height = HEIGHT;
    config->no_texture = NULL;
    config->so_texture = NULL;
    config->we_texture = NULL;
    config->ea_texture = NULL;
    config->floor_color = 0;
    config->ceil_color = 0;
    config->map = NULL;

    while (*line) {
        line = trim_whitespace(line);
        if (*line == '\0' || *line == '\n') {
            if (*line)
                line++;
            continue;
        }

        if (!map_started && strncmp(line, "R ", 2) == 0) {
            if (sscanf(line + 2, "%d %d", &config->width, &config->height) != 2)
                ft_error("Invalid resolution");
        }
        else if (!map_started && strncmp(line, "NO ", 3) == 0) {
            char *path_start = trim_whitespace(line + 3);
            char *path_end = strchr(path_start, '\n');
            if (path_end) *path_end = '\0'; // Terminate at newline
            config->no_texture = strdup(path_start);
            if (!config->no_texture) ft_error("Texture allocation failed");
            if (path_end) *path_end = '\n'; // Restore for next line
        }
        else if (!map_started && strncmp(line, "SO ", 3) == 0) {
            char *path_start = trim_whitespace(line + 3);
            char *path_end = strchr(path_start, '\n');
            if (path_end) *path_end = '\0';
            config->so_texture = strdup(path_start);
            if (!config->so_texture) ft_error("Texture allocation failed");
            if (path_end) *path_end = '\n';
        }
        else if (!map_started && strncmp(line, "WE ", 3) == 0) {
            char *path_start = trim_whitespace(line + 3);
            char *path_end = strchr(path_start, '\n');
            if (path_end) *path_end = '\0';
            config->we_texture = strdup(path_start);
            if (!config->we_texture) ft_error("Texture allocation failed");
            if (path_end) *path_end = '\n';
        }
        else if (!map_started && strncmp(line, "EA ", 3) == 0) {
            char *path_start = trim_whitespace(line + 3);
            char *path_end = strchr(path_start, '\n');
            if (path_end) *path_end = '\0';
            config->ea_texture = strdup(path_start);
            if (!config->ea_texture) ft_error("Texture allocation failed");
            if (path_end) *path_end = '\n';
        }
        else if (!map_started && strncmp(line, "F ", 2) == 0)
            config->floor_color = parse_color(trim_whitespace(line + 2));
        else if (!map_started && strncmp(line, "C ", 2) == 0)
            config->ceil_color = parse_color(trim_whitespace(line + 2));
        else if (!map_started && strchr("01NSEW ", *line)) {
            map_started = 1;
            parse_map(config, data, line);
        }

        while (*line && *line != '\n')
            line++;
        if (*line)
            line++;
    }

    if (!config->no_texture || !config->so_texture || !config->we_texture ||
        !config->ea_texture || !config->map)
        ft_error("Missing required elements in .cub file");

    free(content);
}