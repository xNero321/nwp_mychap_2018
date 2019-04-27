/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** main.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <packet.h>

int main(int ac, char **av)
{
    packet_t *core = malloc(sizeof(packet_t));
    packet_ipv4_t *adr4 = malloc(sizeof(packet_ipv4_t));

    init_packet(core);
    struct option op[] = {
        {"target", required_argument, 0, 't'},
        {"port", required_argument, 0, 'p'},
        {"password", required_argument, 0, 'P'},
        {0, 0, 0, 0}
    };
    if (av[get_option(op, av, core, ac)] != NULL)
        error(ERROR_ARGS);
    if (check_args(core) == 84)
        error(ERROR_ARG);
    socket_init(core, adr4);
    return (0);
}

void init_packet(packet_t *core)
{
    core->target = NULL;
    core->port = 0;
    core->password = NULL;
}

int check_args(packet_t *core)
{
    if (core->target != NULL && core->port > 0 && core->password != NULL)
        return (1);
    return (84);
}

int get_option(struct option op[], char **av, packet_t *core, int ac)
{
    int l_id = 0;

    for (int f = 0; f = getopt_long(ac, av, "t:p:P:", op,
    &l_id);) {
        if (get_flags_from_switch(core, f) == -1)
            return (optind);
    }
}

int get_flags_from_switch(packet_t *core, int f)
{
    switch(f) {
        case 't': core->target = strdup(optarg);
            break;
        case 'p': core->port = atoi(optarg);
            break;
        case 'P': core->password = strdup(optarg);
            break;
        case '?': error(ERROR_FLAG);
        case -1: return (-1);
    }
}
