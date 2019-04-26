/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** ip_header.c
*/
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <stdint.h>
#include <string.h>
#include "packet.h"

int socket_init(packet_t *core, packet_ipv4_t *op4)
{
	int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	struct sockaddr_in sin;
	struct sockaddr_in cin;

	if (sock < 0) {
		perror("Failed to create raw socket");
		exit(84);
	}
	set_socket_opt(sock);
	// getsockname(sock,&cin,size cin)
	// getaddrinfo(core-target, )
	return (0);
}

void get_socket_info(int sock, int on)
{
	return;
}

void set_socket_opt(int sock)
{
	int on = 1;

	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *) &on,
	sizeof(on)) < 0) {
		fprintf(stderr, "Cannot set IP_HDRINCL: %s\n", strerror(errno));
		exit(84);
	}
	return;
}

void set_udp_header(struct udphdr *udph, uint16_t s_port, uint16_t d_port,
	unsigned short size)
{
	udph->uh_sport = s_port;
	udph->uh_dport = d_port;
	udph->uh_sum = 0;
	udph->uh_ulen = htons(sizeof(struct udphdr) + size);
}

void set_ip_header(struct iphdr *iph, unsigned short size,
	uint32_t d_addr, uint32_t s_addr)
{
	iph->version = IPVERSION;
	iph->ihl = 5;
	iph->tos = IPTOS_LOWDELAY;
	iph->tot_len = htons(4 + 4 * iph->ihl + size);
	iph->id = rand();
	iph->frag_off = 0;
	iph->ttl = IPDEFTTL;
	iph->protocol = SOL_UDP;
	iph->check = 0;
	iph->daddr = d_addr;
	iph->saddr = s_addr;
}
