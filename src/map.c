/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** The open_map.c
*/

#include "../include/my_sokoban.h"

char **get_only_map(char const *map_str, int nb_rows)
{
    char **map = malloc(sizeof(char *) * (nb_rows + 1));
    int nb_cols = 0;
    int index = 0;

    for (int row = 0; row < nb_rows; row++) {
        nb_cols = get_columns(map_str, index);
        map[row] = malloc((sizeof(char) * (nb_cols + 1)));
        for (int col = 0; col < nb_cols; col++) {
            map[row][col] = map_str[index];
            index++;
        }
        map[row][nb_cols] = '\0';
        index++;
    }
    map[nb_rows] = NULL;
    return map;
}

char **copy_map(char **map, int nb_rows)
{
    char **new_map = malloc(sizeof(char *) * (nb_rows + 1));
    int nb_cols = 0;

    for (int row = 0; row < nb_rows; row++) {
        nb_cols = my_strlen(map[row]);
        new_map[row] = malloc((sizeof(char) * (nb_cols + 1)));
        for (int col = 0; col < nb_cols; col++)
            new_map[row][col] = map[row][col];
        new_map[row][nb_cols] = '\0';
    }
    new_map[nb_rows] = NULL;
    return new_map;
}

int print_map(game_t *game)
{
    for (int row = 0; row < game->nb_rows; row++) {
        write(1, game->map[row], my_strlen(game->map[row]));
        write(1, "\n", 1);
    }
    return 0;
}

int load_game(char *file_path)
{
    int file = open(file_path, O_RDONLY);
    struct stat file_infos;
    int file_status = stat(file_path, &file_infos);
    char *map_str;
    char **map;
    int rows;

    search_file_error(file, file_status, &file_infos);
    map_str = malloc(sizeof(char) * (file_infos.st_size + 1));
    map_str[read(file, map_str, file_infos.st_size)] = '\0';
    rows = get_rows(map_str);
    search_map_str_error(map_str, rows);
    map = get_only_map(map_str, rows);
    search_map_error(map, rows);
    return update_game(map, rows);
}
