/*
** EPITECH PROJECT, 2018
** NWP_mychap_2018
** File description:
** ip_header.c
*/
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <stdint.h>
#include <string.h>
#include <netdb.h>
#include "packet.h"

int socket_init(packet_t *core, packet_ipv4_t *op4)
{
	int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

	if (sock < 0) {
		perror("Failed to create raw socket");
		exit(84);
	}
	set_socket_opt(sock);
	get_info_socket(sock);
	struct hostent *hostname = NULL;
	
	hostname = gethostbyname(core->target);
	if (hostname == NULL) {
		printf("No such hostname: '%s'\n", core->target);
		exit(84);
	}
	printf("Ip adress = %s\n", hostname->h_name);
	return (0);
}

int get_info_socket(int sock)
{
	struct sockaddr_in sa;
	int sa_len;
	
	if (getsockname(sock, &sa, &sa_len) == -1) {
		fprintf(stdout, "Error: getsockname() failed");
		return (84);
	}
	printf("Local IP address is: %s\n", inet_ntoa(sa.sin_addr));
	printf("Local port is: %d\n", (int) ntohs(sa.sin_port));
	return (1);
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
	udph->uh_sport = s_port; // getsockname()
	udph->uh_dport = d_port; // param port
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
	iph->daddr = d_addr; // inet_addr(target)
	iph->saddr = s_addr; // recup by getsockname
}
