/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** args_parsing.c
*/
/** \file args_parsing.c
  * \brief file used for arguments parsing
  * \author Janote J.
*/
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "packet.h"
/*
** PURPOSE : Initialise core structure
** PARAMS  : packet_t *core
** RETURNS : void
*/
void init_packet(packet_t *core)
{
    core->target = NULL;
    core->port = 0;
    core->password = NULL;
}

/*
** PURPOSE : Checks if arguments are correctly given to the program
   otherwise it will return an error.
** PARAMS  : packet_t *core
** RETURNS : int
*/
int check_args(packet_t *core)
{
    if (core->target != NULL && core->port > 0 && core->password != NULL)
        return (1);
    return (84);
}

/*
** PURPOSE : Takes the parameters with getopt_long and loop on aruments
** PARAMS  : struct option op[], char **av, packet_t *core, int ac
** RETURNS : int
*/
int get_option(struct option op[], char **av, packet_t *core, int ac)
{
    int l_id = 0;

    for (int f = 0; f = getopt_long(ac, av, "t:p:P:", op,
    &l_id);) {
        if (get_flags_from_switch(core, f) == -1)
            return (optind);
    }
}

/*
** PURPOSE : loop on arguments and attribute the right values
** PARAMS  : packet_t *core, int f
** RETURNS : int
*/
int get_flags_from_switch(packet_t *core, int f)
{
    switch (f) {
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
