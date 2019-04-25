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
	
	init_packet(core);
	struct option op[] = {
		{"target", required_argument, 0, 't'},
		{"port", required_argument, 0, 'p'},
		{"password", required_argument, 0, 'P'},
		{0, 0, 0, 0}
	};
	if (av[get_option(op, av, core, ac)] != NULL) {
		printf("Error: Arguments are not right.");
		exit(84);
	}
	return (0);
}

void init_packet(packet_t *core)
{
	core->target = "";
	core->port = "";
	core->password = "";
}

int get_option(struct option op[], char **av, packet_t *core, int ac)
{
	int l_id = 0;
	
	for (int f = 0; f = getopt_long_only(ac, av, "t:p:P:", op,
	&l_id);) {
		if (get_flags_from_switch(core, f) == -1)
			return (optind);
	}
}

int get_flags_from_switch(packet_t *core, int f)
{
	switch(f) {
		case 't': printf("le flag t est trouvé.\n");
			break;
		case 'p': printf("le flag p est trouvé.\n");
			break;
		case 'P': printf("le flag P est trouvé.\n");
			break;
		case '?': printf("Flag non approprié");
		 	exit(84);
		case -1: return (-1);
	}
}
