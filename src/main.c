/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** main.c
*/
/** \file main.c
  * \brief main file used for arguments parsing
  * \author Janote J.
*/
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "packet.h"
int main(int ac, char **av)
{
    packet_t *core = malloc(sizeof(packet_t));
    packet_ipv4_t *adr4 = malloc(sizeof(packet_ipv4_t));
    struct option op[] = {
        {"target", required_argument, 0, 't'},
        {"port", required_argument, 0, 'p'},
        {"password", required_argument, 0, 'P'},
        {0, 0, 0, 0}
    };

    init_packet(core);
    if (av[get_option(op, av, core, ac)] != NULL)
        error(ERROR_ARGS);
    if (check_args(core) == 84)
        error(ERROR_ARG);
    socket_init(core, adr4);
    return (0);
}
