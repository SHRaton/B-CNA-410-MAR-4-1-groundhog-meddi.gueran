/*
** EPITECH PROJECT, 2024
** Groundhog
** File description:
** main
*/

#include "Groundhog.hpp"

int main(int argc, char **argv)
{
    Groundhog groundhog;
    if (argc != 2) {
        std::cerr << "Usage: ./groundhog period" << std::endl;
        return 84;
    }
    if (argc == 2 && std::string(argv[1]) == "-h") {
        std::cout << "SYNOPSIS\n\t./groundhog period\n\nDESCRIPTION\n\tperiod\tthe number of days defining a period\n\t" << std::endl;
        return 0;
    }
    if (argc == 2) {
        groundhog.setPeriod(std::stoi(argv[1]));
        groundhog.loop();
    }
    return 0;
}