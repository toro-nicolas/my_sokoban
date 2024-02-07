/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** The print_map.c
*/

#include "../include/my_sokoban.h"

void print_window_size(void)
{
    erase();
    move(LINES / 2 - 1 / 2,
        COLS / 2 - 28 / 2);
    printw("Please, enlarge the terminal");
    refresh();
}

int check_box_blocked(game_t *game, int row, int col)
{
    if ((game->map[row - 1][col] == '#' || game->map[row - 1][col] == 'X') &&
    (game->map[row][col - 1] == '#' || game->map[row][col - 1] == 'X'))
        return 1;
    if ((game->map[row - 1][col] == '#' || game->map[row - 1][col] == 'X') &&
    (game->map[row][col + 1] == '#' || game->map[row][col + 1] == 'X'))
        return 1;
    if ((game->map[row + 1][col] == '#' || game->map[row + 1][col] == 'X') &&
    (game->map[row][col + 1] == '#' || game->map[row][col + 1] == 'X'))
        return 1;
    if ((game->map[row + 1][col] == '#' || game->map[row + 1][col] == 'X') &&
    (game->map[row][col - 1] == '#' || game->map[row][col - 1] == 'X'))
        return 1;
    return 0;
}

static int check_game_over(game_t *game)
{
    int hole_nb = 0;
    int blocked_box = 0;
    int row = 0;
    int col = 0;
    int nb_cols = my_strlen(game->map[row]);

    for (hole_t *tmp = game->hole_list; tmp != NULL; tmp = tmp->next)
        hole_nb = hole_nb + 1;
    for (; row < game->nb_rows && col < nb_cols; col++) {
        if (game->map[row][col] == 'X')
            blocked_box = blocked_box + check_box_blocked(game, row, col);
        if (col + 1 >= nb_cols) {
            col = 0;
            row++;
            nb_cols = my_strlen(game->map[row]);
        }
    }
    if (hole_nb == blocked_box)
        return 1;
    return 0;
}

static int check_win(game_t *game)
{
    int hole_nb = 0;
    int hole_full = 0;

    for (hole_t *tmp = game->hole_list; tmp != NULL; tmp = tmp->next) {
        hole_nb = hole_nb + 1;
    }
    for (hole_t *tmp = game->hole_list;
    tmp != NULL && tmp->full == 1; tmp = tmp->next) {
        hole_full = hole_full + 1;
    }
    if (hole_nb == hole_full)
        return 1;
    return 0;
}

int print_status(game_t *game)
{
    int result = 0;

    erase();
    if (check_win(game)) {
        game->in_game = 0;
        result = 1;
    }
    if (game->in_game == 1 && check_game_over(game)) {
        game->in_game = 0;
        result = 2;
    }
    for (int row = 0; row < game->nb_rows; row++)
        printw("%s\n", game->map[row]);
    refresh();
    return result;
}

static void get_hole_list(game_t *game)
{
    hole_t *tmp;
    int pos[2] = {0, 0};
    int nb_cols = my_strlen(game->map[pos[0]]);

    game->hole_list = NULL;
    for (; pos[0] < game->nb_rows && pos[1] < nb_cols; pos[1]++) {
        if (game->map[pos[0]][pos[1]] == 'O') {
            tmp = malloc(sizeof(hole_t));
            tmp->x = pos[0];
            tmp->y = pos[1];
            tmp->full = 0;
            tmp->next = game->hole_list;
            game->hole_list = tmp;
        }
        if (pos[1] + 1 >= nb_cols) {
            pos[1] = 0;
            pos[0]++;
            nb_cols = my_strlen(game->map[pos[0]]);
        }
    }
}

static game_t *init_game(char **map, int nb_rows)
{
    game_t *game = malloc(sizeof(game_t));

    game->initiale_map = map;
    game->map = copy_map(map, nb_rows);
    game->nb_rows = nb_rows;
    game->max_cols = get_max_cols(map, nb_rows);
    game->in_game = 1;
    get_player_pos(game);
    get_hole_list(game);
    return game;
}

int exit_game(game_t *game, int status)
{
    usleep(3000);
    endwin();
    for (int row = 0; row < game->nb_rows; row++) {
        free(game->map[row]);
        free(game->initiale_map[row]);
    }
    free(game->map);
    free(game->initiale_map);
    free(game);
    return status;
}

static void wait_touch(game_t *game, int *touch)
{
    *touch = getch();
    if (*touch == ' ') {
        for (int row = 0; row < game->nb_rows; row++)
            free(game->map[row]);
        game->map = copy_map(game->initiale_map, game->nb_rows);
        get_hole_list(game);
    } else
        move_player(game, *touch);
}

int update_game(char **map, int nb_rows)
{
    game_t *game = init_game(map, nb_rows);
    int status = 0;
    int touch = 0;

    initscr();
    keypad(stdscr, TRUE);
    while (game->in_game) {
        if (touch == KEY_RESIZE &&
        (game->nb_rows > LINES || game->max_cols > COLS))
            print_window_size();
        status = print_status(game);
        if (game->nb_rows < LINES && game->max_cols < COLS && status != 0)
            break;
        wait_touch(game, &touch);
    }
    return exit_game(game, status - 1);
}
