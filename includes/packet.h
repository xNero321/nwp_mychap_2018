/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** packet.h
*/

#ifndef __PACKET__
#define __PACKET__
	#include <stdio.h>
	#include <stdlib.h>
	#include <getopt.h>
	typedef struct packet_s
	{
		char *target;
		char *port;
		char *password;
	}packet_t;
	
	void init_packet(packet_t *core);
	int get_option(struct option op[], char **av, packet_t *core, int ac);
	int get_flags_from_switch(packet_t *core, int f);
	
#endif
