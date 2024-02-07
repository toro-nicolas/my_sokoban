/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** The move_player.c
*/

#include "../include/my_sokoban.h"

void get_player_pos(game_t *game)
{
    int row = 0;
    int col = 0;
    int nb_cols = my_strlen(game->map[row]);

    for (; row < game->nb_rows && col < nb_cols; col++) {
        if (game->map[row][col] == 'P') {
            game->player_pos[0] = row;
            game->player_pos[1] = col;
            break;
        }
        if (col + 1 >= nb_cols) {
            col = -1;
            row++;
            nb_cols = my_strlen(game->map[row]);
        }
    }
}

static void reset_place_after_move(game_t *game)
{
    if (game->initiale_map[game->player_pos[0]][game->player_pos[1]] == ' '
    || game->initiale_map[game->player_pos[0]][game->player_pos[1]] == 'X'
    || game->initiale_map[game->player_pos[0]][game->player_pos[1]] == 'P') {
        game->map[game->player_pos[0]][game->player_pos[1]] = ' ';
        return;
    }
    for (hole_t *tmp = game->hole_list; tmp != NULL; tmp = tmp->next) {
        if (tmp->x == game->player_pos[0] && tmp->y == game->player_pos[1]) {
            tmp->full = 0;
            game->map[tmp->x][tmp->y] = 'O';
            return;
        }
    }
}

static void fill_hole(game_t *game, int x, int y)
{
    for (hole_t *tmp = game->hole_list; tmp != NULL; tmp = tmp->next) {
        if (tmp->x == x && tmp->y == y) {
            tmp->full = 1;
            return;
        }
    }
}

static int move_box(game_t *game, int top, int left)
{
    if (game->map[game->player_pos[0] + top]
    [game->player_pos[1] + left] != '#' && game->map
    [game->player_pos[0] + top][game->player_pos[1] + left] != 'X') {
        game->map[game->player_pos[0] + top][game->player_pos[1] + left] = 'X';
        if (game->initiale_map[game->player_pos[0] + top / 2]
        [game->player_pos[1] + left / 2] == 'X')
            game->map[game->player_pos[0] + top / 2]
            [game->player_pos[1] + left / 2] = ' ';
        else
            game->map[game->player_pos[0] + top / 2]
            [game->player_pos[1] + left / 2] = game->initiale_map
            [game->player_pos[0] + top / 2][game->player_pos[1] + left / 2];
        if (game->initiale_map[game->player_pos[0] + top]
        [game->player_pos[1] + left] == 'O')
            fill_hole(game, game->player_pos[0] + top,
                game->player_pos[1] + left);
        return 1;
    }
    return 0;
}

static void move_player_up(game_t *game)
{
    if (game->player_pos[0] > 0 && game->player_pos[1] <
    my_strlen(game->map[game->player_pos[0] - 1]) &&
    game->map[game->player_pos[0] - 1][game->player_pos[1]] != '#') {
        if (game->map[game->player_pos[0] - 1][game->player_pos[1]] == 'X'
        && game->player_pos[0] - 2 < 0)
            return;
        if (game->map[game->player_pos[0] - 1][game->player_pos[1]] == 'X' &&
        move_box(game, -2, 0) == 0)
            return;
        game->map[game->player_pos[0] - 1][game->player_pos[1]] = 'P';
        reset_place_after_move(game);
    }
}

static void move_player_down(game_t *game)
{
    if (game->player_pos[0] + 1 < game->nb_rows && game->player_pos[1] <
    my_strlen(game->map[game->player_pos[0] + 1])
    && game->map[game->player_pos[0] + 1][game->player_pos[1]] != '#') {
        if (game->map[game->player_pos[0] + 1][game->player_pos[1]] == 'X'
        && game->player_pos[0] + 2 > game->nb_rows)
            return;
        if (game->map[game->player_pos[0] + 1][game->player_pos[1]] == 'X' &&
        move_box(game, 2, 0) == 0)
            return;
        game->map[game->player_pos[0] + 1][game->player_pos[1]] = 'P';
        reset_place_after_move(game);
    }
}

static void move_player_left(game_t *game)
{
    if (game->player_pos[1] > 0 &&
    game->map[game->player_pos[0]][game->player_pos[1] - 1] != '\0' &&
    game->map[game->player_pos[0]][game->player_pos[1] - 1] != '#') {
        if (game->map[game->player_pos[0]][game->player_pos[1] - 1] == 'X'
            && game->player_pos[1] - 2 < 0)
            return;
        if (game->map[game->player_pos[0]][game->player_pos[1] - 1] == 'X' &&
        move_box(game, 0, -2) == 0)
            return;
        game->map[game->player_pos[0]][game->player_pos[1] - 1] = 'P';
        reset_place_after_move(game);
    }
}

static void move_player_right(game_t *game)
{
    if (game->map[game->player_pos[0]][game->player_pos[1] + 1] != '\0' &&
    game->map[game->player_pos[0]][game->player_pos[1] + 1] != '#') {
        if (game->map[game->player_pos[0]][game->player_pos[1] + 1] == 'X'
        && game->player_pos[1] + 2 >= my_strlen
        (game->map[game->player_pos[0]]))
            return;
        if (game->map[game->player_pos[0]][game->player_pos[1] + 1] == 'X'
        && move_box(game, 0, 2) == 0)
            return;
        game->map[game->player_pos[0]][game->player_pos[1] + 1] = 'P';
        reset_place_after_move(game);
    }
}

void move_player(game_t *game, int touch)
{
    get_player_pos(game);
    if (touch == KEY_UP)
        move_player_up(game);
    if (touch == KEY_DOWN)
        move_player_down(game);
    if (touch == KEY_LEFT)
        move_player_left(game);
    if (touch == KEY_RIGHT)
        move_player_right(game);
}
