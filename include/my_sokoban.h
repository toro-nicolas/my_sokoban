/*
** EPITECH PROJECT, 2023
** settingup
** File description:
** The setting_up.h
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <ncurses.h>
#include <signal.h>
#include "my.h"

#ifndef SETTING_UP_H
    #define SETTING_UP_H

typedef struct hole_s {
    int x;
    int y;
    int full;
    struct hole_s *next;
} hole_t;

typedef struct game_s {
    char **initiale_map;
    char **map;
    int nb_rows;
    int max_cols;
    int in_game;
    int player_pos[2];
    hole_t *hole_list;
} game_t;

/* Errors handling */
void search_file_error(int file, int infos_status, struct stat *file_infos);
void search_map_str_error(char *map_str, int rows);
void search_map_error(char **map, int rows);

/* Get size */
int get_rows(char const *map_str);
int get_columns(char const *map_str, int start);
int get_max_cols(char **map, int nb_rows);

/* Game */
char **copy_map(char **map, int nb_rows);
int print_map(game_t *game);
int load_game(char *file);
void get_player_pos(game_t *game);
void move_player(game_t *game, int touch);
int update_game(char **map, int rows);

#endif /* SETTING_UP_H */
