/*
** EPITECH PROJECT, 2023
** my_sokoban
** File description:
** The main.c
*/

#include "../include/my_sokoban.h"

int print_help(void)
{
    my_printf("USAGE\n"
        "     ./my_sokoban map\n"
        "DESCRIPTION\n"
        "     map  file representing the warehouse map,"
        "containing '#' for walls,\n"
        "          'P' for the player,"
        "'X' for boxes and 'O' for storage locations.\n");
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 2) {
        if (argc == 1) {
            my_putstr_error("No file specified\n");
            return 84;
        } else {
            my_putstr_error("Too many open files\n");
            return 84;
        }
    } else {
        if (my_strcmp(argv[1], "-h") == 0)
            return print_help();
        return load_game(argv[1]);
    }
}
