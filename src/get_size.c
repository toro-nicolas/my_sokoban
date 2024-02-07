/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** The get_colums.c
*/

#include "../include/my_sokoban.h"

int get_rows(char const *map_str)
{
    int lines = 1;

    for (int c = 0; map_str[c] != '\0'; c++) {
        if (map_str[c] == '\n' && map_str[c + 1] != '\0')
            lines = lines + 1;
    }
    return lines;
}

int get_columns(char const *map_str, int start)
{
    int columns = 0;

    for (int index = start; map_str[index] != '\0' && map_str[index] != '\n';
    index++) {
        columns = columns + 1;
    }
    return columns;
}

int get_max_cols(char **map, int nb_rows)
{
    int max_cols = 0;
    int nb_cols = 0;

    for (int row = 0; row < nb_rows; row++) {
        nb_cols = my_strlen(map[row]);
        if (nb_cols > max_cols)
            max_cols = nb_cols;
    }
    return max_cols;
}
