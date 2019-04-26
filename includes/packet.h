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
	#include <stdint.h>
	#include <netinet/udp.h>
	#include <netinet/ip.h>
	typedef struct packet_s
	{
		char *target;
		int port;
		char *password;
	}packet_t;
	
	typedef struct packet_ipv4
	{
		struct iphdr ip;
		struct udphdr udp;
		char payload[256];
	}packet_ipv4_t;
	
	void init_packet(packet_t *core);
	int check_args(packet_t *core);
	int get_option(struct option op[], char **av, packet_t *core, int ac);
	int get_flags_from_switch(packet_t *core, int f);
	int socket_init(packet_t *core, packet_ipv4_t *op4);
	void set_socket_opt(int sock);
	void set_udp_header(struct udphdr *udph, uint16_t s_port, uint16_t d_port,
		unsigned short size);
	void set_ip_header(struct iphdr *iph, unsigned short size,
		uint32_t d_addr, uint32_t s_addr);

#endif
