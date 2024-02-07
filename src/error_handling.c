/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** The error_handling.c
*/

#include "../include/my_sokoban.h"

void search_file_error(int file, int infos_status, struct stat *file_infos)
{
    if (file < 0 || infos_status < 0) {
        my_putstr_error("Cannot open or get file information\n");
        exit(84);
    }
    if (S_ISREG(file_infos->st_mode) != 1) {
        my_putstr_error("The file is not a regular file\n");
        exit(84);
    }
    if (file_infos->st_size == 0) {
        my_putstr_error("The file is empty\n");
        exit(84);
    }
}

static int count_lines(char const *map_str)
{
    int counter = 0;

    for (int c = 0; map_str[c] != '\0'; c++) {
        if (map_str[c] == '\n')
            counter = counter + 1;
    }
    return counter - 1;
}

void search_map_str_error(char *map_str, int rows)
{
    if (rows < 3) {
        my_putstr_error("Invalid rows number\n");
        exit(84);
    }
}

static void check_barrier(char c, int localisation[2], int map_size[2])
{
    if ((localisation[0] == 0 || localisation[1] == 0 ||
    localisation[0] == map_size[0] - 1 ||
    localisation[1] == map_size[1] - 1) && c != '#') {
        my_putstr_error("The map barrier aren't good\n");
        exit(84);
    }
}

static void check_map_error(char c, int *player, int *hole, int *box)
{
    if (c == 'P')
        *player = *player + 1;
    if (c == 'O')
        *hole = *hole + 1;
    if (c == 'X')
        *box = *box + 1;
    if (c == '\0') {
        my_putstr_error("Lines are not full\n");
        exit(84);
    }
    if (c != ' ' && c != '#' && c != 'X' && c != 'O' && c != 'P') {
        my_putstr_error("Invalid characters detected in map\n");
        exit(84);
    }
}

void search_map_error(char **map, int rows)
{
    int player = 0;
    int hole = 0;
    int box = 0;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; map[row][col] != '\0'; col++) {
            check_map_error(map[row][col], &player, &hole, &box);
        }
    }
    if (player != 1) {
        my_putstr_error("Can't find player\n");
        exit(84);
    }
    if (hole != box || hole == 0 || box == 0) {
        my_putstr_error("Invalid box or hole number\n");
        exit(84);
    }
}
